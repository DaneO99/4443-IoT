# Lab 4: Tetris Game with OLED Display

## Overview
This lab creates a fully functional Tetris game using an OLED display and joystick controls. Features include scoring, level progression, and sound feedback.

## Hardware Setup

### ✅ Wiring Instructions

**OLED Display (SSD1306 128x64):**
| OLED Pin | Arduino Uno Pin |
|----------|-----------------|
| VCC      | 3.3V or 5V     |
| GND      | GND             |
| SDA      | A4              |
| SCL      | A5              |

**Analog Joystick Module:**
| Joystick Pin | Arduino Uno Pin |
|--------------|-----------------|
| VCC          | 5V              |
| GND          | GND             |
| VRx (X-axis) | A0              |
| VRy (Y-axis) | A1              |
| SW (Button)  | Digital Pin 2   |

**Buzzer:**
| Buzzer Pin | Arduino Uno Pin |
|------------|-----------------|
| Positive   | Digital Pin 3   |
| Negative   | GND             |

### Game Controls
- **Left/Right**: Move joystick horizontally
- **Down**: Push joystick down (soft drop)
- **Up**: Push joystick up (rotate piece)
- **Button Press**: Hard drop (instant drop to bottom)

## Software Requirements

### ✅ Arduino IDE Libraries Required

Install these libraries through Arduino IDE Library Manager:

1. **Adafruit GFX Library**
2. **Adafruit SSD1306**
3. **Wire** (usually pre-installed)

### Installation Steps
1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for and install each library listed above

## Game Features

- **Scoring System**: 100 points per completed line
- **Level Progression**: Speed increases every 200 points
- **Next Piece Preview**: Shows upcoming tetromino
- **Sound Effects**: Different tones for moves, rotations, and line clears
- **Game Over Detection**: Automatic restart option

## Possible Upgrades

1. **Enhanced Graphics**: Add animated line-clearing effects or particle systems
2. **Multiplayer Mode**: Connect two setups for competitive play
3. **High Score Memory**: Store high scores in EEPROM
4. **Custom Tetrominoes**: Create special pieces with unique abilities
5. **Music Player**: Add background music using tone sequences
6. **Wireless Competition**: Use ESP32/ESP8266 for online multiplayer
7. **LED Matrix**: Replace OLED with larger LED matrix display
8. **Gesture Controls**: Use accelerometer instead of joystick
9. **Touch Screen**: Implement touch controls for mobile-like experience
10. **Statistics Tracking**: Track pieces played, lines cleared, time played

## Files

- **Tetris_SSD1306_JoystickFix.ino** - Main Tetris game sketch
- **IMG_3557.JPG** - Photo of completed project setup
