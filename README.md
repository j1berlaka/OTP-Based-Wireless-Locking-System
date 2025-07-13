# OTP-Based Smart Wireless Locking System

This project presents a low-cost, wireless smart locking system based on OTP (One-Time Password) verification using an Arduino UNO and GSM module. It provides secure access control by sending a time-sensitive OTP to a registered mobile number and allowing access only when the correct OTP is entered on a keypad.

##  Overview

Traditional locking systems are prone to duplication and unauthorized access. This system enhances security by:
- Generating a unique OTP on each access attempt
- Sending the OTP via SMS using the SIM800L GSM module
- Verifying the OTP input via a keypad
- Controlling a solenoid door lock through a relay

The solution is ideal for homes, offices, and restricted areas where GSM connectivity is available.

##  Features

- Motion detection using IR sensor
- Automatic OTP generation and SMS delivery
- OTP input via 4x4 matrix keypad
- Access feedback via 16×2 I2C LCD display
- Relay-controlled solenoid locking
- Auto-locking after a time delay
- Power stability with capacitor filtering

##  Hardware Used

| Component                   | Quantity | Description                                |
|----------------------------|----------|--------------------------------------------|
| Arduino Uno                | 1        | Microcontroller board                       |
| SIM800L GSM Module         | 1        | SMS-based OTP delivery                      |
| IR Sensor                  | 1        | Motion detection                            |
| 4x4 Keypad                 | 1        | User OTP input                              |
| 16×2 LCD Display (I2C)     | 1        | User interface display                      |
| 5V Relay Module            | 1        | Controls solenoid lock                      |
| Solenoid Lock              | 1        | Door locking mechanism                      |
| Capacitor (3300µF)         | 1        | Power filtering                             |
| 12V Adapter                | 1        | Power supply                                |
| Breadboard + Jumper Wires | -        | Circuit prototyping                         |

##  Working Principle

1. **Motion Detection**: IR sensor detects presence → triggers system.
2. **OTP Generation**: Arduino generates a random 4-digit OTP.
3. **OTP Delivery**: GSM module sends OTP via SMS to the user.
4. **User Input**: User enters OTP via the keypad.
5. **Verification**: Arduino compares input with generated OTP.
6. **Lock Control**: Relay activates → unlocks solenoid lock if OTP is correct.
7. **Auto Reset**: System re-locks after a delay and waits for next trigger.

##  Future Scope

- Mobile app-based OTP delivery (via Bluetooth or Wi-Fi)
- Integration with biometric authentication (fingerprint or face detection)
- AI-powered camera to prevent false OTP triggers
- Cloud logging and access history


## 👩‍💻 Authors

- Ganga Krishna A (SCT22EC061)
- Gawtham Choodan A V (SCT22EC062)
- Karthik Pramodh (SCT22EC076)
- Meenakshi H L (SCT22EC081)

> Submitted in partial fulfillment for the degree of **Bachelor of Technology in Electronics and Communication Engineering**, Sree Chitra Thirunal College of Engineering, under **APJ Abdul Kalam Technological University**, April 2025.

---

## 📞 Contact

For queries, contact [gautamchoodan2003@gmail.com] or create an issue in this repository.

---

