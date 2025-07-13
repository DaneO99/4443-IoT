/*********
  Complete project details at https://randomnerdtutorials.com
  
  This is an example for our Monochrome OLEDs based on SSD1306 drivers. 
  Written by Limor Fried/Ladyada for Adafruit Industries, with contributions
  from the open source community. BSD license.

  You need three connections:
    * SDA → A4
    * SCL → A5
    * RESET → RESET (or tie to -1 in code to share Arduino reset)
    * VCC → 3.3 V (or 5 V if your module supports it)
    * GND → GND
*********/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED width in pixels
#define SCREEN_HEIGHT 64 // OLED height in pixels

// If your module has its own reset pin tied to a digital pin, change this.
// Otherwise use -1 to share Arduino RESET.
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES   10  // For the snowfall animation
#define LOGO_WIDTH  16
#define LOGO_HEIGHT 16

static const unsigned char PROGMEM logo_bmp[] = {
  B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Show splash, pause, then clear
  display.display();
  delay(2000);
  display.clearDisplay();

  // Draw a single pixel
  display.drawPixel(10, 10, WHITE);
  display.display();
  delay(2000);

  // Run all the test routines once
  testdrawline();
  testdrawrect();
  testfillrect();
  testdrawcircle();
  testfillcircle();
  testdrawroundrect();
  testfillroundrect();
  testdrawtriangle();
  testfilltriangle();
  testdrawchar();
  testdrawstyles();
  testscrolltext();
  testdrawbitmap();

  // Invert and restore
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  // Start the endless snowfall animation from bitmap
  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT);
}

void loop() {
  // Nothing needed here—the testanimate() function never returns
}

// ————————————————————————————————————————————————————————————————————————————————

void testdrawline() {
  display.clearDisplay();
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, 0, i, display.height() - 1, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(0, 0, display.width() - 1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(0, display.height() - 1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(0, display.height() - 1, display.width() - 1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i = display.width() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = display.height() - 1; i >= 0; i -= 4) {
    display.drawLine(display.width() - 1, display.height() - 1, 0, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i = 0; i < display.height(); i += 4) {
    display.drawLine(display.width() - 1, 0, 0, i, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i = 0; i < display.width(); i += 4) {
    display.drawLine(display.width() - 1, 0, i, display.height() - 1, WHITE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testdrawrect() {
  display.clearDisplay();
  for (int16_t i = 0; i < display.height() / 2; i += 2) {
    display.drawRect(i, i, display.width() - 2*i, display.height() - 2*i, WHITE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testfillrect() {
  display.clearDisplay();
  for (int16_t i = 0; i < display.height() / 2; i += 3) {
    display.fillRect(i, i, display.width() - 2*i, display.height() - 2*i, INVERSE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testdrawcircle() {
  display.clearDisplay();
  for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testfillcircle() {
  display.clearDisplay();
  for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 3) {
    display.fillCircle(display.width()/2, display.height()/2, i, INVERSE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testdrawroundrect() {
  display.clearDisplay();
  for (int16_t i = 0; i < display.height()/2 - 2; i += 2) {
    display.drawRoundRect(i, i,
      display.width() - 2*i,
      display.height() - 2*i,
      display.height()/4,
      WHITE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testfillroundrect() {
  display.clearDisplay();
  for (int16_t i = 0; i < display.height()/2 - 2; i += 2) {
    display.fillRoundRect(i, i,
      display.width() - 2*i,
      display.height() - 2*i,
      display.height()/4,
      INVERSE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testdrawtriangle() {
  display.clearDisplay();
  for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 5) {
    display.drawTriangle(
      display.width()/2, display.height()/2 - i,
      display.width()/2 - i, display.height()/2 + i,
      display.width()/2 + i, display.height()/2 + i,
      WHITE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testfilltriangle() {
  display.clearDisplay();
  for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 5) {
    display.fillTriangle(
      display.width()/2, display.height()/2 - i,
      display.width()/2 - i, display.height()/2 + i,
      display.width()/2 + i, display.height()/2 + i,
      INVERSE);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testdrawchar() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.cp437(true);
  for (int16_t i = 0; i < 256; i++) {
    if (i == '\n') display.write(' ');
    else           display.write(i);
    display.display();
    delay(1);
  }
  delay(2000);
}

void testdrawstyles() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Hello, world!"));
  display.setTextColor(BLACK, WHITE);
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
}

void testscrolltext() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();
  delay(100);
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void testdrawbitmap() {
  display.clearDisplay();
  display.drawBitmap(
    (display.width() - LOGO_WIDTH) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT,
    WHITE);
  display.display();
  delay(1000);
}

#define XPOS   0
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t  icons[NUMFLAKES][3];
  // Initialize
  for (int8_t f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - w, display.width());
    icons[f][YPOS]   = -h;
    icons[f][DELTAY] = random(1, 6);
  }
  // Loop forever
  for (;;) {
    display.clearDisplay();
    for (int8_t f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
      icons[f][YPOS] += icons[f][DELTAY];
      if (icons[f][YPOS] >= display.height()) {
        icons[f][XPOS]   = random(1 - w, display.width());
        icons[f][YPOS]   = -h;
        icons[f][DELTAY] = random(1, 6);
      }
    }
    display.display();
    delay(200);
  }
}
