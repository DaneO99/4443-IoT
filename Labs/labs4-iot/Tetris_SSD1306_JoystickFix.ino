#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Grid setup
#define COLS 10
#define ROWS 12
#define BLOCK 5

#define JOY_X A0
#define JOY_Y A1
#define JOY_SW 2
#define BUZZER_PIN 3

#define THRESH_LOW 300
#define THRESH_HIGH 700

uint8_t grid[ROWS][COLS];
int pieceX, pieceY, score = 0, level = 1;
const int levelThreshold = 200;
unsigned long initialDrop = 500;
unsigned long dropInterval = 500;
unsigned long dropTimer = 0;
bool gameOver = false;

const uint8_t tetrominoes[7][4][4] = {
  { {0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0} }, // O
  { {0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0} }, // I
  { {0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0} }, // T
  { {0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0} }, // L
  { {0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0} }, // J
  { {0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0} }, // S
  { {0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0} }  // Z
};

uint8_t current[4][4];
uint8_t nextPiece[4][4];

void setup() {
  pinMode(JOY_SW, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  randomSeed(analogRead(A3));
  generateNextPiece();
  spawnPiece();
}

void loop() {
  if (gameOver) {
    if (digitalRead(JOY_SW) == LOW) {
      delay(200);
      resetGame();
    }
    return;
  }

  handleInput();
  if (millis() - dropTimer > dropInterval) {
    moveDown();
    dropTimer = millis();
  }
  drawGame();
}

void drawGame() {
  display.clearDisplay();

  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      if (grid[r][c]) {
        display.fillRect(c * BLOCK, r * BLOCK, BLOCK - 1, BLOCK - 1, WHITE);
      }
    }
  }

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      if (current[r][c]) {
        int gx = pieceX + c;
        int gy = pieceY + r;
        if (gx >= 0 && gx < COLS && gy >= 0 && gy < ROWS)
          display.fillRect(gx * BLOCK, gy * BLOCK, BLOCK - 1, BLOCK - 1, WHITE);
      }
    }
  }

  int boundaryX = COLS * BLOCK;
  display.drawLine(boundaryX, 0, boundaryX, SCREEN_HEIGHT, WHITE);

  display.setCursor(boundaryX + 2, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("S:");
  display.print(score);
  display.setCursor(boundaryX + 2, 10);
  display.print("L:");
  display.print(level);

  display.setCursor(boundaryX + 2, 24);
  display.print("Next:");
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      if (nextPiece[r][c]) {
        display.fillRect(boundaryX + 2 + c * 4, 34 + r * 4, 3, 3, WHITE);
      }
    }
  }

  display.display();
}

void moveDown() {
  if (valid(pieceX, pieceY + 1, current)) {
    pieceY++;
  } else {
    placePiece();
  }
}

void rotatePiece() {
  uint8_t temp[4][4];
  for (int r = 0; r < 4; r++)
    for (int c = 0; c < 4; c++)
      temp[c][3 - r] = current[r][c];

  if (valid(pieceX, pieceY, temp)) memcpy(current, temp, 16);
}

void handleInput() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);
  bool pressed = digitalRead(JOY_SW) == LOW;
  bool moved = false;

  if (x < THRESH_LOW && abs(y - 512) < 150 && valid(pieceX - 1, pieceY, current)) {
    pieceX--;
    tone(BUZZER_PIN, 300, 40);
    moved = true;
  }
  if (x > THRESH_HIGH && abs(y - 512) < 150 && valid(pieceX + 1, pieceY, current)) {
    pieceX++;
    tone(BUZZER_PIN, 300, 40);
    moved = true;
  }
  if (y > THRESH_HIGH && abs(x - 512) < 150) {
    moveDown();
    tone(BUZZER_PIN, 200, 30);
    moved = true;
  }
  if (y < THRESH_LOW && abs(x - 512) < 150) {
    rotatePiece();
    tone(BUZZER_PIN, 500, 40);
    moved = true;
  }

  if (pressed && !gameOver) {
    while (valid(pieceX, pieceY + 1, current)) pieceY++;
    placePiece();
    delay(200);
  }

  if (moved) delay(150);
}

bool valid(int x, int y, uint8_t mat[4][4]) {
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      if (mat[r][c]) {
        int gx = x + c;
        int gy = y + r;
        if (gx < 0 || gx >= COLS || gy >= ROWS || grid[gy][gx]) return false;
      }
    }
  }
  return true;
}

void placePiece() {
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      if (current[r][c]) grid[pieceY + r][pieceX + c] = 1;
    }
  }
  tone(BUZZER_PIN, 150, 50);
  clearLines();
  spawnPiece();
}

void clearLines() {
  for (int r = ROWS - 1; r >= 0; r--) {
    bool full = true;
    for (int c = 0; c < COLS; c++) {
      if (!grid[r][c]) {
        full = false;
        break;
      }
    }
    if (full) {
      for (int y = r; y > 0; y--) {
        memcpy(grid[y], grid[y - 1], COLS);
      }
      memset(grid[0], 0, COLS);
      score += 100;
      tone(BUZZER_PIN, 600, 100);
      if (score >= level * levelThreshold) {
        level++;
        dropInterval = max((unsigned long)(initialDrop * pow(0.85, level - 1)), 100UL);
      }
      r++;
    }
  }
}

void generateNextPiece() {
  int type = random(0, 7);
  memcpy(nextPiece, tetrominoes[type], 16);
}

void spawnPiece() {
  memcpy(current, nextPiece, 16);
  pieceX = (COLS / 2) - 2;
  pieceY = 0;
  generateNextPiece();

  if (!valid(pieceX, pieceY, current)) {
    gameOver = true;
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(20, 20);
    display.setTextColor(WHITE);
    display.print("GAME OVER");
    display.setCursor(10, 35);
    display.print("Push to Restart");
    display.display();
    tone(BUZZER_PIN, 100, 300);
  }
}

void resetGame() {
  memset(grid, 0, sizeof(grid));
  score = 0;
  level = 1;
  dropInterval = initialDrop;
  gameOver = false;
  generateNextPiece();
  spawnPiece();
}
