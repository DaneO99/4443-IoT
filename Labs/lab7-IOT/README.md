# Lab 7: Reaction Timer Game

## Overview
This lab creates a competitive two-player reaction timer game using WS2812B LED strips, LCD display, and push buttons. Players compete to react fastest to the "GO!" signal.

## Hardware Setup

### ✅ Wiring Instructions

**WS2812B LED Strip:**
| LED Strip Pin | Arduino Uno Pin |
|---------------|-----------------|
| VCC (+5V)     | 5V              |
| GND           | GND             |
| Data Input    | Digital Pin 6   |

**I2C LCD Display (16x2):**
| LCD Pin | Arduino Uno Pin |
|---------|-----------------|
| VCC     | 5V              |
| GND     | GND             |
| SDA     | A4              |
| SCL     | A5              |

**Player Buttons:**
| Button    | Arduino Uno Pin |
|-----------|-----------------|
| Player 1  | Digital Pin 2   |
| Player 2  | Digital Pin 3   |

**Buzzer:**
| Buzzer Pin | Arduino Uno Pin |
|------------|-----------------|
| Positive   | Digital Pin 4   |
| Negative   | GND             |

### Game Sequence Colors
- **Red**: Get Ready phase
- **Yellow**: Get Set phase  
- **Green**: GO! signal
- **Blue**: Player 1 winner animation
- **Purple**: Player 2 winner animation

## Software Requirements

### ✅ Arduino IDE Libraries Required

Install these libraries through Arduino IDE Library Manager:

1. **Adafruit NeoPixel** - For WS2812B LED control
2. **LiquidCrystal I2C** - For LCD display
3. **Wire** (usually pre-installed)

### Installation Steps
1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries…**
3. Search for and install each library listed above

## Game Flow

1. **Startup**: Press any button to begin
2. **Get Ready**: Red LEDs, first warning beep
3. **Get Set**: Yellow LEDs, second warning beep  
4. **Random Delay**: 1-5 seconds of suspense
5. **GO Signal**: Green LEDs + beep
6. **Reaction Measurement**: Timer starts
7. **Results Display**: Show both reaction times
8. **Winner Announcement**: Animated celebration
9. **Auto Restart**: Return to startup screen

## Game Features

- **False Start Detection**: Penalty for reacting before GO signal
- **Precision Timing**: Millisecond accuracy with 3-decimal display
- **Visual Feedback**: Full LED strip color changes
- **Audio Cues**: Different tones for each game phase
- **Winner Animations**: Unique celebrations for each player
- **Tie Detection**: Special handling for identical times

## Possible Upgrades

1. **Multi-Round Tournaments**: Best of 3/5/7 scoring system
2. **Statistics Tracking**: Store reaction time history in EEPROM
3. **Difficulty Modes**: Shorter/longer random delays
4. **Team Mode**: 4+ players with team competitions
5. **Web Dashboard**: Upload scores to online leaderboard
6. **Mobile App**: Control game and view statistics remotely
7. **Voice Announcements**: Text-to-speech for player names and results
8. **Custom Sound Effects**: SD card with game sounds and music
9. **Gesture Controls**: Replace buttons with motion sensors
10. **LED Matrix Display**: Show countdown numbers visually
11. **Wireless Competition**: Connect multiple units for tournaments
12. **Professional Timer**: Hundredth of second accuracy with better timing
13. **Tournament Bracket**: Multi-player elimination system
14. **Achievement System**: Unlock rewards for consistent performance

## Technical Specifications

- **Timing Resolution**: 1 millisecond
- **Random Delay Range**: 1000-5000ms (1-5 seconds)
- **LED Count**: 8 WS2812B LEDs (expandable)
- **Display**: 16x2 character LCD
- **Audio**: Passive buzzer with multiple tones

## Troubleshooting

**Common Issues:**
- **LEDs not working**: Check data pin connection and power supply
- **Buttons not responsive**: Verify wiring and ensure no floating pins
- **LCD blank**: Check I2C connections and address (usually 0x27)
- **No sound**: Verify buzzer polarity and pin connection
- **Timing inaccurate**: Avoid delays in main loop, use millis() timing

## Safety Notes

- **LED Power**: WS2812B strips can draw significant current - ensure adequate power supply
- **Button Debouncing**: Built-in delays prevent false triggering
- **Eye Safety**: LEDs can be bright - consider diffusion for comfort

## Files

- **reaction.ino** - Main reaction timer game sketch
- **IMG_3391.MOV** - Video demonstration of gameplay

## Technical Notes

- Uses `millis()` for precise timing measurements
- Implements state machine for clean game flow control
- LED animations use color wiping and flashing effects
- Built-in false start detection with penalty display
- Automatic game reset for continuous play
