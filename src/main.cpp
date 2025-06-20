
// #include <Arduino.h>

// const int pumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
// const int sensorPins[9] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8};
// // float calibrationFactors[9] = {1st  , 2nd  , 3rd, 4th, 5th, 6th, 7th, 8th, 9th}; // Default values
// float calibrationFactors[9] =    {264.3, 10.62,  80,  38,   1,   4,   1,   1,   1}; // Default values

// volatile uint16_t pulseCount = 0;
// unsigned long totalMilliLitres = 0;
// unsigned long targetMilliLitres = 0;
// unsigned long previousMillis = 0;
// const unsigned long interval = 1000;

// int activePumpIndex = -1;
// bool pumpOn = false;

// void pulseCounter() {
//   pulseCount++;
// }

// void stopAllPumps() {
//   for (int i = 0; i < 9; i++) {
//     digitalWrite(pumpPins[i], LOW);
//   }

//   if (activePumpIndex != -1) {
//     detachInterrupt(digitalPinToInterrupt(sensorPins[activePumpIndex]));
//     activePumpIndex = -1;
//   }

//   pumpOn = false;
//   Serial.println("🛑 All pumps OFF");
// }

// void setup() {
//   Serial.begin(9600);

//   for (int i = 0; i < 9; i++) {
//     digitalWrite(pumpPins[i], LOW);
//     pinMode(pumpPins[i], OUTPUT);
//     pinMode(sensorPins[i], INPUT_PULLUP);
//   }

//   Serial.println("✅ Ready!");
//   Serial.println("📘 Commands:");
//   Serial.println("  D1:100         → Pump 1, 100mL");
//   Serial.println("  D4:100:24      → Pump 4, 100mL, set calibration to 24");
//   Serial.println("  S              → Stop all pumps");
// }

// void loop() {
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();

//     if (input.equalsIgnoreCase("S")) {
//       stopAllPumps();
//     }

//     else if (input.startsWith("D")) {
//       int firstColon = input.indexOf(':');
//       int secondColon = input.indexOf(':', firstColon + 1);

//       int pumpNum = -1;
//       int volume = -1;
//       float newCal = -1;

//       // D4:100 or D4:100:24
//       if (firstColon > 1) {
//         pumpNum = input.substring(1, firstColon).toInt();

//         if (secondColon > firstColon) {
//           volume = input.substring(firstColon + 1, secondColon).toInt();
//           newCal = input.substring(secondColon + 1).toFloat();
//         } else {
//           volume = input.substring(firstColon + 1).toInt();
//         }
//       }

//       if (pumpNum >= 1 && pumpNum <= 9 && volume > 0) {
//         int index = pumpNum - 1;

//         if (newCal > 0.5f) {
//           calibrationFactors[index] = newCal;
//           Serial.print("🛠️ Updated calibration for Pump ");
//           Serial.print(pumpNum);
//           Serial.print(": ");
//           Serial.println(newCal, 2);
//         }

//         if (calibrationFactors[index] <= 1.0f) {
//           Serial.print("⚠️ Cannot use Pump ");
//           Serial.print(pumpNum);
//           Serial.println(": Faulty or uncalibrated sensor.");
//           return;
//         }

//         stopAllPumps();  // Ensure clean start

//         activePumpIndex = index;
//         targetMilliLitres = volume;
//         totalMilliLitres = 0;
//         pulseCount = 0;
//         previousMillis = millis();

//         attachInterrupt(digitalPinToInterrupt(sensorPins[activePumpIndex]), pulseCounter, FALLING);
//         digitalWrite(pumpPins[activePumpIndex], HIGH);
//         pumpOn = true;

//         Serial.print("⚙️ Pump ");
//         Serial.print(pumpNum);
//         Serial.print(" ON - Target: ");
//         Serial.print(volume);
//         Serial.print(" mL | Cal: ");
//         Serial.println(calibrationFactors[activePumpIndex], 2);
//       } else {
//         Serial.println("❌ Invalid command format. Use D4:100 or D4:100:24");
//       }
//     }

