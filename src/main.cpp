
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

// This is the code for single pump sensor testing.
#include <Arduino.h>

// Hardware Pins for all pumps (even though we're only using Pump 2)
const int allPumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
const int pumpPin = PB5;  // Pump 4
const int sensorPin = PA4; // Sensor for Pump 4

// Calibration factors [0-50mL, 51-100mL, 101-150mL, 151-1000mL]
float calibrationFactors[4] = {8, 13, 15, 15}; // Initial values

// Dispensing control
volatile uint32_t pulseCount = 0;
unsigned long targetVolume = 0;
unsigned long dispensedVolume = 0;
unsigned long lastPulseTime = 0;
bool pumpOn = false;

void stopAllPumps() {
  for (int i = 0; i < 9; i++) {
    digitalWrite(allPumpPins[i], LOW);
  }
  if (pumpOn) {
    detachInterrupt(digitalPinToInterrupt(sensorPin));
    pumpOn = false;
  }
  Serial.println("🛑 ALL PUMPS OFF");
}

void pulseCounter() {
  pulseCount++;
  lastPulseTime = millis();
}

void stopPump() {
  digitalWrite(pumpPin, LOW);
  if (pumpOn) {
    detachInterrupt(digitalPinToInterrupt(sensorPin));
    pumpOn = false;
  }
  Serial.println("🚑 Pump 5 OFF");
}

float getCalibrationFactor(unsigned long volume) {
  if (volume <= 50) return calibrationFactors[0];
  if (volume <= 100) return calibrationFactors[1];
  if (volume <= 150) return calibrationFactors[2];
  return calibrationFactors[3];
}

void runPump(unsigned long volume) {
  float calFactor = getCalibrationFactor(volume);
  pulseCount = 0;
  dispensedVolume = 0;
  lastPulseTime = millis();

  digitalWrite(pumpPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  pumpOn = true;

  Serial.print("⚙️ Pump 5 ON - Target: ");
  Serial.print(volume);
  Serial.print(" mL | Cal: ");
  Serial.println(calFactor, 2);
}

void showCalibration() {
  Serial.println("📊 Current Calibration:");
  Serial.print("0-50mL: "); Serial.println(calibrationFactors[0], 2);
  Serial.print("51-100mL: "); Serial.println(calibrationFactors[1], 2);
  Serial.print("101-150mL: "); Serial.println(calibrationFactors[2], 2);
  Serial.print("151-1000mL: "); Serial.println(calibrationFactors[3], 2);
}

void setup() {
  Serial.begin(9600);
  
  // Initialize all pump pins and turn them off
  for (int i = 0; i < 9; i++) {
    pinMode(allPumpPins[i], OUTPUT);
    digitalWrite(allPumpPins[i], LOW);
  }
  
  pinMode(sensorPin, INPUT_PULLUP);
  stopAllPumps(); // Ensure all pumps are off at startup

  Serial.println("✅ Pump 5 Test System Ready");
  Serial.println("📘 Commands:");
  Serial.println("  D5:<volume>       - Dispense volume (mL)");
  Serial.println("  D5:<v>:<cal>@<r> - Set cal & dispense (e.g. D4:100:11.5@1)");
  Serial.println("  D5:<r>:<cal>      - Set calibration only (e.g. D4:2:30)");
  Serial.println("  C                - Show calibration");
  Serial.println("  S                - Stop all pumps");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.equalsIgnoreCase("S")) {
      stopAllPumps(); // Now stops ALL pumps
    }
    else if (input.equalsIgnoreCase("C")) {
      showCalibration();
    }
    else if (input.startsWith("D5:")) {
      stopAllPumps(); // Stop all pumps before starting a new operation
      
      int colon1 = input.indexOf(':');
      int colon2 = input.indexOf(':', colon1 + 1);
      int atSymbol = input.indexOf('@');

      unsigned long volume = input.substring(colon1 + 1, colon2 > 0 ? colon2 : input.length()).toInt();
      float newCal = -1;
      int range = -1;

      if (colon2 > 0) {
        newCal = input.substring(colon2 + 1, atSymbol > 0 ? atSymbol : input.length()).toFloat();
        if (atSymbol > 0) {
          range = input.substring(atSymbol + 1).toInt();
        }
      }

      if (newCal > 0 && range >= 0 && range <= 3) {
        calibrationFactors[range] = newCal;
        Serial.print("🔧 Calibration updated: Range");
        Serial.print(range);
        Serial.print(" → ");
        Serial.println(newCal, 2);
      }

      targetVolume = volume;
      runPump(volume);
    }
    else if (input.startsWith("R:")) {
      int colon = input.indexOf(':');
      int range = input.substring(colon + 1, input.indexOf(':', colon + 1)).toInt();
      float newCal = input.substring(input.indexOf(':', colon + 1) + 1).toFloat();

      if (range >= 0 && range <= 3 && newCal > 0) {
        calibrationFactors[range] = newCal;
        Serial.print("🔧 Calibration updated: Range");
        Serial.print(range);
        Serial.print(" → ");
        Serial.println(newCal, 2);
      }
    }
  }

  if (pumpOn) {
    float currentVolume = pulseCount / getCalibrationFactor(targetVolume);

    static unsigned long lastPrint = 0;
    if (millis() - lastPrint >= 1000) {
      lastPrint = millis();
      Serial.print("📏 Pulses: ");
      Serial.print(pulseCount);
      Serial.print(" | Flow: ");
      Serial.print(currentVolume - dispensedVolume, 1);
      Serial.print(" mL/s | Total: ");
      Serial.print(currentVolume, 1);
      Serial.print("/");
      Serial.print(targetVolume);
      Serial.println(" mL");
    }

    if (currentVolume >= targetVolume) {
      stopPump();
      Serial.println("🌟 Target reached!");
    }
    else if (millis() - lastPulseTime > 2000) {
      stopPump();
      Serial.println("⚠️ No flow detected - Pump stopped!");
    }
  }
}