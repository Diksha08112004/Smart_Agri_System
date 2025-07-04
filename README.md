# Smart_Agri_System
# Smart Soil Moisture Monitoring and Pump Control System 🌱

This Arduino + Blynk-based project monitors soil moisture from two sensors and automatically controls two water pumps. It also reads temperature and humidity using a DHT11 sensor and pushes all data to the Blynk IoT app in real-time.

## 🔧 Hardware Used

- ESP32
- DHT11 Sensor
- Soil Moisture Sensors x2
- Relay Module x2
- Water Pumps
- Blynk IoT Platform

## 📲 Features

- Monitor real-time soil moisture of two plants
- Automatic pump control based on threshold
- Remote view of data on Blynk app
- Temperature and humidity monitoring
- Manual override using Blynk buttons (V3 & V4)

## 🧠 How It Works

- Reads analog values from moisture sensors
- Sends data to Blynk virtual pins V1, V2, V5 (Temp), and V6 (Humidity)
- Turns ON pumps via relay if soil is dry (below 3000)
- Sends ON/OFF state to Blynk via V3 and V4

## 📱 Blynk Setup

- Create a template on [Blynk](https://blynk.cloud)
- Add 2 Gauges (V1, V2), 2 Buttons (V3, V4), and 2 Labels (V5, V6)
- Paste your `BLYNK_TEMPLATE_ID`, `BLYNK_AUTH_TOKEN` into the code

## ⚙️ Setup

1. Install libraries:
   - `Blynk` (v1 or Blynk IoT)
   - `DHT sensor library`
   - `Adafruit Unified Sensor`

2. Flash code to ESP32 via Arduino IDE

## 📸 Preview

*Coming soon: Circuit diagram*

## 📄 License

MIT