//     else {
//       Serial.println("❌ Unknown command. Try D1:100 or S");
//     }
//   }

//   if (pumpOn && millis() - previousMillis >= interval) {
//     previousMillis = millis();

//     noInterrupts();
//     uint16_t pulsesThisSecond = pulseCount;
//     float flowRate = pulsesThisSecond / calibrationFactors[activePumpIndex];
//     pulseCount = 0;
//     interrupts();

//     totalMilliLitres += flowRate;

//     // 🧪 DEBUG OUTPUT
//     Serial.print("📟 Raw Pulses: ");
//     Serial.print(pulsesThisSecond);
//     Serial.print(" | 🧮 Flow: ");
//     Serial.print(flowRate, 2);
//     Serial.print(" mL/s | 🧪 Total: ");
//     Serial.print(totalMilliLitres);
//     Serial.print(" mL (🎯 Target: ");
//     Serial.print(targetMilliLitres);
//     Serial.println(" mL)");

//     if (totalMilliLitres >= targetMilliLitres || totalMilliLitres > 100000) {
//       stopAllPumps();
//       Serial.println("🎯 Target volume reached!");
//     }
//   }
// }

//Thrid snippet
// This code is for a multi-pump system with calibration and flow measurement.
// It uses interrupts to count pulses from flow sensors and controls pumps based on user commands.
// #include <Arduino.h>

// const int pumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
// const int sensorPins[9] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8};

// // Calibration factors structure: [pump][range] = calibration factor
// float calibrationFactors[9][4] = {
//   // Pump 1 (0-50, 51-100, 101-150, 151-1000)
//   {5.25, 5.25, 11.5, 11.5},
//   // Pump 2
//   {13.27, 13.27, 19.91, 20.0},
//   // Pump 3
//   {33.33, 33.33, 33.33, 33.33},
//   // Pump 4
//   {3.17, 3.17, 3.17, 3.17},
//   // Pump 5
//   {1.6, 3.2, 3.2, 3.2},
//   // Pump 6
//   {4.0, 4.0, 4.0, 4.0},
//   // Pump 7-9 (untested)
//   {3, 3, 3, 3},
//   {3, 3, 3, 3},
//   {3, 3, 3, 3}
// };

// volatile uint16_t pulseCount = 0;
// unsigned long totalMilliLitres = 0;
// unsigned long targetMilliLitres = 0;
// unsigned long previousMillis = 0;
// const unsigned long interval = 1000;

// int activePumpIndex = -1;
// bool pumpOn = false;

// void pulseCounter() {
//   pulseCount++;
// }

// void stopAllPumps() {
//   for (int i = 0; i < 9; i++) {
//     digitalWrite(pumpPins[i], LOW);
//   }

//   if (activePumpIndex != -1) {
//     detachInterrupt(digitalPinToInterrupt(sensorPins[activePumpIndex]));
//     activePumpIndex = -1;
//   }

//   pumpOn = false;
//   Serial.println("🛑 All pumps OFF");
// }

// // Get the appropriate calibration factor based on current volume
// float getCurrentCalibrationFactor(int pumpIndex, unsigned long currentVolume) {
//   int rangeIndex;
  
//   if (currentVolume <= 50) rangeIndex = 0;
//   else if (currentVolume <= 100) rangeIndex = 1;
//   else if (currentVolume <= 150) rangeIndex = 2;
//   else rangeIndex = 3;
  
//   return calibrationFactors[pumpIndex][rangeIndex];
// }

// void setup() {
//   Serial.begin(9600);

//   for (int i = 0; i < 9; i++) {
//     digitalWrite(pumpPins[i], LOW);
//     pinMode(pumpPins[i], OUTPUT);
//     pinMode(sensorPins[i], INPUT_PULLUP);
//   }

//   Serial.println("✅ Ready!");
//   Serial.println("📘 Commands:");
//   Serial.println("  D1:100         → Pump 1, 100mL");
//   Serial.println("  D4:100:24      → Pump 4, 100mL, set calibration to 24");
//   Serial.println("  S              → Stop all pumps");
//   Serial.println("  C              → Show current calibration factors");
// }

