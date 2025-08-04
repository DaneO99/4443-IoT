# Lab 6: Weather API with Arduino

## Overview
This lab creates a weather display system that fetches real-time weather data from OpenWeatherMap API and displays it on Arduino when an RFID tag is scanned.

## ⚠️ IMPORTANT: Execution Order

**You MUST follow this exact sequence:**

1. **Upload Arduino Code First** - Upload your Arduino sketch and verify RFID scanning works
2. **CLOSE Arduino IDE** - This frees up the serial port (critical step!)
3. **Run Python Script** - Execute the Python weather bridge script

**Failure to close Arduino IDE will result in "Port busy" errors!**

## Hardware Setup

### ✅ Wiring Instructions

**RFID Reader Module:**
| RFID Pin | Arduino Uno Pin |
|----------|-----------------|
| VCC      | 3.3V            |
| GND      | GND             |
| SDA      | Pin 10          |
| SCK      | Pin 13          |
| MOSI     | Pin 11          |
| MISO     | Pin 12          |
| RST      | Pin 9           |

**LCD Display (Optional for weather display):**
| LCD Pin | Arduino Uno Pin |
|---------|-----------------|
| VCC     | 5V              |
| GND     | GND             |
| SDA     | A4              |
| SCL     | A5              |

## Software Requirements

### ✅ Arduino IDE Libraries
- **MFRC522** library for RFID functionality

### ✅ Python Requirements
Install these Python packages:
```bash
pip3 install pyserial requests
```

## System Flow

1. **Arduino waits for RFID scan**
2. **Tag detected** → Sends "TAG:" message via serial
3. **Python script receives tag notification**
4. **Fetches weather data** from OpenWeatherMap API
5. **Sends location and weather** back to Arduino
6. **Arduino displays weather information**

## Configuration

### API Key Setup
Edit the Python script to include your OpenWeatherMap API key:
```python
API_KEY = "your_api_key_here"
```

### Serial Port Configuration
Update the serial port in the Python script for your system:
- **macOS**: `/dev/tty.usbmodem...`
- **Windows**: `COM3`, `COM4`, etc.
- **Linux**: `/dev/ttyUSB0`, `/dev/ttyACM0`, etc.

## Possible Upgrades

1. **Weather Icons**: Add OLED display with graphical weather icons
2. **Forecast Display**: Show 5-day weather forecast
3. **Database Logging**: Store weather history in SQLite database
4. **Web Dashboard**: Create web interface to view weather data
5. **Multiple Locations**: Assign different locations to different RFID tags
6. **Alert System**: Send notifications for severe weather conditions
7. **Sensor Integration**: Combine with local sensors for comparison
8. **Voice Announcements**: Add text-to-speech for weather reports
9. **Mobile App**: Create smartphone app to control and view data
10. **Data Visualization**: Generate weather trend graphs and charts
11. **IoT Integration**: Connect to home automation systems
12. **Backup APIs**: Use multiple weather services for redundancy

## Troubleshooting

**Common Issues:**
- **Port busy error**: Make sure Arduino IDE is completely closed
- **No RFID response**: Check wiring and tag proximity
- **API errors**: Verify API key and internet connection
- **Serial timeout**: Ensure correct baud rate (115200) and port

## Files

- **Arduino sketch** - RFID reader and weather display code
- **weather_to_arduino.py** - Python weather API bridge
- **city.list.json.gz** - City database (auto-downloaded)
- **IMG_3558.MOV** - Video demonstration
- **IMG_3633.JPG** - Project photo

## Technical Notes

- Python script auto-downloads city list on first run
- Uses Nominatim API for reverse geocoding (county lookup)
- Implements random city selection for demonstration
- Serial communication at 115200 baud rate
- Includes error handling for network timeouts
