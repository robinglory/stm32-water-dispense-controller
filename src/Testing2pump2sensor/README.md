````

# 💧 STM32 Pump 2 Water Dispensing System (Pulse-Based with Dynamic Calibration)

This project is a debug and test implementation of a water dispensing system using **Pump 2** and **Sensor 2** of a larger 9-pump STM32-based system. It demonstrates real-time pulse-counting from a flow sensor, dynamic calibration based on volume ranges, and serial command control.

## 🚀 Features

- Controls **Pump 2** connected to `PB8`, reads pulses from **Sensor 2** on `PA1`.
- Dispenses water based on a **target volume (in mL)**.
- Uses **dynamic calibration factors** for four volume ranges:
  - 0–50 mL
  - 51–100 mL
  - 101–150 mL
  - 151–1000 mL
- Serial command interface for:
  - Starting a dispense
  - Setting calibration values
  - Stopping pumps
  - Viewing current calibration settings
- Real-time logging: shows pulse count, current flow, and total volume.
- **Timeout safety**: automatically stops if no pulses are received within 2 seconds.

## 🧪 Hardware Setup

- **Pump 2** control pin: `PB8`
- **Flow Sensor 2** input pin: `PA1` (using `INPUT_PULLUP`)
- All pump pins are declared to ensure full shutdown:
  ```cpp
  const int allPumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
````

## 🛠️ Calibration

The system uses different calibration values depending on the target volume:

| Volume Range (mL) | Calibration Factor Index |
| ----------------- | ------------------------ |
| 0–50              | 0                        |
| 51–100            | 1                        |
| 101–150           | 2                        |
| 151–1000          | 3                        |

To dispense accurately, calibration factors must be tuned based on real pulse data from each volume range.

## 💬 Serial Commands

| Command Format     | Description                                                       |
| ------------------ | ----------------------------------------------------------------- |
| `D2:<volume>`      | Dispense specified volume using current calibration               |
| `D2:<v>:<cal>@<r>` | Dispense `<v>` mL using calibration `<cal>` for range `<r>` (0–3) |
| `D4:<r>:<cal>`     | Set calibration factor `<cal>` for range `<r>` only               |
| `C`                | Show current calibration values                                   |
| `S`                | Stop all pumps immediately                                        |

### Example:

```bash
D2:100:11.5@1   # Set calibration 11.5 for range 1 (51–100 mL) and dispense 100 mL
D4:2:9.2        # Set calibration 9.2 for range 2 (101–150 mL)
C               # Display all current calibration values
S               # Emergency stop
```

## 🧠 How It Works

* Each flow sensor pulse increments `pulseCount` via an interrupt.
* A calibration factor determines how many pulses per mL.
* When the calculated `dispensedVolume` reaches `targetVolume`, the pump is stopped.
* If no pulses are detected for 2 seconds, the pump is automatically stopped for safety.

## 📦 Dependencies

* STM32 core for Arduino (use STM32Cube or STM32duino for uploading)
* Serial terminal (e.g., Arduino Serial Monitor or PuTTY) at `9600 baud`

## 🧯 Safety Notes

* Make sure pumps and MOSFET drivers are wired correctly.
* Ensure the sensor gives pulses; otherwise, timeout will occur.
* Always use the `S` command to stop the system in emergencies.

## 📌 Status

✅ Fully functional for **Pump 2 / Sensor 2** debug
🔧 Extendable to other pumps with similar logic

---