// void loop() {
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();

//     if (input.equalsIgnoreCase("S")) {
//       stopAllPumps();
//     }
//     else if (input.equalsIgnoreCase("C")) {
//       Serial.println("📊 Current Calibration Factors:");
//       for (int i = 0; i < 9; i++) {
//         Serial.print("Pump ");
//         Serial.print(i+1);
//         Serial.print(": ");
//         for (int j = 0; j < 4; j++) {
//           Serial.print(calibrationFactors[i][j], 2);
//           if (j < 3) Serial.print(", ");
//         }
//         Serial.println();
//       }
//     }
//     else if (input.startsWith("D")) {
//       int firstColon = input.indexOf(':');
//       int secondColon = input.indexOf(':', firstColon + 1);

//       int pumpNum = -1;
//       int volume = -1;
//       float newCal = -1;

//       if (firstColon > 1) {
//         pumpNum = input.substring(1, firstColon).toInt();

//         if (secondColon > firstColon) {
//           volume = input.substring(firstColon + 1, secondColon).toInt();
//           newCal = input.substring(secondColon + 1).toFloat();
//         } else {
//           volume = input.substring(firstColon + 1).toInt();
//         }
//       }

//       if (pumpNum >= 1 && pumpNum <= 9 && volume > 0) {
//         int index = pumpNum - 1;

//         if (newCal > 0.5f) {
//           // Update all ranges for this pump with the new calibration
//           for (int i = 0; i < 4; i++) {
//             calibrationFactors[index][i] = newCal;
//           }
//           Serial.print("🛠️ Updated all calibration ranges for Pump ");
//           Serial.print(pumpNum);
//           Serial.print(" to ");
//           Serial.println(newCal, 2);
//         }

//         // Check if pump is calibrated
//         bool pumpCalibrated = true;
//         for (int i = 0; i < 4; i++) {
//           if (calibrationFactors[index][i] <= 1.0f) {
//             pumpCalibrated = false;
//             break;
//           }
//         }

//         if (!pumpCalibrated) {
//           Serial.print("⚠️ Cannot use Pump ");
//           Serial.print(pumpNum);
//           Serial.println(": Faulty or uncalibrated sensor.");
//           return;
//         }

//         stopAllPumps();  // Ensure clean start

//         activePumpIndex = index;
//         targetMilliLitres = volume;
//         totalMilliLitres = 0;
//         pulseCount = 0;
//         previousMillis = millis();

//         attachInterrupt(digitalPinToInterrupt(sensorPins[activePumpIndex]), pulseCounter, FALLING);
//         digitalWrite(pumpPins[activePumpIndex], HIGH);
//         pumpOn = true;

//         Serial.print("⚙️ Pump ");
//         Serial.print(pumpNum);
//         Serial.print(" ON - Target: ");
//         Serial.print(volume);
//         Serial.print(" mL | Initial Cal: ");
//         Serial.println(getCurrentCalibrationFactor(activePumpIndex, 0), 2);
//       } else {
//         Serial.println("❌ Invalid command format. Use D4:100 or D4:100:24");
//       }
//     }
//     else {
//       Serial.println("❌ Unknown command. Try D1:100, S, or C");
//     }
//   }

//   if (pumpOn && millis() - previousMillis >= interval) {
//     previousMillis = millis();

//     noInterrupts();
//     uint16_t pulsesThisSecond = pulseCount;
//     float currentCal = getCurrentCalibrationFactor(activePumpIndex, totalMilliLitres);
//     float flowRate = pulsesThisSecond / currentCal;
//     pulseCount = 0;
//     interrupts();

//     totalMilliLitres += flowRate;

