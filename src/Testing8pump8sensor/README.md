# STM32 Pump 8 Time-Based Dispenser

This program controls **Pump 8** of a 9-pump STM32 water dispensing system. Unlike the others, Pump 8's **flow sensor pin is faulty** and cannot detect pulses. To overcome this hardware limitation, the system uses a **time-based approach** to simulate water volume dispensing.

---

## 💡 Why Time-Based?

Pump 8's designated flow sensor (PA7) does **not respond or register any pulses** due to hardware failure (wiring issue, dead pin, etc.). Instead of discarding the pump, this program **estimates the dispensed volume by timing how long the pump is active**.

Empirical tests showed:

- **50 mL** is dispensed in ~6.236 seconds  
- **100 mL** is dispensed in ~12.208 seconds  
- **150 mL** is dispensed in ~18.4 seconds  

These durations are **hardcoded** for accurate, consistent operation without a sensor.

---

## 🚀 How It Works

This is a standalone program for **Pump 8 only**. It runs the pump for a preset number of seconds based on the command input.

### ⌨️ Serial Commands

| Command        | Description                                 |
|----------------|---------------------------------------------|
| `D8:50`        | Dispense 50 mL (≈6.236 seconds)             |
| `D8:100`       | Dispense 100 mL (≈12.208 seconds)           |
| `D8:150`       | Dispense 150 mL (≈18.4 seconds)             |
| `S`            | Stop the pump immediately                   |
| `C`            | Print a simulated calibration table (fake)  |

> Note: Input like `D8:50:12.3@1` is accepted, but **the duration and calibration values are ignored**.

---

## 📊 Fake Calibration Table

Even though there is no real calibration in use, the `C` command prints a simulated output to match the other pump systems:

```

📊 Current Calibration:
0-50mL: 4.10
51-100mL: 3.12
101-150mL: 5.18
151-1000mL: 5.56

````

This helps keep the GUI/UX consistent.

---

## 🧪 Example Output

```text
⚙️ Pump 8 ON - Target: 50 mL | Duration: 6.236 seconds
📏 Time-Based | Elapsed: 1.00s / 6.24s
📏 Time-Based | Elapsed: 2.00s / 6.24s
🌟 Target time reached!
🚑 Pump OFF
````

---

## 🔧 Hardware Notes

* **Pump Pin**: `PA15`
* **Flow Sensor Pin**: `PA7` (not used in this program)
* System runs on **STM32 (Arduino-compatible core)**
* Compatible with PlatformIO or Arduino IDE

---

## 📁 File Structure

```bash
Pump8_Time_Faker/
├── src/
│   └── main.cpp          # This program
├── README.md             # This file
├── platformio.ini        # (if using PlatformIO)
```

---

## 📌 Summary

This program is a **graceful fallback** to extend functionality to hardware with limited capability. Pump 8 now works reliably using **time as a proxy for volume**, making it useful in production or testing.
