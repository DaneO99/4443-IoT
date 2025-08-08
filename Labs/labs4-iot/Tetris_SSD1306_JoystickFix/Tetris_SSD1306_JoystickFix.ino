// Tetris Game for ST7796 480x320 in Portrait Mode on Arduino Uno R4 WiFi
#include <TFT_eSPI.h>
#include <SPI.h>
#include <math.h>

TFT_eSPI tft = TFT_eSPI();

// Logical playfield dimensions
const int COLS = 10;
const int SCREEN_WIDTH  = 320;
const int SCREEN_HEIGHT = 480;
const int BLOCK_SIZE = SCREEN_WIDTH / COLS;
const int ROWS = SCREEN_HEIGHT / BLOCK_SIZE;

// Joystick + button pins
const int VRX = A1;
const int VRY = A0;
const int SW  = 2;

// Playfield state and piece info
int grid[ROWS][COLS] = {0};
unsigned long lastDropTime = 0;
unsigned long dropInterval = 500;
int score = 0, level = 1;
bool gameOver = false;

int currentPiece[4][2];
int pieceType, posX, posY;

// Predefined tetromino shapes
const int PIECES[7][4][2] = {
  {{0,0},{0,1},{1,0},{1,1}}, // O
  {{0,1},{1,1},{2,1},{3,1}}, // I
  {{1,0},{1,1},{1,2},{2,2}}, // L
  {{1,0},{1,1},{1,2},{0,2}}, // J
  {{0,1},{1,1},{1,0},{2,0}}, // S
  {{0,0},{1,0},{1,1},{2,1}}, // Z
  {{0,1},{1,0},{1,1},{1,2}}  // T
};

// Color palette (index 0 = empty)
uint16_t colors[] = {
  TFT_BLACK,
  TFT_RED, TFT_YELLOW, TFT_ORANGE,
  TFT_GREEN, TFT_BLUE, TFT_PINK, TFT_CYAN
};

void drawBlock(int x, int y, int colorIndex) {
  // Only draw if on-screen
  if (x < 0 || x >= COLS || y < 0 || y >= ROWS) return;
  tft.fillRect(x * BLOCK_SIZE, y * BLOCK_SIZE,
               BLOCK_SIZE, BLOCK_SIZE,
               colors[colorIndex]);
  tft.drawRect(x * BLOCK_SIZE, y * BLOCK_SIZE,
               BLOCK_SIZE, BLOCK_SIZE,
               TFT_BLACK);
}

void drawGrid() {
  // Draw only the *locked* blocks
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      drawBlock(x, y, grid[y][x]);
    }
  }
  // Draw the moving piece on top
  for (int i = 0; i < 4; i++) {
    int x = currentPiece[i][0] + posX;
    int y = currentPiece[i][1] + posY;
    drawBlock(x, y, pieceType + 1);
  }
  // HUD
  tft.setCursor(SCREEN_WIDTH - 100, 10);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.printf("Score:%4d", score);
  tft.setCursor(10, 10);
  tft.printf("Lvl:%2d", level);
}

bool canMove(int dx, int dy) {
  for (int i = 0; i < 4; i++) {
    int x = currentPiece[i][0] + posX + dx;
    int y = currentPiece[i][1] + posY + dy;
    if (x < 0 || x >= COLS || y >= ROWS) return false;
    if (y >= 0 && grid[y][x])      return false;
  }
  return true;
}

void lockPiece() {
  for (int i = 0; i < 4; i++) {
    int x = currentPiece[i][0] + posX;
    int y = currentPiece[i][1] + posY;
    if (y >= 0 && y < ROWS) grid[y][x] = pieceType + 1;
  }
}

void clearLines() {
  for (int y = ROWS - 1; y >= 0; y--) {
    bool full = true;
    for (int x = 0; x < COLS; x++) {
      if (!grid[y][x]) { full = false; break; }
    }
    if (full) {
      score += 100;
      level = score / 500 + 1;
      // Speed up drop interval by ~15% per level
      dropInterval = max((unsigned long)(500 * pow(0.85, level - 1)), 100UL);
      // Shift rows down
      for (int yy = y; yy > 0; yy--)
        for (int x = 0; x < COLS; x++)
          grid[yy][x] = grid[yy - 1][x];
      // Clear top row
      for (int x = 0; x < COLS; x++) grid[0][x] = 0;
      y++; // recheck this row
    }
  }
}

void spawnPiece() {
  pieceType = random(0, 7);
  for (int i = 0; i < 4; i++) {
    currentPiece[i][0] = PIECES[pieceType][i][0];
    currentPiece[i][1] = PIECES[pieceType][i][1];
  }
  posX = COLS/2 - 2;
  posY = 0;
  if (!canMove(0, 0)) {
    // Game Over screen
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(3);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.setCursor((SCREEN_WIDTH/2)-80, SCREEN_HEIGHT/2 - 20);
    tft.println("GAME OVER");
    gameOver = true;
  }
}

void setup() {
  pinMode(SW, INPUT_PULLUP);
  tft.init();
  tft.setRotation(1);          // portrait 320×480
  tft.setSwapBytes(true);      // faster block fills
  tft.fillScreen(TFT_BLACK);   // clear once
  
  randomSeed(analogRead(A2));
  spawnPiece();
  drawGrid();
  lastDropTime = millis();
}

void loop() {
  if (gameOver) {
    if (digitalRead(SW) == LOW) {
      delay(300);
      // reset state
      memset(grid, 0, sizeof(grid));
      score = 0; level = 1;
      dropInterval = 500;
      gameOver = false;
      tft.fillScreen(TFT_BLACK);
      spawnPiece();
    }
    return;
  }

  // Read joystick for left/right
  int dx = 0;
  int xVal = analogRead(VRX);
  if (xVal < 300)      dx = -1;
  else if (xVal > 700) dx = +1;
  if (dx && canMove(dx, 0)) {
    posX += dx;
    delay(100);  // simple rate limit
  }

  // Read joystick down for quick drop
  if (analogRead(VRY) > 700 && canMove(0, 1)) {
    posY++;
    lastDropTime = millis();
  }

  // Automatic drop
  if (millis() - lastDropTime > dropInterval) {
    if (canMove(0, 1)) {
      posY++;
    } else {
      lockPiece();
      clearLines();
      spawnPiece();
    }
    lastDropTime = millis();
  }

  drawGrid();
  delay(30);
}
