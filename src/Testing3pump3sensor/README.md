````markdown
# 🧪 STM32 Pump Control System (Pump 3 + Sensor 3 Debug Version)

This project is a standalone STM32 (Arduino-style) sketch that controls Pump 3 using Flow Sensor 3 with dynamic, volume-based calibration and serial command interface for precise liquid dispensing.

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

| Volume Range (mL) | Calibration Index | Default Factor |
|------------------:|------------------:|----------------|
| 0–50              | 0                 | 18.00          |
| 51–100            | 1                 | 23.00          |
| 101–150           | 2                 | 30.00          |
| 151–1000          | 3                 | 50.00          |

You can override these values live via serial commands.

---

## 🖥️ Serial Commands
🛑 ALL PUMPS OFF
⚙️ Pump 2 ON - Target: 100 mL | Cal: 5.20
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/100 mL
📏 Pulses: 88 | Flow: 16.9 mL/s | Total: 16.9/100 mL
📏 Pulses: 170 | Flow: 32.7 mL/s | Total: 32.7/100 mL
📏 Pulses: 240 | Flow: 46.2 mL/s | Total: 46.2/100 mL
📏 Pulses: 316 | Flow: 60.8 mL/s | Total: 60.8/100 mL
📏 Pulses: 412 | Flow: 79.2 mL/s | Total: 79.2/100 mL
🚑 Pump 2 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 2 ON - Target: 100 mL | Cal: 5.20
📏 Pulses: 2 | Flow: 0.0 mL/s | Total: 0.0/100 mL
📏 Pulses: 88 | Flow: 16.9 mL/s | Total: 16.9/100 mL
📏 Pulses: 192 | Flow: 36.9 mL/s | Total: 36.9/100 mL
📏 Pulses: 257 | Flow: 49.4 mL/s | Total: 49.4/100 mL
📏 Pulses: 333 | Flow: 64.0 mL/s | Total: 64.0/100 mL
📏 Pulses: 443 | Flow: 85.2 mL/s | Total: 85.2/100 mL
🚑 Pump 2 OFF

### 🧪 Dispense Command

```text
D3:<volume>
D3:<volume>:<cal>@<range>
````

*  D3:100  – Dispenses 100 mL using the default calibration for 51–100 mL range.
*  D3:100:11.5\@1  – Sets range 1 calibration to 11.5, then dispenses 100 mL.
*  D3:150:30\@2  – Sets range 2 calibration to 30.0, then dispenses 150 mL.

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
| Pump 1        | `PB7` |
| Flow Sensor 1 | `PA2` |

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

*  Filename:  `pump2_debug.ino` (can be renamed as needed)
*  Platform:  STM32 (Arduino Core or STM32duino)
*  Dependencies:  None

---

## 👨‍🔧 Author

Written by Yan Naing Kyaw Tint
Documentation compiled by ChatGPT

---


