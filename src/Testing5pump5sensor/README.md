# 🧪 STM32 Pump Control System (Pump 5 + Sensor 5 Debug Version)

This project is a standalone STM32 (Arduino-style) sketch that controls  Pump 5 using Flow  Sensor 5 with dynamic, volume-based calibration and serial command interface for precise liquid dispensing.

---

## 🚀 Features

✅  Single Pump + Sensor Debug Mode   
✅  Pulse-based flow detection  using interrupts  
✅  Volume-based calibration logic  (4 ranges: 0–50, 51–100, 101–150, 151–1000 mL)  
✅  Live calibration override  via serial command  
✅  Flow timeout protection   
✅  Real-time serial debug output   

---

## 🧠 Calibration Logic

The program dynamically selects a calibration factor based on the target volume:
s
| Volume Range (mL) | Calibration Index | Default Factor |
|------------------:|------------------:|----------------|
| 0–50              | 0                 | 18.00          |
| 51–100            | 1                 | 23.00          |
| 101–150           | 2                 | 30.00          |
| 151–1000          | 3                 | 50.00          |

You can override these values live via serial commands.

---

## 🖥️ Serial Commands

```Serial Command
🔧 Calibration updated: Range1 → 12.50
⚙️ Pump 5 ON - Target: 100 mL | Cal: 12.50
📏 Pulses: 11 | Flow: 0.9 mL/s | Total: 0.9/100 mL
📏 Pulses: 203 | Flow: 16.2 mL/s | Total: 16.2/100 mL
📏 Pulses: 382 | Flow: 30.6 mL/s | Total: 30.6/100 mL
📏 Pulses: 573 | Flow: 45.8 mL/s | Total: 45.8/100 mL
📏 Pulses: 791 | Flow: 63.3 mL/s | Total: 63.3/100 mL
📏 Pulses: 1007 | Flow: 80.6 mL/s | Total: 80.6/100 mL
📏 Pulses: 1205 | Flow: 96.4 mL/s | Total: 96.4/100 mL
🚑 Pump 5 OFF
🌟 Target reached!
📊 Current Calibration:
0-50mL: 7.60
51-100mL: 12.50
101-150mL: 10.00
151-1000mL: 10.00
🛑 ALL PUMPS OFF
⚙️ Pump 5 ON - Target: 25 mL | Cal: 7.60
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/25 mL
🚑 Pump 5 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 5 ON - Target: 50 mL | Cal: 7.60
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 173 | Flow: 22.8 mL/s | Total: 22.8/50 mL
📏 Pulses: 372 | Flow: 48.9 mL/s | Total: 48.9/50 mL
🚑 Pump 5 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 5 ON - Target: 50 mL | Cal: 7.60
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 185 | Flow: 24.3 mL/s | Total: 24.3/50 mL
📏 Pulses: 332 | Flow: 43.7 mL/s | Total: 43.7/50 mL
🚑 Pump 5 OFF
🌟 Target reached!
📊 Current Calibration:
0-50mL: 7.60
51-100mL: 12.50
101-150mL: 10.00
151-1000mL: 10.00
```

### 🧪 Dispense Command

```text
D5:<volume>
D5:<volume>:<cal>@<range>
````

*  D5:100  – Dispenses 100 mL using the default calibration for 51–100 mL range.
*  D5:100:11.5\@1  – Sets range 1 calibration to 11.5, then dispenses 100 mL.
*  D5:150: 40\@2  – Sets range 2 calibration to  40.0, then dispenses 150 mL.

### ⚙️ Calibration Only

```text
R:<range>:<cal>
```

*  R:1:25.5  – Updates range 1 (51–100 mL) to calibration factor 25.5.

### 📊 Show Current Calibration

```text
C
```

* Prints all 4 calibration factors.

### 🛑 Emergency Stop

```text
S
```

* Immediately stops the pump and detaches interrupt.

---

## 🧰 Hardware Setup

| Component     | Pin   |
| ------------- | ----- |
| Pump 5       | `PB5` |
| Flow Sensor 5 | `PA4` |

* `pumpPin` uses digital HIGH/LOW to control pump power.
* `sensorPin` is connected to the flow sensor's pulse output.
* Ensure pull-up or pull-down is correct for your sensor model.

---

## 🔄 Pump Operation

1. Upon receiving a `D1` command, calibration factor is selected.
2. Pump is turned ON and sensor pulses are counted via interrupt.
3. Flow = `pulses / calFactor`
4. Real-time updates are printed every 1 second.
5. Pump turns OFF when:

   * Target volume is reached
   * No pulses are received for 2 seconds (timeout)

---

## 🛡️ Safety Mechanism

* If  no pulses are detected for 2 seconds , the pump automatically shuts off to prevent over-dispensing.
* `S` command is always available to stop manually.

---

## 🧪 Example Output

```
⚙️ Pump ON - Target: 100 mL | Cal: 23.00
📟 Pulses: 543 | Flow: 19.2 mL/s | Total: 54.3/100.0 mL
📟 Pulses: 1001 | Flow: 19.0 mL/s | Total: 100.2/100.0 mL
🛑 Pump OFF
🎯 Target reached!
```

---

## 📌 Notes

* This code is written for debugging a single pump/sensor pair.
* Pulse interrupt logic is efficient enough for real-time flow detection on STM32.
* Future enhancements can include EEPROM save/load, multi-pump support, or GUI integration.

---

## 📁 File Info

*  Filename:  `pump5_debug.ino` (can be renamed as needed)
*  Platform:  STM32 (Arduino Core or STM32duino)
*  Dependencies:  None

---

## 👨‍🔧 Author

Written by Yan Naing Kyaw Tint
Documentation compiled by ChatGPT

---


