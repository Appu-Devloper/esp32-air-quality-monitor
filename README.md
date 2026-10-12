# ESP32 Air Quality Monitor

A low-cost, IoT-based air quality and weather monitoring system built with an **ESP32**, **MQ135** gas sensor, **DHT22** temperature/humidity sensor, a **0.96" OLED display**, and a **ThingSpeak** cloud dashboard.

Readings are shown locally on the OLED and can also be sent to the cloud for remote monitoring and trend analysis.

![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![IDE](https://img.shields.io/badge/IDE-Arduino-00979D)
![Cloud](https://img.shields.io/badge/cloud-ThingSpeak-green)

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Components Required](#components-required)
- [Circuit Connections](#circuit-connections)
- [How It Works](#how-it-works)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Cloud Dashboard Setup](#cloud-dashboard-setup)
- [Configuration](#configuration)
- [Uploading the Code](#uploading-the-code)
- [Air Quality Status](#air-quality-status)
- [Applications](#applications)
- [Advantages](#advantages)
- [Limitations](#limitations)
- [Future Improvements](#future-improvements)
- [Repository Structure](#repository-structure)
- [Conclusion](#conclusion)

---

## Overview

Air pollution and changing environmental conditions can affect human health, indoor comfort, and workplace safety. Traditional air quality monitoring systems are often expensive and may not suit small-scale applications.

This project offers a simple, affordable alternative using easily available electronic components. It monitors air quality, temperature, and humidity in real time.

## Features

- Real-time air quality monitoring using the MQ135 gas sensor
- Temperature and humidity measurement using the DHT22 sensor
- Live data display on an OLED screen
- Wi-Fi connectivity using ESP32
- Cloud dashboard support for remote monitoring
- Graph-based visualization of historical data
- Air quality status indication: **Good**, **Moderate**, or **Poor**
- Expandable design for adding more environmental sensors

## Components Required

| Component | Quantity | Purpose |
|---|---|---|
| ESP32 Development Board | 1 | Main controller and Wi-Fi module |
| MQ135 Gas Sensor | 1 | Air quality sensing |
| DHT22 Sensor | 1 | Temperature and humidity sensing |
| OLED Display 0.96" I2C | 1 | Local display output |
| Breadboard | 1 | Circuit assembly |
| Jumper Wires | As required | Connections |
| USB Cable | 1 | Programming and power |

## Circuit Connections

| Module | Module Pin | ESP32 Pin |
|---|---|---|
| MQ135 | AO | GPIO34 |
| DHT22 | DATA | GPIO4 |
| OLED Display | SDA | GPIO21 |
| OLED Display | SCL | GPIO22 |
| All Modules | VCC | 3.3V or 5V |
| All Modules | GND | GND |

> **Note:** Check the voltage rating of your sensor modules before connecting VCC. Some modules support 5V, while others work best with 3.3V. ESP32 GPIO pins accept a maximum of 3.3V, so if your MQ135 module is powered at 5V, make sure its analog output is within the 3.3V range (for example, by using a voltage divider).

A wiring diagram is available in [`circuit_diagram.png`](circuit_diagram.png).

## How It Works

1. The MQ135 sensor detects changes in air-quality-related gas concentration.
2. The DHT22 sensor measures temperature and humidity.
3. The ESP32 reads and processes the sensor values.
4. The OLED display shows the live readings.
5. The ESP32 sends the readings to a cloud dashboard over Wi-Fi.
6. The dashboard displays current and historical data using graphs.
7. Users can observe environmental changes and identify unhealthy conditions.

## Software Requirements

- Arduino IDE
- ESP32 board package for Arduino IDE
- DHT sensor library
- Adafruit SSD1306 library
- Adafruit GFX library
- ThingSpeak library

## Installation

### 1. Install the ESP32 board package

1. Open Arduino IDE.
2. Go to **File > Preferences**.
3. Add the following URL to **Additional Boards Manager URLs**:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to **Tools > Board > Boards Manager**.
5. Search for **ESP32** and install it.

### 2. Install the libraries

Open **Library Manager** in Arduino IDE and install:

- `DHT sensor library`
- `Adafruit SSD1306`
- `Adafruit GFX Library`
- `ThingSpeak`

## Cloud Dashboard Setup

This project uses [ThingSpeak](https://thingspeak.com) for cloud monitoring.

Create a ThingSpeak channel with these fields:

| Field | Data |
|---|---|
| Field 1 | Air Quality Value |
| Field 2 | Temperature |
| Field 3 | Humidity |

After creating the channel, copy your **Channel ID** and **Write API Key**.

## Configuration

Update these values in `esp32_air_quality_monitor.ino`:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

unsigned long channelID = YOUR_CHANNEL_ID;
const char* writeAPIKey = "YOUR_WRITE_API_KEY";
```

> **Tip:** Never commit your real Wi-Fi password or Write API Key to a public repository.

## Uploading the Code

1. Open `esp32_air_quality_monitor.ino` in Arduino IDE.
2. Select your ESP32 board from **Tools > Board**.
3. Select the correct port from **Tools > Port**.
4. Enter your Wi-Fi name, Wi-Fi password, ThingSpeak Channel ID, and Write API Key.
5. Click **Upload**.
6. Open the Serial Monitor at **115200 baud** to view sensor readings.

## Air Quality Status

The MQ135 sensor provides an analog value. In this project, the value is classified as follows:

| MQ135 Value | Status |
|---|---|
| Less than 1000 | Good |
| 1000 to 1999 | Moderate |
| 2000 and above | Poor |

> These thresholds are for demonstration purposes. For accurate AQI or PPM measurement, the MQ135 sensor must be properly calibrated.

## Applications

- Indoor air quality monitoring
- Classroom environment monitoring
- Laboratory monitoring
- Small workplace safety monitoring
- Home weather and air quality tracking
- IoT mini project or academic project

## Advantages

- Low-cost implementation
- Easy to build and understand
- Real-time local and remote monitoring
- Uses commonly available components
- Suitable for beginners and students
- Can be expanded with more sensors

## Limitations

- MQ135 needs calibration for accurate gas concentration measurement
- Readings may change based on sensor quality and environmental conditions
- An internet connection is required for cloud dashboard updates
- Not a replacement for certified industrial air quality monitoring equipment

## Future Improvements

- [ ] Add a buzzer alert for poor air quality
- [ ] Add mobile app notifications
- [ ] Add a PM2.5, CO2, or pressure sensor
- [ ] Store data in a custom database
- [ ] Add battery power support
- [ ] Control an exhaust fan automatically based on air quality
- [ ] Add a web dashboard hosted on a local server

## Repository Structure

```
esp32-air-quality-monitor/
├── esp32_air_quality_monitor.ino
├── README.md
└── circuit_diagram.png
```

## Conclusion

This ESP32-based air quality and weather monitoring system provides a simple and affordable way to monitor environmental conditions in real time. It is well suited to academic demonstrations, IoT learning, and basic indoor environment monitoring.
