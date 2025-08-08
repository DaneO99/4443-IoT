# Lab 4: Tetris Game with ST7796S TFT Display

## Overview
This lab creates a fully functional Tetris game using a large ST7796S TFT display and joystick controls. The game features a colorful interface, scoring system, level progression, and smooth gameplay on a 320x480 pixel display.

## Hardware Setup

### ✅ Components Used
- **Arduino Uno R4 WiFi**
- **ST7796S TFT LCD Display** (320x480 pixels, 3.5" or 4.0")
- **Analog Joystick Module**

### ✅ Wiring Instructions

**ST7796S TFT Display (SPI Connection):**
| TFT Pin | Arduino Uno Pin |
|---------|------------------|
| VCC     | 5V              |
| GND     | GND             |
| CS      | Pin 10          |
| DC      | Pin 9           |
| MOSI    | Pin 11          |
| SCK     | Pin 13          |
| RST     | Pin 8           |
| MISO    | Pin 12          |
| LED     | 3.3V            |

**Analog Joystick Module:**
| Joystick Pin | Arduino Uno Pin |
|--------------|-----------------|
| VCC          | 5V              |
| GND          | GND             |
| VRx (X-axis) | A1              |
| VRy (Y-axis) | A0              |
| SW (Button)  | Digital Pin 2   |

### Game Controls
- **Left/Right**: Move joystick horizontally to move pieces left/right
- **Down**: Push joystick down for quick drop (soft drop)
- **Button Press**: Restart game when game over

**Note**: This version does not include piece rotation - simplified controls for better gameplay flow.

## Software Requirements

### ✅ Arduino IDE Libraries Required

Install these libraries through Arduino IDE Library Manager:

1. **TFT_eSPI** - Main display driver library
2. **SPI** - Serial Peripheral Interface (usually pre-installed)

### Configuration Steps
1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for and install "TFT_eSPI" library
4. Configure the TFT_eSPI library for ST7796S in the User_Setup.h file

### TFT_eSPI Configuration
The TFT_eSPI library requires configuration for the ST7796S display. Ensure these settings in User_Setup.h:
```cpp
#define ST7796_DRIVER
#define TFT_WIDTH  320
#define TFT_HEIGHT 480
```

## Game Features

### ✅ Visual Features
- **Full Color Display**: 320x480 pixel high-resolution gameplay
- **Colorful Tetrominoes**: Each piece type has distinct colors (red, yellow, orange, green, blue, pink, cyan)
- **Block Outlines**: Clear visual separation between blocks
- **Large Playfield**: 10x15 grid optimized for the larger screen
- **Real-time HUD**: Live score and level display

### ✅ Gameplay Features
- **Scoring System**: 100 points per completed line
- **Progressive Difficulty**: Speed increases by 15% per level (every 500 points)
- **Automatic Drop**: Pieces fall automatically with decreasing intervals
- **Collision Detection**: Accurate piece placement and boundary checking
- **Line Clearing**: Full rows disappear with proper animations
- **Game Over Detection**: Automatic restart with button press

## Technical Implementation

### ✅ Display Configuration
- **Portrait Mode**: 320x480 resolution (rotated for optimal Tetris gameplay)
- **Block Size**: Dynamic scaling (32x32 pixels per Tetris block)
- **Color Depth**: 16-bit color (65,536 colors)
- **Refresh Rate**: Optimized for smooth 30+ FPS gameplay

### ✅ Performance Optimizations
- **Efficient Rendering**: Only redraws changed areas
- **SPI Communication**: Fast data transfer to display
- **Minimal Delays**: Responsive controls with 30ms loop timing
- **Memory Management**: Efficient grid storage and piece handling

## Possible Upgrades

1. **Piece Rotation**: Add up joystick movement for piece rotation
2. **Enhanced Graphics**: Add animated line-clearing effects or particle systems
3. **Sound Effects**: Add buzzer for audio feedback
4. **Touch Screen**: Implement touch controls for mobile-like experience
5. **High Score Memory**: Store best scores in EEPROM
6. **Custom Tetrominoes**: Create special pieces with unique abilities
7. **Multiplayer Mode**: Connect two setups for competitive play
8. **Background Graphics**: Add animated backgrounds or themes
9. **Statistics Tracking**: Track pieces played, lines cleared, time played
10. **Wireless Features**: Use Arduino R4 WiFi for online leaderboards

## Files

- **Tetris_SSD1306_JoystickFix/Tetris_SSD1306_JoystickFix.ino** - Main Tetris game sketch for ST7796S display
- **IMG_3664.MOV** - Video demonstration of completed project setup and gameplay

## Technical Notes

- The sketch filename contains "SSD1306" for historical reasons, but the code is specifically designed for ST7796S TFT displays
- Display must be configured in portrait mode (rotation 1) for proper Tetris gameplay
- Joystick sensitivity is calibrated for smooth piece movement without over-triggering
- Color palette is optimized for good contrast and visual appeal on TFT displays
