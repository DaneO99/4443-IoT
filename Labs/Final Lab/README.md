# Final Lab: Snake Game with Touch Screen Controls

## Overview
This final lab project creates a classic Snake game using a touchscreen display with swipe gesture controls. The game features smooth movement, score tracking, and an intuitive touch interface that responds to swipe gestures for directional control.

## Hardware Setup

### ✅ Components Used
- **ESP32 or Arduino with TFT Display**
- **TFT LCD Touchscreen Display** (480x320 resolution)
- **XPT2046 Touch Controller**

### ✅ Wiring Instructions

**TFT Touchscreen Display:**
| Display Pin | ESP32/Arduino Pin |
|-------------|-------------------|
| VCC         | 3.3V              |
| GND         | GND               |
| CS          | Pin 15            |
| DC          | Pin 2             |
| MOSI        | Pin 23            |
| SCK         | Pin 18            |
| BLK         | Pin 4             |
| MISO        | Pin 19            |
| T_CLK       | Pin 18            |
| T_CS        | Pin 9             |
| T_DIN       | Pin 23            |
| T_OUT       | Pin 19            |
| T_IRQ       | Not connected     |

## Software Requirements

### ✅ Arduino IDE Libraries Required

Install these libraries through Arduino IDE Library Manager:

1. **TFT_eSPI** - For display control
2. **XPT2046_Touchscreen** - For touch input handling
3. **SPI** - For communication (usually pre-installed)

### Installation Steps
1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for and install each library listed above
4. Configure TFT_eSPI library for your specific display in User_Setup.h

## Game Features

### ✅ Core Gameplay
- **Classic Snake Game**: Eat food to grow longer and increase score
- **Swipe Controls**: Use finger swipes on touchscreen to control snake direction
- **Collision Detection**: Game ends when snake hits walls or itself
- **Score System**: Points awarded for each food item consumed
- **Auto-restart**: Touch screen after game over to restart

### ✅ Technical Features
- **Optimized Rendering**: Efficient partial screen updates for smooth gameplay
- **Touch Calibration**: Mapped touch coordinates for accurate input detection
- **Swipe Recognition**: Advanced swipe detection with distance and time thresholds
- **Direction Validation**: Prevents snake from immediately reversing into itself
- **Real-time Display**: Live score display during gameplay

### Game Controls
- **Swipe Up**: Move snake upward
- **Swipe Down**: Move snake downward  
- **Swipe Left**: Move snake left
- **Swipe Right**: Move snake right
- **Touch (Game Over)**: Restart the game

## Game Configuration

### ✅ Adjustable Parameters
- **Grid Size**: 20x20 pixel cells for clear visibility
- **Snake Speed**: 300ms movement interval
- **Swipe Sensitivity**: 30-pixel minimum swipe distance
- **Swipe Timing**: 300ms maximum swipe duration
- **Screen Resolution**: 480x320 optimized display

## Files

- **snakegame.ino** - Main Snake game sketch with swipe controls
- **IMG_3803.MOV** - Video demonstration of the completed project
- **Screen and Joystick Module.3mf** - 3D model file for custom housing/mount

## Possible Future Enhancements

1. **Multiple Difficulty Levels**: Adjustable snake speed settings
2. **High Score Memory**: Store best scores in EEPROM
3. **Sound Effects**: Add audio feedback for food consumption and game over
4. **Enhanced Graphics**: Add animations and visual effects
5. **Multiplayer Mode**: Two-player snake game on same screen
6. **Power Management**: Sleep mode when inactive
7. **Custom Themes**: Different color schemes and visual styles
8. **Food Variations**: Special food types with bonus points
9. **Obstacles**: Add walls and barriers for increased difficulty
10. **Statistics**: Track games played, average score, longest snake

## Technical Notes

- Touch screen calibration values may need adjustment based on specific hardware
- The game uses efficient partial redraws to maintain smooth 60+ FPS gameplay  
- Swipe detection algorithm filters out accidental touches and ensures intentional input
- Serial monitor provides debugging output for touch coordinates and swipe detection

## Project Demonstration

See the included video file `IMG_3803.MOV` for a complete demonstration of the game in action, including swipe gesture controls and gameplay mechanics.
