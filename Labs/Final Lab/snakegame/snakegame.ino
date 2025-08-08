// Snake Game with Swipe Controls - Fixed
#include <TFT_eSPI.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <Arduino.h>

// Hardware config
#define TOUCH_CS 9
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320
#define GRID_SIZE 20
#define GRID_WIDTH (SCREEN_WIDTH / GRID_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / GRID_SIZE)

// Snake state
int snakeX[100], snakeY[100], snakeLen = 3;
int dirX = 1, dirY = 0;
int foodX, foodY;
unsigned long lastMove = 0;
int score = 0;
bool gameOver = false;
bool redraw = true;
bool firstDraw = true;

// Swipe detection
int swipeStartX = 0, swipeStartY = 0;
int swipeEndX = 0, swipeEndY = 0;
bool swipeInProgress = false;
unsigned long swipeStartTime = 0;
#define MIN_SWIPE_DISTANCE 30  // Reduced for more sensitivity
#define MAX_SWIPE_TIME 300     // Reduced for faster response

// Previous positions for efficient redraw
int prevSnakeX[100], prevSnakeY[100], prevSnakeLen = 0;
int prevFoodX = -1, prevFoodY = -1;
int prevScore = -1;

// Display and Touch
TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen ts(TOUCH_CS);

void setup() {
  Serial.begin(9600);
  Serial.println("Snake Game with Swipe Controls Starting...");
  
  // Initialize SPI for touch screen
  SPI.begin();
  
  // Initialize display
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  
  // Initialize touch screen
  ts.begin();
  
  randomSeed(analogRead(A0));
  resetGame();
  
  Serial.println("Snake Game Ready!");
}

void loop() {
  // Read touch
  TS_Point p = ts.getPoint();
  bool touch = (p.z > 0);
  
  if (touch) {
    // Map touch coordinates (using your calibration values)
    int x = map(p.x, 611, 3575, 0, SCREEN_WIDTH);
    int y = map(p.y, 719, 3431, 0, SCREEN_HEIGHT);
    x = constrain(x, 0, SCREEN_WIDTH-1);
    y = constrain(y, 0, SCREEN_HEIGHT-1);
    
    if (gameOver) {
      // Any touch restarts the game when game over
      resetGame();
      redraw = true;
      return;
    }
    
    if (!swipeInProgress) {
      // Start of swipe
      swipeStartX = x;
      swipeStartY = y;
      swipeStartTime = millis();
      swipeInProgress = true;
      
      Serial.print("Swipe start: ");
      Serial.print(x);
      Serial.print(", ");
      Serial.println(y);
    } else {
      // Update end position during swipe
      swipeEndX = x;
      swipeEndY = y;
    }
  } else {
    if (swipeInProgress && !gameOver) {
      // End of swipe - calculate direction
      int deltaX = swipeEndX - swipeStartX;
      int deltaY = swipeEndY - swipeStartY;
      int distance = sqrt(deltaX * deltaX + deltaY * deltaY);
      unsigned long swipeTime = millis() - swipeStartTime;
      
      Serial.print("Swipe end - Distance: ");
      Serial.print(distance);
      Serial.print(" Time: ");
      Serial.println(swipeTime);
      
      if (distance > MIN_SWIPE_DISTANCE && swipeTime < MAX_SWIPE_TIME) {
        // Valid swipe detected
        if (abs(deltaX) > abs(deltaY)) {
          // Horizontal swipe
          if (deltaX > 0 && dirX != -1) {
            dirX = 1; dirY = 0; // Right
            Serial.println("Swipe RIGHT");
          } else if (deltaX < 0 && dirX != 1) {
            dirX = -1; dirY = 0; // Left
            Serial.println("Swipe LEFT");
          }
        } else {
          // Vertical swipe
          if (deltaY > 0 && dirY != -1) {
            dirX = 0; dirY = 1; // Down
            Serial.println("Swipe DOWN");
          } else if (deltaY < 0 && dirY != 1) {
            dirX = 0; dirY = -1; // Up
            Serial.println("Swipe UP");
          }
        }
        redraw = true;
      }
      
      swipeInProgress = false;
    }
  }
  
  // Snake auto-move
  if (!gameOver && millis() - lastMove > 300) { 
    updateSnake(); 
    redraw = true; 
  }
  
  // Redraw if needed
  if (redraw) {
    drawGame();
    redraw = false;
  }
}