//     // 🧪 DEBUG OUTPUT
//     Serial.print("📟 Raw Pulses: ");
//     Serial.print(pulsesThisSecond);
//     Serial.print(" | 🧮 Flow: ");
//     Serial.print(flowRate, 2);
//     Serial.print(" mL/s (Cal: ");
//     Serial.print(currentCal, 2);
//     Serial.print(") | 🧪 Total: ");
//     Serial.print(totalMilliLitres);
//     Serial.print(" mL (🎯 Target: ");
//     Serial.print(targetMilliLitres);
//     Serial.println(" mL)");

//     if (totalMilliLitres >= targetMilliLitres || totalMilliLitres > 100000) {
//       stopAllPumps();
//       Serial.println("🎯 Target volume reached!");
//     }
//   }
// }

// // This code is for a multi-pump system with calibration and flow measurement without pump 8
// // It uses interrupts to count pulses from flow sensors and controls pumps based on user commands.
// // The code is designed for an Arduino environment and includes features for calibration, flow rate measurement, and user commands to control the pumps.
// // The code is structured to handle up to 9 pumps, with specific calibration factors for each pump and the ability to stop all pumps or display calibration information.
// #include <Arduino.h>

// const int allPumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
// const int allSensorPins[9] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6, -1, PA8}; // -1 for Pump 8 (no sensor)

// float allCalibrationFactors[9][4] = {
//   {18.00, 23.00, 30.00, 50.00},  // Pump 1
//   {1.90,  1.90,  1.90,  1.90},   // Pump 2
//   {2.40,  5.20,  5.50,  5.50},   // Pump 3
//   {3.00,  8.70,  10.00, 10.00},  // Pump 4
//   {8.00,  13.00, 15.00, 15.00},  // Pump 5
//   {4.10,  4.70,  5.18,  5.56},   // Pump 6
//   {4.10,  3.12,  2.34,  1.71},   // Pump 7
//   {0,     0,     0,     0},      // Pump 8 (not included)
//   {31.30, 31.30, 29.80, 28.50}   // Pump 9
// };

// volatile uint32_t pulseCount = 0;
// unsigned long targetVolume = 0;
// unsigned long dispensedVolume = 0;
// unsigned long lastPulseTime = 0;
// bool pumpOn = false;
// int currentPump = -1;

// void stopAllPumps() {
//   for (int i = 0; i < 9; i++) {
//     digitalWrite(allPumpPins[i], LOW);
//   }
//   if (pumpOn && currentPump != 7) {
//     detachInterrupt(digitalPinToInterrupt(allSensorPins[currentPump]));
//   }
//   pumpOn = false;
//   currentPump = -1;
//   Serial.println("\xF0\x9F\x9B\x91 ALL PUMPS OFF");
// }

// void pulseCounter() {
//   pulseCount++;
//   lastPulseTime = millis();
// }

// float getCalibrationFactor(int pump, unsigned long volume) {
//   if (volume <= 50) return allCalibrationFactors[pump][0];
//   if (volume <= 100) return allCalibrationFactors[pump][1];
//   if (volume <= 150) return allCalibrationFactors[pump][2];
//   return allCalibrationFactors[pump][3];
// }

// void runPump(int pump, unsigned long volume) {
//   float calFactor = getCalibrationFactor(pump, volume);
//   pulseCount = 0;
//   dispensedVolume = 0;
//   lastPulseTime = millis();

//   digitalWrite(allPumpPins[pump], HIGH);
//   if (allSensorPins[pump] != -1) {
//     attachInterrupt(digitalPinToInterrupt(allSensorPins[pump]), pulseCounter, FALLING);
//   }
//   pumpOn = true;
//   currentPump = pump;

//   Serial.print("\xE2\x9A\x99\xEF\xB8\x8F Pump ");
//   Serial.print(pump + 1);
//   Serial.print(" ON - Target: ");
//   Serial.print(volume);
//   Serial.print(" mL | Cal: ");
//   Serial.println(calFactor, 2);
// }

