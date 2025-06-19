# 🧪 STM32 Pump Control System (Pump 6 + Sensor  6 Debug Version)

This project is a standalone STM32 (Arduino-style) sketch that controls  Pump 6 using Flow  Sensor  6 with dynamic, volume-based calibration and serial command interface for precise liquid dispensing.

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

``` Serial Command
🔧 Calibration updated: Range0 → 4.10
🛑 ALL PUMPS OFF
⚙️ Pump 6 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 74 | Flow: 18.0 mL/s | Total: 18.0/50 mL
📏 Pulses: 156 | Flow: 38.0 mL/s | Total: 38.0/50 mL
🚑 Pump 6 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 6 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 71 | Flow: 17.3 mL/s | Total: 17.3/50 mL
📏 Pulses: 150 | Flow: 36.6 mL/s | Total: 36.6/50 mL
🚑 Pump 6 OFF
🌟 Target reached!

⚙️ Pump 6 ON - Target: 100 mL | Cal: 4.70
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/100 mL
📏 Pulses: 25 | Flow: 5.3 mL/s | Total: 5.3/100 mL
📏 Pulses: 102 | Flow: 21.7 mL/s | Total: 21.7/100 mL
📏 Pulses: 179 | Flow: 38.1 mL/s | Total: 38.1/100 mL
📏 Pulses: 252 | Flow: 53.6 mL/s | Total: 53.6/100 mL
📏 Pulses: 329 | Flow: 70.0 mL/s | Total: 70.0/100 mL
📏 Pulses: 406 | Flow: 86.4 mL/s | Total: 86.4/100 mL
🚑 Pump 6 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 6 ON - Target: 100 mL | Cal: 4.70
📏 Pulses: 252 | Flow: 53.6 mL/s | Total: 53.6/100 mL
📏 Pulses: 329 | Flow: 70.0 mL/s | Total: 70.0/100 mL
📏 Pulses: 406 | Flow: 86.4 mL/s | Total: 86.4/100 mL
🚑 Pump 6 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 6 ON - Target: 100 mL | Cal: 4.70
📏 Pulses: 1 | Flow: 0.0 mL/s | Total: 0.0/100 mL
⚙️ Pump 6 ON - Target: 100 mL | Cal: 4.70
📏 Pulses: 1 | Flow: 0.0 mL/s | Total: 0.0/100 mL
📏 Pulses: 1 | Flow: 0.0 mL/s | Total: 0.0/100 mL
📏 Pulses: 66 | Flow: 14.0 mL/s | Total: 14.0/100 mL
📏 Pulses: 139 | Flow: 29.6 mL/s | Total: 29.6/100 mL
📏 Pulses: 212 | Flow: 45.1 mL/s | Total: 45.1/100 mL
📏 Pulses: 288 | Flow: 61.3 mL/s | Total: 61.3/100 mL
📏 Pulses: 365 | Flow: 77.7 mL/s | Total: 77.7/100 mL
📏 Pulses: 444 | Flow: 94.5 mL/s | Total: 94.5/100 mL
🚑 Pump 6 OFF
🌟 Target reached!






📏 Pulses: 66 | Flow: 14.0 mL/s | Total: 14.0/100 mL
📏 Pulses: 139 | Flow: 29.6 mL/s | Total: 29.6/100 mL
📏 Pulses: 212 | Flow: 45.1 mL/s | Total: 45.1/100 mL
📏 Pulses: 288 | Flow: 61.3 mL/s | Total: 61.3/100 mL
📏 Pulses: 365 | Flow: 77.7 mL/s | Total: 77.7/100 mL
📏 Pulses: 444 | Flow: 94.5 mL/s | Total: 94.5/100 mL
🚑 Pump 6 OFF
🌟 Target reached!




📏 Pulses: 66 | Flow: 14.0 mL/s | Total: 14.0/100 mL
📏 Pulses: 139 | Flow: 29.6 mL/s | Total: 29.6/100 mL
📏 Pulses: 212 | Flow: 45.1 mL/s | Total: 45.1/100 mL
📏 Pulses: 288 | Flow: 61.3 mL/s | Total: 61.3/100 mL
📏 Pulses: 365 | Flow: 77.7 mL/s | Total: 77.7/100 mL
📏 Pulses: 444 | Flow: 94.5 mL/s | Total: 94.5/100 mL
🚑 Pump 6 OFF
🌟 Target reached!


📏 Pulses: 66 | Flow: 14.0 mL/s | Total: 14.0/100 mL
📏 Pulses: 139 | Flow: 29.6 mL/s | Total: 29.6/100 mL
📏 Pulses: 212 | Flow: 45.1 mL/s | Total: 45.1/100 mL
📏 Pulses: 288 | Flow: 61.3 mL/s | Total: 61.3/100 mL
📏 Pulses: 365 | Flow: 77.7 mL/s | Total: 77.7/100 mL
📏 Pulses: 444 | Flow: 94.5 mL/s | Total: 94.5/100 mL
🚑 Pump 6 OFF
📏 Pulses: 66 | Flow: 14.0 mL/s | Total: 14.0/100 mL
📏 Pulses: 139 | Flow: 29.6 mL/s | Total: 29.6/100 mL
📏 Pulses: 212 | Flow: 45.1 mL/s | Total: 45.1/100 mL
📏 Pulses: 66 | Flow: 14.0 mL/s | Total: 14.0/100 mL
📏 Pulses: 66 | Flow: 14.0 mL/s | Total: 14.0/100 mL
📏 Pulses: 139 | Flow: 29.6 mL/s | Total: 29.6/100 mL
📏 Pulses: 212 | Flow: 45.1 mL/s | Total: 45.1/100 mL
📏 Pulses: 288 | Flow: 61.3 mL/s | Total: 61.3/100 mL
📏 Pulses: 365 | Flow: 77.7 mL/s | Total: 77.7/100 mL
📏 Pulses: 444 | Flow: 94.5 mL/s | Total: 94.5/100 mL
🚑 Pump 6 OFF
🌟 Target reached!

```

### 🧪 Dispense Command

```text
D6:<volume>
D6:<volume>:<cal>@<range>
````

*  D6:100  – Dispenses 100 mL using the default calibration for 51–100 mL range.
*  D6:100:11.5\@1  – Sets range 1 calibration to 11.5, then dispenses 100 mL.
*  D6:150: 40\@2  – Sets range 2 calibration to  40.0, then dispenses 150 mL.

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
| Pump 6       | `PB4` |
| Flow Sensor  6 | `PA5` |

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

*  Filename:  `pump6_debug.ino` (can be renamed as needed)
*  Platform:  STM32 (Arduino Core or STM32duino)
*  Dependencies:  None

---

## 👨‍🔧 Author

Written by Yan Naing Kyaw Tint
Documentation compiled by ChatGPT

---


