# 🧪 STM32 Pump Control System (Pump 7 + Sensor  7 Debug Version)

This project is a standalone STM32 (Arduino-style) sketch that controls **Pump 7** using **Flow Sensor  7** with dynamic, volume-based calibration and serial command interface for precise liquid dispensing.

---

## 🚀 Features

✅ **Single Pump + Sensor Debug Mode**  
✅ **Pulse-based flow detection** using interrupts  
✅ **Volume-based calibration logic** (4 ranges: 0–50, 51–100, 101–150, 151–1000 mL)  
✅ **Live calibration override** via serial command  
✅ **Flow timeout protection**  
✅ **Real-time serial debug output**  

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
```
📊 Current Calibration:
0-50mL: 4.10
51-100mL: 4.70
101-150mL: 5.18
151-1000mL: 5.56
🛑 ALL PUMPS OFF
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 3 | Flow: 0.7 mL/s | Total: 0.7/50 mL
📏 Pulses: 45 | Flow: 11.0 mL/s | Total: 11.0/50 mL
📏 Pulses: 108 | Flow: 26.3 mL/s | Total: 26.3/50 mL
📏 Pulses: 173 | Flow: 42.2 mL/s | Total: 42.2/50 mL
🚑 Pump 7 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 53 | Flow: 12.9 mL/s | Total: 12.9/50 mL
📏 Pulses: 124 | Flow: 30.2 mL/s | Total: 30.2/50 mL
📏 Pulses: 203 | Flow: 49.5 mL/s | Total: 49.5/50 mL
🚑 Pump 7 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 56 | Flow: 13.7 mL/s | Total: 13.7/50 mL
📏 Pulses: 116 | Flow: 28.3 mL/s | Total: 28.3/50 mL
📏 Pulses: 178 | Flow: 43.4 mL/s | Total: 43.4/50 mL
🚑 Pump 7 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 100 mL | Cal: 4.70
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/100 mL
📏 Pulses: 50 | Flow: 10.6 mL/s | Total: 10.6/100 mL
📏 Pulses: 105 | Flow: 22.3 mL/s | Total: 22.3/100 mL
📏 Pulses: 159 | Flow: 33.8 mL/s | Total: 33.8/100 mL
📏 Pulses: 212 | Flow: 45.1 mL/s | Total: 45.1/100 mL
📏 Pulses: 267 | Flow: 56.8 mL/s | Total: 56.8/100 mL
📏 Pulses: 325 | Flow: 69.1 mL/s | Total: 69.1/100 mL
📏 Pulses: 379 | Flow: 80.6 mL/s | Total: 80.6/100 mL
📏 Pulses: 437 | Flow: 93.0 mL/s | Total: 93.0/100 mL
🚑 Pump 7 OFF
🌟 Target reached!
🔧 Calibration updated: Range1 → 3.12
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 100 mL | Cal: 3.12
📏 Pulses: 1 | Flow: 0.0 mL/s | Total: 0.0/100 mL
📏 Pulses: 46 | Flow: 14.7 mL/s | Total: 14.7/100 mL
📏 Pulses: 100 | Flow: 32.1 mL/s | Total: 32.1/100 mL
📏 Pulses: 154 | Flow: 49.4 mL/s | Total: 49.4/100 mL
📏 Pulses: 209 | Flow: 67.0 mL/s | Total: 67.0/100 mL
📏 Pulses: 263 | Flow: 84.3 mL/s | Total: 84.3/100 mL
🚑 Pump 7 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 100 mL | Cal: 3.12
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/100 mL
📏 Pulses: 29 | Flow: 9.3 mL/s | Total: 9.3/100 mL
📏 Pulses: 83 | Flow: 26.6 mL/s | Total: 26.6/100 mL
📏 Pulses: 136 | Flow: 43.6 mL/s | Total: 43.6/100 mL
📏 Pulses: 190 | Flow: 60.9 mL/s | Total: 60.9/100 mL
📏 Pulses: 243 | Flow: 77.9 mL/s | Total: 77.9/100 mL
📏 Pulses: 296 | Flow: 94.9 mL/s | Total: 94.9/100 mL
🚑 Pump 7 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 16 | Flow: 3.9 mL/s | Total: 3.9/50 mL
📏 Pulses: 63 | Flow: 15.4 mL/s | Total: 15.4/50 mL
⚙️ Pump 7 ON - Target: 100 mL | Cal: 3.12
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/100 mL
📏 Pulses: 29 | Flow: 9.3 mL/s | Total: 9.3/100 mL
📏 Pulses: 83 | Flow: 26.6 mL/s | Total: 26.6/100 mL
📏 Pulses: 136 | Flow: 43.6 mL/s | Total: 43.6/100 mL
📏 Pulses: 190 | Flow: 60.9 mL/s | Total: 60.9/100 mL
📏 Pulses: 243 | Flow: 77.9 mL/s | Total: 77.9/100 mL
📏 Pulses: 296 | Flow: 94.9 mL/s | Total: 94.9/100 mL
🚑 Pump 7 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 16 | Flow: 3.9 mL/s | Total: 3.9/50 mL
📏 Pulses: 63 | Flow: 15.4 mL/s | Total: 15.4/50 mL
📏 Pulses: 136 | Flow: 43.6 mL/s | Total: 43.6/100 mL
📏 Pulses: 190 | Flow: 60.9 mL/s | Total: 60.9/100 mL
📏 Pulses: 243 | Flow: 77.9 mL/s | Total: 77.9/100 mL
📏 Pulses: 296 | Flow: 94.9 mL/s | Total: 94.9/100 mL
🚑 Pump 7 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 16 | Flow: 3.9 mL/s | Total: 3.9/50 mL
📏 Pulses: 63 | Flow: 15.4 mL/s | Total: 15.4/50 mL
📏 Pulses: 296 | Flow: 94.9 mL/s | Total: 94.9/100 mL
🚑 Pump 7 OFF
🌟 Target reached!
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 16 | Flow: 3.9 mL/s | Total: 3.9/50 mL
📏 Pulses: 63 | Flow: 15.4 mL/s | Total: 15.4/50 mL
🛑 ALL PUMPS OFF
⚙️ Pump 7 ON - Target: 50 mL | Cal: 4.10
📏 Pulses: 0 | Flow: 0.0 mL/s | Total: 0.0/50 mL
📏 Pulses: 16 | Flow: 3.9 mL/s | Total: 3.9/50 mL
📏 Pulses: 63 | Flow: 15.4 mL/s | Total: 15.4/50 mL
📏 Pulses: 16 | Flow: 3.9 mL/s | Total: 3.9/50 mL
📏 Pulses: 63 | Flow: 15.4 mL/s | Total: 15.4/50 mL
📏 Pulses: 115 | Flow: 28.0 mL/s | Total: 28.0/50 mL
📏 Pulses: 168 | Flow: 41.0 mL/s | Total: 41.0/50 mL
🚑 Pump 7 OFF
🌟 Target reached!
📊 Current Calibration:
0-50mL: 4.10
51-100mL: 3.12
101-150mL: 5.18
151-1000mL: 5.56
```