// void showCalibration(int pump) {
//   Serial.println("\xF0\x9F\x93\x8A Current Calibration:");
//   Serial.print("0-50mL: "); Serial.println(allCalibrationFactors[pump][0], 2);
//   Serial.print("51-100mL: "); Serial.println(allCalibrationFactors[pump][1], 2);
//   Serial.print("101-150mL: "); Serial.println(allCalibrationFactors[pump][2], 2);
//   Serial.print("151-1000mL: "); Serial.println(allCalibrationFactors[pump][3], 2);
// }

// void setup() {
//   Serial.begin(9600);

//   for (int i = 0; i < 9; i++) {
//     pinMode(allPumpPins[i], OUTPUT);
//     digitalWrite(allPumpPins[i], LOW);
//     if (allSensorPins[i] != -1) {
//       pinMode(allSensorPins[i], INPUT_PULLUP);
//     }
//   }

//   stopAllPumps();
//   Serial.println("✅ Multi-Pump Controller Ready");
//   Serial.println("📘 Command Format: D<id>:<vol>[:<cal>@<range>], C<id>, S");
// }

// void loop() {
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();

//     if (input.equalsIgnoreCase("S")) {
//       stopAllPumps();
//     }
//     else if (input.startsWith("C")) {
//       int pumpId = input.substring(1).toInt();
//       if (pumpId >= 1 && pumpId <= 9 && pumpId != 8) {
//         showCalibration(pumpId - 1);
//       }
//     }
//     else if (input.startsWith("D")) {
//       int pumpId = input.substring(1, input.indexOf(":")) .toInt();
//       if (pumpId < 1 || pumpId > 9 || pumpId == 8) return;

//       int colon1 = input.indexOf(":");
//       int colon2 = input.indexOf(":", colon1 + 1);
//       int atSymbol = input.indexOf("@");

//       unsigned long volume = input.substring(colon1 + 1, colon2 > 0 ? colon2 : input.length()).toInt();
//       float newCal = -1;
//       int range = -1;

//       if (colon2 > 0) {
//         newCal = input.substring(colon2 + 1, atSymbol > 0 ? atSymbol : input.length()).toFloat();
//         if (atSymbol > 0) {
//           range = input.substring(atSymbol + 1).toInt();
//         }
//       }

//       if (newCal > 0 && range >= 0 && range <= 3) {
//         allCalibrationFactors[pumpId - 1][range] = newCal;
//         Serial.print("🔧 Calibration updated: Pump ");
//         Serial.print(pumpId);
//         Serial.print(" Range ");
//         Serial.print(range);
//         Serial.print(" → ");
//         Serial.println(newCal, 2);
//       }

//       targetVolume = volume;
//       runPump(pumpId - 1, volume);
//     }
//   }

//   if (pumpOn && currentPump != -1) {
//     float currentVolume = pulseCount / getCalibrationFactor(currentPump, targetVolume);

//     static unsigned long lastPrint = 0;
//     if (millis() - lastPrint >= 1000) {
//       lastPrint = millis();
//       Serial.print("📏 Pulses: ");
//       Serial.print(pulseCount);
//       Serial.print(" | Flow: ");
//       Serial.print(currentVolume - dispensedVolume, 1);
//       Serial.print(" mL/s | Total: ");
//       Serial.print(currentVolume, 1);
//       Serial.print("/");
//       Serial.print(targetVolume);
//       Serial.println(" mL");
//     }

//     if (currentVolume >= targetVolume) {
//       stopAllPumps();
//       Serial.println("🌟 Target reached!");
//     }
//     else if (millis() - lastPulseTime > 2000) {
//       stopAllPumps();
//       Serial.println("⚠️ No flow detected - Pump stopped!");
//     }
//   }
// }


#include <Arduino.h>

const int allPumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
const int allSensorPins[9] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6, -1, PA8};

float allCalibrationFactors[9][4] = {
  {18, 23, 30.00, 50.00},     // Pump 1
  {1.9, 1.9, 1.9, 1.9},       // Pump 2
  {2.4, 5.2, 5.5, 5.5},       // Pump 3
  {3, 8.7, 10, 10},           // Pump 4
  {8, 13, 15, 15},            // Pump 5
  {4.1, 4.7, 5.18, 5.56},     // Pump 6
  {4.1, 3.12, 2.34, 1.71},    // Pump 7
  {0, 0, 0, 0},               // Pump 8 (time-based, calibration not used)
  {31.30, 31.30, 29.80, 28.50} // Pump 9
};

