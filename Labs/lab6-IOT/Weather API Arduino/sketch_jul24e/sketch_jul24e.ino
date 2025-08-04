#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

#define RFID_SS_PIN        10
#define RFID_RST_PIN       9
#define LED_PIN            6
#define LED_COUNT          8
#define DEFAULT_BRIGHTNESS 100

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(RFID_SS_PIN, RFID_RST_PIN);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

String getTagUID() {
  String uid;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) uid += "0";
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();
  return uid;
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize RFID reader
  SPI.begin();
  mfrc522.PCD_Init();

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Initialize NeoPixel strip
  strip.begin();
  strip.setBrightness(DEFAULT_BRIGHTNESS);
  strip.show();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan a tag...");
}

void loop() {
  // 1) RFID scan → send TAG:<UID>
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String uid = getTagUID();
    Serial.print("TAG:");
    Serial.println(uid);
    // Wait until tag is removed
    while (mfrc522.PICC_IsNewCardPresent()) delay(50);
  }

  // 2) Handle incoming Serial commands
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();

    // Location update: LOC:City,County,State or LOC:City,Country
    if (line.startsWith("LOC:")) {
      String body = line.substring(4);
      int c1 = body.indexOf(',');
      int c2 = body.indexOf(',', c1 + 1);

      String city   = body.substring(0, c1);
      String middle = (c2 > 0) ? body.substring(c1 + 1, c2) : "";
      String last   = (c2 > 0) ? body.substring(c2 + 1) : body.substring(c1 + 1);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(city);
      lcd.print(",");
      lcd.print(last);
      if (middle.length()) {
        lcd.setCursor(0, 1);
        lcd.print(middle);
      }
    }

    // Temperature update: TMP:temp,description
    else if (line.startsWith("TMP:")) {
      String body = line.substring(4);
      int comma = body.indexOf(',');
      float temp = body.substring(0, comma).toFloat();
      String cond = body.substring(comma + 1);

      // Set NeoPixel color based on temperature
      uint32_t color;
      if (temp < 40)      color = strip.Color(0, 0, 255);
      else if (temp < 70) color = strip.Color(0, 255, 0);
      else if (temp < 90) color = strip.Color(255, 255, 0);
      else                color = strip.Color(255, 0, 0);

      for (int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, color);
      }
      strip.show();

      // Display temperature and condition on second line only
      lcd.setCursor(0, 1);
      lcd.print("                ");  // clear second line
      lcd.setCursor(0, 1);
      lcd.print(temp, 1);
      lcd.print("F ");
      lcd.print(cond.substring(0, 14)); // adjust length as needed
    }
  }
}
