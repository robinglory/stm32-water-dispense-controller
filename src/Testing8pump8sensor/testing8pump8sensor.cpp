// #include <Arduino.h>

// const int allPumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
// const int pumpPin = PA15;  // Replace with desired pump pin

// unsigned long targetDuration = 0; // in ms
// unsigned long startTime = 0;
// bool pumpOn = false;

// void stopAllPumps() {
//   for (int i = 0; i < 9; i++) {
//     digitalWrite(allPumpPins[i], LOW);
//   }
//   pumpOn = false;
//   Serial.println("🛑 ALL PUMPS OFF");
// }

// void stopPump() {
//   digitalWrite(pumpPin, LOW);
//   pumpOn = false;
//   Serial.println("🚑 Pump OFF");
// }

// void runPumpForDuration(unsigned long duration_ms, unsigned long volume) {
//   targetDuration = duration_ms;
//   startTime = millis();
//   digitalWrite(pumpPin, HIGH);
//   pumpOn = true;

//   Serial.print("⚙️ Pump 8 ON - Target: ");
//   Serial.print(volume);
//   Serial.print(" mL | Duration: ");
//   Serial.print(duration_ms / 1000.0, 3);
//   Serial.println(" seconds");
// }

// void showCalibrationFake() {
//   Serial.println("📊 Current Calibration:");
//   Serial.println("0-50mL: 4.10");
//   Serial.println("51-100mL: 3.12");
//   Serial.println("101-150mL: 5.18");
//   Serial.println("151-1000mL: 5.56");
// }

// void setup() {
//   Serial.begin(9600);

//   for (int i = 0; i < 9; i++) {
//     pinMode(allPumpPins[i], OUTPUT);
//     digitalWrite(allPumpPins[i], LOW);
//   }

//   stopAllPumps();

//   Serial.println("✅ Pump 8 Time-Based Controller Ready");
//   Serial.println("📘 Commands:");
//   Serial.println("  D8:<volume>       - Dispense volume (mL)");
//   Serial.println("  C                - Show calibration (fake display)");
//   Serial.println("  S                - Stop all pumps");
// }

// void loop() {
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();

//     if (input.equalsIgnoreCase("S")) {
//       stopAllPumps();
//     }
//     else if (input.equalsIgnoreCase("C")) {
//       showCalibrationFake();
//     }
//     else if (input.startsWith("D8:")) {
//       stopAllPumps();

//       int colon1 = input.indexOf(':');
//       int colon2 = input.indexOf(':', colon1 + 1); // optional cal input (ignored)

//       unsigned long volume = input.substring(colon1 + 1, colon2 > 0 ? colon2 : input.length()).toInt();

//       // Fake hardcoded durations for specific volumes
//       unsigned long duration_ms = 0;
//       if (volume == 50) duration_ms = 6236;
//       else if (volume == 100) duration_ms = 12208;
//       else if (volume == 150) duration_ms = 18400;
//       else {
//         Serial.println("❌ Unsupported volume. Only 50, 100, and 150 mL are supported.");
//         return;
//       }

//       runPumpForDuration(duration_ms, volume);
//     }
//   }

//   if (pumpOn) {
//     static unsigned long lastPrint = 0;
//     if (millis() - lastPrint >= 1000) {
//       lastPrint = millis();
//       float elapsedSec = (millis() - startTime) / 1000.0;
//       Serial.print("📏 Time-Based | Elapsed: ");
//       Serial.print(elapsedSec, 2);
//       Serial.print("s / ");
//       Serial.print(targetDuration / 1000.0, 2);
//       Serial.println("s");
//     }

//     if (millis() - startTime >= targetDuration) {
//       stopPump();
//       Serial.println("🌟 Target time reached!");
//     }
//   }
// }