volatile uint32_t pulseCount = 0;
unsigned long targetVolume = 0;
unsigned long dispensedVolume = 0;
unsigned long lastPulseTime = 0;
bool pumpOn = false;

unsigned long startTime = 0;
unsigned long targetDuration = 0; // For pump 8 only

int currentPumpId = -1;

void stopAllPumps() {
  for (int i = 0; i < 9; i++) {
    digitalWrite(allPumpPins[i], LOW);
  }
  if (pumpOn && currentPumpId != 7) {
    int sensorPin = allSensorPins[currentPumpId];
    if (sensorPin != -1) detachInterrupt(digitalPinToInterrupt(sensorPin));
  }
  pumpOn = false;
  Serial.println("🛑 ALL PUMPS OFF");
}

void pulseCounter() {
  pulseCount++;
  lastPulseTime = millis();
}

float getCalibrationFactor(int pumpId, unsigned long volume) {
  if (volume <= 50) return allCalibrationFactors[pumpId][0];
  if (volume <= 100) return allCalibrationFactors[pumpId][1];
  if (volume <= 150) return allCalibrationFactors[pumpId][2];
  return allCalibrationFactors[pumpId][3];
}

void runPump(int pumpId, unsigned long volume) {
  float cal = getCalibrationFactor(pumpId, volume);
  pulseCount = 0;
  dispensedVolume = 0;
  lastPulseTime = millis();

  digitalWrite(allPumpPins[pumpId], HIGH);
  if (pumpId != 7) {
    int sensorPin = allSensorPins[pumpId];
    if (sensorPin != -1) attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  } else {
    // Pump 8 time-based
    if (volume == 50) targetDuration = 6236;
    else if (volume == 100) targetDuration = 12208;
    else if (volume == 150) targetDuration = 18400;
    else {
      Serial.println("❌ Unsupported volume for Pump 8. Use 50, 100, 150 mL");
      return;
    }
    startTime = millis();
  }

  pumpOn = true;
  currentPumpId = pumpId;
  Serial.print("⚙️ Pump "); Serial.print(pumpId + 1);
  Serial.print(" ON - Target: "); Serial.print(volume);
  if (pumpId != 7) {
    Serial.print(" mL | Cal: "); Serial.println(cal, 2);
  } else {
    Serial.print(" mL | Duration: "); Serial.print(targetDuration / 1000.0, 3);
    Serial.println(" seconds");
  }
}

