#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2        // DHT11 connected to digital pin 2
#define DHTTYPE DHT11   // Define sensor type

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27 is common

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop() {
  delay(2000);  // DHT11 needs 1-2 seconds between reads
  
  float tempF = dht.readTemperature(true);  // 'true' returns Fahrenheit
  float hum = dht.readHumidity();
  
  lcd.clear();
  if (isnan(tempF) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(tempF);
    lcd.print(" F");

    lcd.setCursor(0, 1);
    lcd.print("Humi: ");
    lcd.print(hum);
    lcd.print(" %");
  }
}
