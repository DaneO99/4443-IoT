# Lab 5: Temperature and Humidity Display

## Overview
This lab demonstrates environmental monitoring using a DHT11 sensor to read temperature and humidity, displaying the data on an I2C LCD screen.

## Hardware Setup

### ✅ Wiring Instructions

**DHT11 Temperature & Humidity Sensor:**
| DHT11 Pin | Arduino Uno Pin |
|-----------|-----------------|
| VCC       | 3.3V or 5V     |
| Data      | Digital Pin 2   |
| GND       | GND             |

**I2C LCD Display (16x2):**
| LCD Pin | Arduino Uno Pin |
|---------|-----------------|
| VCC     | 5V              |
| GND     | GND             |
| SDA     | A4              |
| SCL     | A5              |

### Display Format
- **Line 1**: Temperature in Fahrenheit
- **Line 2**: Humidity percentage
- **Error Handling**: Shows "Sensor Error" if readings fail

## Software Requirements

### ✅ Arduino IDE Libraries Required

Install these libraries through Arduino IDE Library Manager:

1. **DHT sensor library** by Adafruit
2. **LiquidCrystal I2C** by Frank de Brabander
3. **Wire** (usually pre-installed)

### Installation Steps
1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for and install each library listed above

## Sensor Specifications

**DHT11 Specifications:**
- Temperature range: 0-50°C (32-122°F)
- Humidity range: 20-90% RH
- Accuracy: ±2°C, ±5% RH
- Reading interval: 2 seconds minimum

## Possible Upgrades

1. **DHT22 Upgrade**: Use DHT22 for higher precision (±0.5°C, ±2% RH)
2. **Data Logging**: Store readings to SD card with timestamps
3. **Threshold Alerts**: Add LEDs or buzzer for temperature/humidity warnings
4. **Bar Graph Display**: Show readings as visual bar graphs on LCD
5. **Wireless Monitoring**: Send data via WiFi to web dashboard
6. **Multi-Sensor Setup**: Monitor multiple rooms with sensor arrays
7. **Heat Index Calculation**: Calculate and display apparent temperature
8. **Trend Analysis**: Show rising/falling arrows for temperature trends
9. **Min/Max Tracking**: Track daily/weekly minimum and maximum values
10. **Mobile App**: Create smartphone app to view readings remotely
11. **Web Server**: Host readings on local web server for browser access
12. **Database Integration**: Send data to cloud database for long-term analysis

## Technical Notes

- DHT11 requires 1-2 second delays between readings
- I2C address 0x27 is common for LCD modules (may vary)
- Use pullup resistor (10kΩ) on DHT11 data line if needed
- Sensor needs brief warm-up time for accurate readings

## Files

- **sketch_jul20a.ino** - Main temperature/humidity monitoring sketch