void resetGame() {
  snakeLen = 3;
  dirX = 1;
  dirY = 0;
  score = 0;
  gameOver = false;
  
  // Initialize snake in center
  for (int i = 0; i < snakeLen; i++) {
    snakeX[i] = GRID_WIDTH/2 - i;
    snakeY[i] = GRID_HEIGHT/2;
  }
  
  // Generate food
  generateFood();
  
  // Reset previous positions
  prevSnakeLen = 0;
  prevFoodX = -1;
  prevFoodY = -1;
  prevScore = -1;
  firstDraw = true;
}

void generateFood() {
  do {
    foodX = random(0, GRID_WIDTH);
    foodY = random(0, GRID_HEIGHT);
  } while (foodX == snakeX[0] && foodY == snakeY[0]);
}

void updateSnake() {
  lastMove = millis();
  
  // Move body
  for (int i = snakeLen - 1; i > 0; i--) {
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  
  // Move head
  snakeX[0] += dirX;
  snakeY[0] += dirY;
  
  // Check wall collision
  if (snakeX[0] < 0 || snakeX[0] >= GRID_WIDTH || 
      snakeY[0] < 0 || snakeY[0] >= GRID_HEIGHT) {
    gameOver = true;
    return;
  }
  
  // Check self collision
  for (int i = 1; i < snakeLen; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
      return;
    }
  }
  
  // Check food collision
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLen++;
    score++;
    generateFood();
  }
}

void drawGame() {
  if (firstDraw) {
    // Full screen redraw
    tft.fillScreen(TFT_BLACK);
    firstDraw = false;
  }
  
  if (gameOver) {
    // Game over screen
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(3);
    tft.drawCentreString("GAME OVER", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 30, 2);
    
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.drawCentreString("Final Score: " + String(score), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 2);
    tft.drawCentreString("Touch to restart", SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 30, 2);
    return;
  }
  
  // Clear old snake segments
  for (int i = 0; i < prevSnakeLen; i++) {
    tft.fillRect(prevSnakeX[i] * GRID_SIZE, prevSnakeY[i] * GRID_SIZE, 
                 GRID_SIZE - 1, GRID_SIZE - 1, TFT_BLACK);
  }
  
  // Clear old food
  if (prevFoodX >= 0 && prevFoodY >= 0) {
    tft.fillRect(prevFoodX * GRID_SIZE, prevFoodY * GRID_SIZE, 
                 GRID_SIZE - 1, GRID_SIZE - 1, TFT_BLACK);
  }
  
  // Draw new snake
  for (int i = 0; i < snakeLen; i++) {
    uint16_t color = (i == 0) ? TFT_YELLOW : TFT_GREEN;  // Head is yellow
    tft.fillRect(snakeX[i] * GRID_SIZE, snakeY[i] * GRID_SIZE, 
                 GRID_SIZE - 1, GRID_SIZE - 1, color);
  }
  
  // Draw new food
  tft.fillRect(foodX * GRID_SIZE, foodY * GRID_SIZE, 
               GRID_SIZE - 1, GRID_SIZE - 1, TFT_RED);
  
  // Update score if changed - moved to bottom left
  if (score != prevScore) {
    tft.fillRect(10, SCREEN_HEIGHT - 30, 200, 25, TFT_BLACK);  // Clear area at bottom left
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.drawString("Score: " + String(score), 10, SCREEN_HEIGHT - 30);
    prevScore = score;
  }
  
  // Store current positions for next frame
  for (int i = 0; i < snakeLen; i++) {
    prevSnakeX[i] = snakeX[i];
    prevSnakeY[i] = snakeY[i];
  }
  prevSnakeLen = snakeLen;
  prevFoodX = foodX;
  prevFoodY = foodY;
}