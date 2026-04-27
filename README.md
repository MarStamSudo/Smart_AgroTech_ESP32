# Smart_AgroTech_ESP32
A professional-grade IoT weather station for precision agriculture using ESP32, BME388, and SHT40. Featuring dual-sensor redundancy and real-time HTTP telemetry.
# 🛰️ Obsidian Agro-Node V1.0

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-orange.svg)

**Obsidian Agro-Node** is an advanced IoT solution designed for precision agriculture. It monitors critical environmental parameters in real-time, helping farmers prevent crop diseases and optimize resource management.

## 🚀 Key Features
- **Dual-Sensor Redundancy:** Intelligent switching between BME280 (Primary) and DHT22 (Fallback).
- **Auto-Calibration:** Built-in temperature and humidity offsets for high accuracy.
- **Smart Telemetry:** Real-time data transmission via HTTP POST to a centralized SQL server.
- **Robust Error Handling:** Automatic recovery from sensor failure or network disconnection.
- **Edge Intelligence:** Designed to implement agrometeorological models (Frost alert, Disease prediction).

## 🛠️ Hardware Requirements
- **Microcontroller:** ESP32 (WROOM-32)
- **Sensors:** - Bosch BME280 (Temperature, Humidity, Pressure)
  - DHT22 (Temperature, Humidity)
- **Connectivity:** WiFi (LTE/SIM7000G support coming soon)

## 📁 Project Structure
- `/src`: Main firmware source code (`.ino`).
- `config.h.example`: Template for network and API credentials.
- `README.md`: Project documentation.

## 🔧 Installation & Setup
1. Clone this repository.
2. Create a `config.h` file based on `config.h.example`.
3. Update your WiFi credentials and API Key.
4. Flash the code using Arduino IDE or PlatformIO.

## 📈 Roadmap
- [ ] Integration with SIM7000G for LTE-M/NB-IoT connectivity.
- [ ] Implementation of Deep Sleep for solar power optimization.
- [ ] AI-driven frost and pest prediction algorithms.

---
**Author:** Marinos (Computer Science & Telecommunications Student)
**Vision:** Building the future of autonomous agriculture.
