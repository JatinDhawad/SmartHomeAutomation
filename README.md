![GitHub repo size](https://img.shields.io/github/repo-size/JatinDhawad/SmartHomeAutomation)
![GitHub stars](https://img.shields.io/github/stars/JatinDhawad/SmartHomeAutomation?style=social)
![GitHub last commit](https://img.shields.io/github/last-commit/JatinDhawad/SmartHomeAutomation)

# 🏠 Smart Home Automation using Arduino & Blynk IoT

A safety-oriented IoT system that detects **gas leaks, fire, motion, and obstacles**, 
and automatically responds using alarms, lights, and servo mechanisms.  
The system sends live data to the **Blynk Cloud** for real-time mobile monitoring.

---

## ⚙️ Features
- 🔥 Fire Detection  
- 💨 Gas Leak Detection (MQ Sensor)  
- 🚶 Motion & Intruder Detection (IR Sensor)  
- 📏 Ultrasonic Obstacle Detection  
- 🧲 Automatic Window/Door Servo Control  
- 🆘 Panic Button Mode for emergencies  
- 📲 Live IoT Dashboard using **Blynk App**

---

## 🧠 Working Principle
1. **Arduino UNO** collects data from sensors and makes local safety decisions.  
2. Sensor readings are transmitted via serial to the **ESP8266 WiFi Module**.  
3. The ESP8266 connects to **Blynk Cloud**, uploading data for mobile viewing.  
4. Users can view all real-time readings (Gas, Fire, Motion, Distance, Panic) in the app.

---

## 🔧 Hardware Components
| Component | Function |
|------------|-----------|
| Arduino UNO | Main controller for sensors & actuators |
| ESP8266 (NodeMCU) | Sends data to the Blynk Cloud |
| MQ Gas Sensor | Detects harmful gases |
| Flame Sensor | Detects fire or smoke |
| IR Motion Sensor | Detects human movement |
| Ultrasonic Sensor | Measures distance/obstacles |
| Servo Motor | Opens/closes window or door |
| Relay Module | Controls appliances/lights |
| Buzzer & LED | Audible and visual alerts |
| Panic Button | Emergency trigger |

---

## 📱 Blynk Dashboard Mapping
| Virtual Pin | Sensor/Value | Description |
|--------------|---------------|-------------|
| V0 | Gas Sensor | Analog gas reading |
| V1 | Flame Sensor | 1 = Fire detected |
| V2 | Motion Sensor | 1 = Movement detected |
| V3 | Ultrasonic | Distance in cm |
| V4 | Panic Button | 1 = Panic triggered |

---

## 🌐 IoT Integration Diagram
[Sensors] → [Arduino UNO] → (Serial) → [ESP8266 Wi-Fi] → [Blynk Cloud] → [Mobile App]

---

## 🧩 Future Enhancements
- Add **voice control** using Google Assistant  
- Integrate **Firebase** or **ThingSpeak** for data logging  
- Include **ESP32-CAM** for image capture on hazard  
- Send **SMS/email alerts** using IFTTT  

---


## 👨‍💻 Developed By
**Jatin Dhawad**  
*(Microprocessor and Microcontroller Subject Project)*  
