// // // This is the code for single pump sensor testing.
// #include <Arduino.h>

// // Hardware Pins for all pumps (even though we're only using Pump 2)
// const int allPumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
// const int pumpPin = PA12;  // Pump 9
// const int sensorPin = PA8; // Sensor for Pump 9

// // Calibration factors [0-50mL, 51-100mL, 101-150mL, 151-1000mL]
// float calibrationFactors[4] = {31.30, 31.30, 29.80, 28.50}; // Initial values

// // Dispensing control
// volatile uint32_t pulseCount = 0;
// unsigned long targetVolume = 0;
// unsigned long dispensedVolume = 0;
// unsigned long lastPulseTime = 0;
// bool pumpOn = false;

// void stopAllPumps() {
//   for (int i = 0; i < 9; i++) {
//     digitalWrite(allPumpPins[i], LOW);
//   }
//   if (pumpOn) {
//     detachInterrupt(digitalPinToInterrupt(sensorPin));
//     pumpOn = false;
//   }
//   Serial.println("🛑 ALL PUMPS OFF");
// }

// void pulseCounter() {
//   pulseCount++;
//   lastPulseTime = millis();
// }

// void stopPump() {
//   digitalWrite(pumpPin, LOW);
//   if (pumpOn) {
//     detachInterrupt(digitalPinToInterrupt(sensorPin));
//     pumpOn = false;
//   }
//   Serial.println("🚑 Pump 8 OFF");
// }

// float getCalibrationFactor(unsigned long volume) {
//   if (volume <= 50) return calibrationFactors[0];
//   if (volume <= 100) return calibrationFactors[1];
//   if (volume <= 150) return calibrationFactors[2];
//   return calibrationFactors[3];
// }

// void runPump(unsigned long volume) {
//   float calFactor = getCalibrationFactor(volume);
//   pulseCount = 0;
//   dispensedVolume = 0;
//   lastPulseTime = millis();

//   digitalWrite(pumpPin, HIGH);
//   attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
//   pumpOn = true;

//   Serial.print("⚙️ Pump 9 ON - Target: ");
//   Serial.print(volume);
//   Serial.print(" mL | Cal: ");
//   Serial.println(calFactor, 2);
// }

// void showCalibration() {
//   Serial.println("📊 Current Calibration:");
//   Serial.print("0-50mL: "); Serial.println(calibrationFactors[0], 2);
//   Serial.print("51-100mL: "); Serial.println(calibrationFactors[1], 2);
//   Serial.print("101-150mL: "); Serial.println(calibrationFactors[2], 2);
//   Serial.print("151-1000mL: "); Serial.println(calibrationFactors[3], 2);
// }

// void setup() {
//   Serial.begin(9600);
  
//   // Initialize all pump pins and turn them off
//   for (int i = 0; i < 9; i++) {
//     pinMode(allPumpPins[i], OUTPUT);
//     digitalWrite(allPumpPins[i], LOW);
//   }
  
//   pinMode(sensorPin, INPUT_PULLUP);
//   stopAllPumps(); // Ensure all pumps are off at startup

//   Serial.println("✅ Pump 9 Test System Ready");
//   Serial.println("📘 Commands:");
//   Serial.println("  D9:<volume>       - Dispense volume (mL)");
//   Serial.println("  D9:<v>:<cal>@<r> - Set cal & dispense (e.g. D4:100:11.5@1)");
//   Serial.println("  D9:<r>:<cal>      - Set calibration only (e.g. D4:2:30)");
//   Serial.println("  C                - Show calibration");
//   Serial.println("  S                - Stop all pumps");
// }

// void loop() {
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();

//     if (input.equalsIgnoreCase("S")) {
//       stopAllPumps(); // Now stops ALL pumps
//     }
//     else if (input.equalsIgnoreCase("C")) {
//       showCalibration();
//     }
//     else if (input.startsWith("D9:")) {
//       stopAllPumps(); // Stop all pumps before starting a new operation
      
//       int colon1 = input.indexOf(':');
//       int colon2 = input.indexOf(':', colon1 + 1);
//       int atSymbol = input.indexOf('@');

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
//         calibrationFactors[range] = newCal;
//         Serial.print("🔧 Calibration updated: Range");
//         Serial.print(range);
//         Serial.print(" → ");
//         Serial.println(newCal, 2);
//       }

//       targetVolume = volume;
//       runPump(volume);
//     }
//     else if (input.startsWith("R:")) {
//       int colon = input.indexOf(':');
//       int range = input.substring(colon + 1, input.indexOf(':', colon + 1)).toInt();
//       float newCal = input.substring(input.indexOf(':', colon + 1) + 1).toFloat();

//       if (range >= 0 && range <= 3 && newCal > 0) {
//         calibrationFactors[range] = newCal;
//         Serial.print("🔧 Calibration updated: Range");
//         Serial.print(range);
//         Serial.print(" → ");
//         Serial.println(newCal, 2);
//       }
//     }
//   }

//   if (pumpOn) {
//     float currentVolume = pulseCount / getCalibrationFactor(targetVolume);

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
//       stopPump();
//       Serial.println("🌟 Target reached!");
//     }
//     else if (millis() - lastPulseTime > 2000) {
//       stopPump();
//       Serial.println("⚠️ No flow detected - Pump stopped!");
//     }
//   }
// }