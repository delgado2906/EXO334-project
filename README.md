# Voice-Controlled Home Automation System

A DIY embedded systems project that enables hands-free control of household appliances — a fan, a coffee maker, and room lights — using voice commands processed locally, with infrared remote as a secondary input method.

---

## Overview

This project integrates an AI-thinker VC02 voice recognition module with an ESP32-C3 and an Arduino Nano to create a distributed home automation system. Voice commands are recognized locally (no cloud required), decoded, and transmitted wirelessly via Bluetooth between two microcontrollers located in different spaces of a room. Actuators are triggered through relay modules and servo motors depending on the appliance.

The system architecture separates concerns cleanly: the ESP32-C3 handles voice processing and light control, while the Arduino Nano manages higher-power appliances (fan and coffee maker) via relay, and also accepts input from an IR remote as an alternative control method.

---

## Project Goals

- **Simplify daily routines** — Control common appliances without needing to physically reach for switches, ideal for moments when your hands are full or you're settled in bed
- **Enable accessible control** — Provide a voice-first interface that can benefit people with limited mobility
- **Keep processing local** — No internet dependency, no latency from cloud services, complete privacy
- **Demonstrate practical embedded systems design** — Show how two microcontrollers can coordinate over Bluetooth to control distributed hardware in different areas of a room
- **Build a foundation for home automation** — Create an extensible base that can grow into a broader smart home system

---

## Core Features

- **Voice command recognition** via the AI-Thinker VC02 module, processed entirely on-device
- **Bluetooth communication** between ESP32-C3 and Arduino Nano for cross-room coordination
- **Fan control** via relay module, toggled by voice command or IR remote
- **Coffee maker control** via relay module, toggled by voice command or IR remote
- **Light control** via servo motor that physically actuates a wall switch, controlled by the ESP32-C3
- **Dual input methods** — voice commands take priority, with an IR remote as a backup/alternative
- **Relay-based switching** for safe control of AC-powered appliances

---

## Hardware Components

| Component | Role |
|---|---|
| AI-Thinker VC02 Module | Local voice recognition and command output |
| ESP32-C3 | Voice data streaming, Bluetooth master, light control |
| Arduino Nano | Bluetooth receiver, fan & coffee maker control, IR decoding |
| Bluetooth module | Attached to the Arduino nano to receive de ESP-32 C3 data |
| IR Receiver | Receives signals from infrared remote control |
| Relay Module | Switches fan and coffee maker on/off safely |
| Servo Motor(s) | Physically actuates light switches |

---

## System Architecture

The system is split into two subsystems that communicate over Bluetooth:

**ESP32-C3 side (light zone)**
- Receives voice command data from the VC02 module
- Decodes the command and branches into two paths:
  - *Light control* → activates a servo motor to toggle the light switch
  - *Fan & coffee maker control* → transmits the command via Bluetooth to the Arduino Nano

**Arduino Nano side (appliance zone)**
- Receives Bluetooth data from the ESP32-C3
- Also accepts input from an IR receiver as an alternative trigger
- Decodes the incoming signal and activates the appropriate relay channel (fan or coffee maker)

> See `docs/architecture.png` for the full system diagram.

---

## Expandability

This project is designed with growth in mind. Potential expansions include:

- **Additional appliances** — Any relay-switched or servo-actuated device can be added with minimal changes to the command decoding logic
- **More voice commands** — The VC02 module supports custom command sets that can be extended
- **Multiple rooms** — Additional Arduino Nano nodes can be added as Bluetooth receivers for other areas
- **Mobile app integration** — The ESP32-C3's Wi-Fi capability could be used to add a smartphone control interface alongside voice
- **Scheduling** — Adding an RTC module to either microcontroller would enable time-based automation (e.g., start the coffee maker at 7:00 AM)
- **Sensor feedback** — Temperature or occupancy sensors could trigger appliances automatically

---

## Future Improvements & Applications

- **State feedback display** — A small OLED screen showing the current state of each appliance
- **Confirmation audio output** — A buzzer or speaker giving audio acknowledgment after a command is recognized
- **Wake word sensitivity tuning** — Fine-tuning the VC02 recognition threshold to reduce false triggers
- **Persistent state memory** — Saving appliance states to EEPROM so the system remembers settings after a power cycle
- **Broader applications** — This architecture can be adapted for accessibility devices, workshop tool control, or small office automation with minimal hardware changes

---

## Repository Structure

```
├── esp32_firmware/       # Code for the ESP32-C3 (voice decoding, BT master, light control)
├── arduino_firmware/     # Code for the Arduino Nano (BT receiver, relay & IR control)
├── docs/
│   └── architecture.png  # System architecture diagram
└── README.md
```

---

## Getting Started

> Detailed setup instructions coming soon.

1. Flash `esp32_firmware/` to the ESP32-C3 using the Arduino IDE or PlatformIO
2. Flash `arduino_firmware/` to the Arduino Nano
3. Pair the two devices over Bluetooth
4. Wire the relay module and servo motors according to the schematic in `docs/`
5. Power on and test with the default voice commands defined in the VC02 configuration

---

## License

This project is open source. Feel free to use, modify, and build upon it.
