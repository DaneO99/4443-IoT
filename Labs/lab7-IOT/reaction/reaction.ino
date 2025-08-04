#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// WS2812B Setup
#define LED_PIN    6
#define LED_COUNT  8
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// I2C LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button Pins
const int player1Button = 2;
const int player2Button = 3;

// Buzzer Pin
#define BUZZER_PIN 4

// Timing Variables
long ranDelay = 0;
unsigned long startMillis;
unsigned long player1Time = 0;
unsigned long player2Time = 0;
bool gameStarted = false;

void setup() {
  Serial.begin(9600);
  pinMode(player1Button, INPUT);
  pinMode(player2Button, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  strip.begin();
  strip.show();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Reaction Timer");
}

void loop() {
  resetState();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Any Button");
  lcd.setCursor(0, 1);
  lcd.print("To Start");

  waitForAnyPlayerPress();

  lcd.clear();
  lcd.print("Get Ready!");
  setStripColor(255, 0, 0); // RED
  quietBeep(600, 150);
  delay(1000);

  lcd.clear();
  lcd.print("Get Set!");
  setStripColor(255, 150, 0); // YELLOW
  quietBeep(800, 150);
  delay(1000);

  ranDelay = random(1000, 5000);
  startMillis = millis();
  while (millis() - startMillis < ranDelay) {
    if (digitalRead(player1Button) == HIGH) {
      falseStart(1);
      return;
    }
    if (digitalRead(player2Button) == HIGH) {
      falseStart(2);
      return;
    }
  }

  lcd.clear();
  lcd.print("GO!");
  setStripColor(0, 255, 0); // GREEN
  gameStarted = true;
  startMillis = millis();
  quietBeep(1000, 300);

  while (!player1Time || !player2Time) {
    if (digitalRead(player1Button) == HIGH && !player1Time) {
      player1Time = millis() - startMillis;
    }
    if (digitalRead(player2Button) == HIGH && !player2Time) {
      player2Time = millis() - startMillis;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("P1: ");
  lcd.print(player1Time / 1000.0, 3);
  lcd.print("s");

  lcd.setCursor(0, 1);
  lcd.print("P2: ");
  lcd.print(player2Time / 1000.0, 3);
  lcd.print("s");

  delay(3000);
  showWinner();
}

void waitForAnyPlayerPress() {
  while (digitalRead(player1Button) == 0 && digitalRead(player2Button) == 0) {
    // Wait for player to start
  }
  delay(300);
}

void falseStart(int player) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Player ");
  lcd.print(player);
  lcd.print(" False");
  lcd.setCursor(0, 1);
  lcd.print("Start!");
  flashStripColor(255, 0, 0); // RED FLASH
  quietBeep(400, 600);
  delay(3000);
}

void showWinner() {
  lcd.clear();
  lcd.setCursor(0, 0);

  if (player1Time < player2Time) {
    lcd.print("Player 1 Wins!");
    winnerAnimation(1);
  } else if (player2Time < player1Time) {
    lcd.print("Player 2 Wins!");
    winnerAnimation(2);
  } else {
    lcd.print("It's a Tie!");
    flashStripColor(0, 0, 255);
  }

  delay(3000);
}

void winnerAnimation(int player) {
  uint32_t color;
  if (player == 1)
    color = strip.Color(0, 0, 255); // BLUE for Player 1
  else
    color = strip.Color(255, 0, 255); // PURPLE for Player 2

  for (int cycle = 0; cycle < 3; cycle++) {
    // Wipe forward
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, color);
      strip.show();
      delay(75);
    }
    // Wipe backward
    for (int i = LED_COUNT - 1; i >= 0; i--) {
      strip.setPixelColor(i, 0);
      strip.show();
      delay(75);
    }
  }

  // Final flash celebration
  for (int j = 0; j < 3; j++) {
    setStripColor((player == 1) ? 0 : 255, 0, (player == 1) ? 255 : 0);
    delay(200);
    clearStrip();
    delay(200);
  }
}

void setStripColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

void flashStripColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < 3; i++) {
    setStripColor(r, g, b);
    delay(300);
    clearStrip();
    delay(300);
  }
}

void clearStrip() {
  setStripColor(0, 0, 0);
}

void resetState() {
  player1Time = 0;
  player2Time = 0;
  gameStarted = false;
  clearStrip();
}

void quietBeep(int frequency, int duration) {
  tone(BUZZER_PIN, frequency);
  delay(duration);
  noTone(BUZZER_PIN);
}
