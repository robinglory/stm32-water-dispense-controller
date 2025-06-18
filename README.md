# Whole Project README.md File
---


```markdown
# STM32 Water Dispense Controller

This is the hardware-side code for a water dispensing system built on  STM32 . The system uses pulse-counting flow sensors and MOSFET-controlled pumps, with dynamic calibration based on the target volume.

> 💧 Designed for precise multi-channel water dispensing using STM32 microcontrollers.

---

## 📁 Directory Structure

```

```

stm32-water-dispense-controller/
├── .vscode/                    # VSCode settings (PlatformIO or Arduino config)
├── include/                   # Header files (if any)
├── lib/                       # External libraries (if used)
├── src/                       # Main firmware source files (multi-pump tests, etc.)
│   ├── main.cpp
│   ├── main1.cpp
│   ├── main2.cpp
│   ├── flowsensortester/
│   ├── Testing1pump1sensor/
│   │   ├── testing1pumpsensor.cpp
│   │   └── README.md
│   ├── Testing2pump2sensor/
│   │   ├── testing2pumpsensor.cpp
│   │   └── README.md
│   ├── Testing3pump3sensor/
│   │   ├── testing3pumpsensor.cpp
│   │   └── README.md
│   ├── testing4pumpsensor.cpp
│   │   ├── testing4pumpsensor.cpp
│   │   └── README.md
│   ├── testing5pumpsensor.cpp
│   │   ├── testing5pumpsensor.cpp
│   │   └── README.md
│   ├── testing6pumpsensor.cpp
│   │   ├── testing1pumpsensor.cpp
│   │   └── README.md
│   ├── testing7pumpsensor.cpp
│   │   ├── testing7pumpsensor.cpp
│   │   └── README.md
│   ├── testing8pumpsensor.cpp
│   │   ├── testing8pumpsensor.cpp
│   │   └── README.md
│   ├── testing9pumpsensor.cpp
│   │   ├── testing9pumpsensor.cpp
│   │   └── README.md
│   ├── testingfaultysensor.cpp
├── test/                      # Unit tests (if needed)
├── .gitignore                 # Git ignore rules
├── CS50 Python.code-workspace # Workspace config (This is from another project!)
├── stm32hardware.code-workspace
└── platformio.ini             # PlatformIO project config


```

---

## 🧪 Test Directories

Each test folder in `src/` is  self-contained  and includes its own `README.md`:

- `Testing1pump1sensor/` – Test for one pump and one sensor.
- `Testing2pump2sensor/` – Test for two pumps/sensors.
- `Testing3pump3sensor/` – Test for three pumps/sensors.
- Additional tests explore calibration, fault handling, and scaling.

---

## ⚙️ Features

- STM32-compatible C++ code (Arduino-based or PlatformIO)
- Dynamic calibration based on volume ranges
- Flow sensor pulse counting
- MOSFET pump control
- Serial command interface (e.g., `D2:100`, `D4:<range>:<cal>`, `S`)
- Safety timeout (auto-shutdown if no flow detected)

---

## 📌 Notes

- Software (Python GUI) is in a  separate repo : [link placeholder]
- Designed for modular testing and hardware debugging
- Actively developed and tested on STM32 with PlatformIO

---


```

---

## 📄 License

MIT License

Copyright (c) 2025 Robin Glory

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY...
