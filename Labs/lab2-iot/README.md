# Lab 2: Distance Sensor with LEDs

## Overview
This lab demonstrates using an HC-SR04 ultrasonic distance sensor to control LED zones based on proximity. The closer an object gets, the more LED zones light up.

## Hardware Setup

### ✅ Wiring Instructions

**HC-SR04 Ultrasonic Sensor:**
| HC-SR04 Pin | Arduino Uno Pin |
|-------------|----------------|
| VCC         | 5V             |
| GND         | GND            |
| Trig        | Digital Pin 7  |
| Echo        | Digital Pin 8  |

**LEDs (with appropriate resistors):**
| LED Color | Arduino Pins |
|-----------|-------------|
| Green     | Pins 3, 5   |
| Yellow    | Pins 6, 9   |
| Red       | Pins 10, 11 |

### Distance Zones
- **> 30cm**: Only green LEDs on (safe zone)
- **15-30cm**: Green + yellow LEDs on (caution zone)
- **< 15cm**: All LEDs on (danger zone)

## Software Requirements

### ✅ No additional libraries required
This project uses only built-in Arduino functions.

## Possible Upgrades

1. **Audio Feedback**: Add a buzzer to provide different tones for each distance zone
2. **PWM Effects**: Use PWM to create fading or pulsing LED effects
3. **LCD Display**: Add an LCD to show exact distance measurements
4. **Adjustable Thresholds**: Use potentiometers to adjust distance thresholds in real-time
5. **Data Logging**: Log distance readings to SD card for analysis
6. **Wireless Transmission**: Send distance data via Bluetooth or WiFi

## Files

- **lab2-iot.ino** - Arduino sketch for distance sensor with LED control