### 🧪 Dispense Command

```text
D7:<volume>
D7:<volume>:<cal>@<range>
````

* **D7:100** – Dispenses 100 mL using the default calibration for 51–100 mL range.
* **D7:100:11.5\@1** – Sets range 1 calibration to 11.5, then dispenses 100 mL.
* **D7:150:30\@2** – Sets range 2 calibration to 30.0, then dispenses 150 mL.

### ⚙️ Calibration Only

```text
R:<range>:<cal>
```

* **R:1:25.5** – Updates range 1 (51–100 mL) to calibration factor 25.5.

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
| Pump 7        | `PB9` |
| Flow Sensor  7 | `PA0` |

* `pumpPin` uses digital HIGH/LOW to control pump power.
* `sensorPin` is connected to the flow sensor's pulse output.
* Ensure pull-up or pull-down is correct for your sensor model.

---

## 🔄 Pump Operation

1. Upon receiving a `D7` command, calibration factor is selected.
2. Pump is turned ON and sensor pulses are counted via interrupt.
3. Flow = `pulses / calFactor`
4. Real-time updates are printed every 1 second.
5. Pump turns OFF when:

   * Target volume is reached
   * No pulses are received for 2 seconds (timeout)

---

## 🛡️ Safety Mechanism

* If **no pulses are detected for 2 seconds**, the pump automatically shuts off to prevent over-dispensing.
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

* **Filename:** `pump1_debug.ino` (can be renamed as needed)
* **Platform:** STM32 (Arduino Core or STM32duino)
* **Dependencies:** None

---

## 👨‍🔧 Author

Written by Yan Naing Kyaw Tint
Documentation compiled by ChatGPT

---