void showCalibration(int pumpId) {
  Serial.print("📊 Current Calibration for Pump "); Serial.println(pumpId + 1);
  Serial.print("0-50mL: "); Serial.println(allCalibrationFactors[pumpId][0], 2);
  Serial.print("51-100mL: "); Serial.println(allCalibrationFactors[pumpId][1], 2);
  Serial.print("101-150mL: "); Serial.println(allCalibrationFactors[pumpId][2], 2);
  Serial.print("151-1000mL: "); Serial.println(allCalibrationFactors[pumpId][3], 2);
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 9; i++) {
    pinMode(allPumpPins[i], OUTPUT);
    digitalWrite(allPumpPins[i], LOW);
  }
  for (int i = 0; i < 9; i++) {
    if (allSensorPins[i] != -1) pinMode(allSensorPins[i], INPUT_PULLUP);
  }
  stopAllPumps();
  Serial.println("✅ All Pumps Controller Ready");
  Serial.println("📘 Commands:");
  Serial.println("  D<id>:<volume>         - Dispense volume (mL)");
  Serial.println("  D<id>:<v>:<cal>@<r>    - Set calibration + dispense (e.g. D3:100:4.3@1)");
  Serial.println("  D<id>:<r>:<cal>        - Set calibration only (e.g. D6:2:5.5)");
  Serial.println("  C<id>                  - Show calibration for pump");
  Serial.println("  S                      - Stop all pumps");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.equalsIgnoreCase("S")) {
      stopAllPumps();
    } else if (input.startsWith("S")) {
      int pumpId = input.substring(1).toInt() - 1;
      if (pumpId >= 0 && pumpId < 9) showCalibration(pumpId);
    } else if (input.startsWith("D")) {
      stopAllPumps();

      int dIndex = 1;
      int colon1 = input.indexOf(':');
      int colon2 = input.indexOf(':', colon1 + 1);
      int atIndex = input.indexOf('@');

      int pumpId = input.substring(dIndex, colon1).toInt() - 1;
      if (pumpId < 0 || pumpId >= 9) {
        Serial.println("❌ Invalid pump ID");
        return;
      }

      unsigned long volume = input.substring(colon1 + 1, colon2 > 0 ? colon2 : input.length()).toInt();

      if (colon2 > 0 && atIndex > 0) {
        float cal = input.substring(colon2 + 1, atIndex).toFloat();
        int range = input.substring(atIndex + 1).toInt();
        if (range >= 0 && range < 4 && cal > 0 && pumpId != 7) {
          allCalibrationFactors[pumpId][range] = cal;
          Serial.print("🔧 Calibration updated: Pump "); Serial.print(pumpId + 1);
          Serial.print(" Range "); Serial.print(range);
          Serial.print(" → "); Serial.println(cal, 2);
        }
      } else if (colon2 > 0) {
        int range = input.substring(colon1 + 1, colon2).toInt();
        float cal = input.substring(colon2 + 1).toFloat();
        if (range >= 0 && range < 4 && cal > 0 && pumpId != 7) {
          allCalibrationFactors[pumpId][range] = cal;
          Serial.print("🔧 Calibration updated: Pump "); Serial.print(pumpId + 1);
          Serial.print(" Range "); Serial.print(range);
          Serial.print(" → "); Serial.println(cal, 2);
          return;
        }
      }

      targetVolume = volume;
      runPump(pumpId, volume);
    }
  }

  if (pumpOn) {
    if (currentPumpId == 7) {
      static unsigned long lastPrint = 0;
      if (millis() - lastPrint >= 1000) {
        lastPrint = millis();
        float elapsed = (millis() - startTime) / 1000.0;
        Serial.print("📏 Time-Based | Elapsed: ");
        Serial.print(elapsed, 2);
        Serial.print("s / ");
        Serial.print(targetDuration / 1000.0, 2);
        Serial.println("s");
      }
      if (millis() - startTime >= targetDuration) {
        digitalWrite(allPumpPins[currentPumpId], LOW);
        pumpOn = false;
        Serial.println("🌟 Target time reached!");
      }
    } else {
      float currentVol = pulseCount / getCalibrationFactor(currentPumpId, targetVolume);
      static unsigned long lastPrint = 0;
      if (millis() - lastPrint >= 1000) {
        lastPrint = millis();
        Serial.print("📏 Pulses: "); Serial.print(pulseCount);
        Serial.print(" | Flow: "); Serial.print(currentVol - dispensedVolume, 1);
        Serial.print(" mL/s | Total: "); Serial.print(currentVol, 1);
        Serial.print("/"); Serial.print(targetVolume); Serial.println(" mL");
        dispensedVolume = currentVol;
      }
      if (currentVol >= targetVolume) {
        digitalWrite(allPumpPins[currentPumpId], LOW);
        detachInterrupt(digitalPinToInterrupt(allSensorPins[currentPumpId]));
        pumpOn = false;
        Serial.println("🌟 Target reached!");
      } else if (millis() - lastPulseTime > 2000) {
        digitalWrite(allPumpPins[currentPumpId], LOW);
        detachInterrupt(digitalPinToInterrupt(allSensorPins[currentPumpId]));
        pumpOn = false;
        Serial.println("⚠️ No flow detected - Pump stopped!");
      }
    }
  }
}
