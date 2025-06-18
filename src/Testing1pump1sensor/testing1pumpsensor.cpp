// // This is the code for single pump sensor testing.
// #include <Arduino.h>

// // Hardware Pins
// const int pumpPin = PB9;
// const int sensorPin = PA0;

// // Calibration factors [0-50mL, 51-100mL, 101-150mL, 151-1000mL]
// float calibrationFactors[4] = {18, 23, 30.00, 50.00}; // Initial values

// // Dispensing control
// volatile uint32_t pulseCount = 0;
// unsigned long targetVolume = 0;
// unsigned long dispensedVolume = 0;
// unsigned long lastPulseTime = 0;
// bool pumpOn = false;

// void pulseCounter() {
//   pulseCount++;
//   lastPulseTime = millis();
// }

// void stopPump() {
//   digitalWrite(pumpPin, LOW);
//   detachInterrupt(digitalPinToInterrupt(sensorPin));
//   pumpOn = false;
//   Serial.println("🛑 Pump OFF");
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
  
//   Serial.print("⚙️ Pump ON - Target: ");
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
//   pinMode(pumpPin, OUTPUT);
//   digitalWrite(pumpPin, LOW);
//   pinMode(sensorPin, INPUT_PULLUP);
  
//   Serial.println("✅ Pump Test System Ready");
//   Serial.println("📘 Commands:");
//   Serial.println("  D1:<volume>       - Dispense volume (mL)");
//   Serial.println("  D1:<v>:<cal>@<r> - Set cal & dispense (e.g. D1:100:11.5@1)");
//   Serial.println("  D4:<r>:<cal>      - Set calibration only (e.g. D4:2:30)");
//   Serial.println("  C                - Show calibration");
//   Serial.println("  S                - Stop pump");
// }

// void loop() {
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();
    
//     if (input.equalsIgnoreCase("S")) {
//       stopPump();
//     }
//     else if (input.equalsIgnoreCase("C")) {
//       showCalibration();
//     }
//     else if (input.startsWith("D1:")) {
//       // Parse D1 command
//       int colon1 = input.indexOf(':');
//       int colon2 = input.indexOf(':', colon1+1);
//       int atSymbol = input.indexOf('@');
      
//       unsigned long volume = input.substring(colon1+1, colon2>0?colon2:input.length()).toInt();
//       float newCal = -1;
//       int range = -1;
      
//       if (colon2 > 0) {
//         newCal = input.substring(colon2+1, atSymbol>0?atSymbol:input.length()).toFloat();
//         if (atSymbol > 0) {
//           range = input.substring(atSymbol+1).toInt();
//         }
//       }
      
//       // Update calibration if specified
//       if (newCal > 0 && range >= 0 && range <= 3) {
//         calibrationFactors[range] = newCal;
//         Serial.print("🛠️ Calibration updated: Range");
//         Serial.print(range);
//         Serial.print(" → ");
//         Serial.println(newCal, 2);
//       }
      
//       // Start dispensing
//       stopPump();
//       targetVolume = volume;
//       runPump(volume);
//     }
//     else if (input.startsWith("D4:")) {
//       // Calibration-only command
//       int colon = input.indexOf(':');
//       int range = input.substring(colon+1, input.indexOf(':', colon+1)).toInt();
//       float newCal = input.substring(input.indexOf(':', colon+1)+1).toFloat();
      
//       if (range >= 0 && range <= 3 && newCal > 0) {
//         calibrationFactors[range] = newCal;
//         Serial.print("🛠️ Calibration updated: Range");
//         Serial.print(range);
//         Serial.print(" → ");
//         Serial.println(newCal, 2);
//       }
//     }
//   }

//   if (pumpOn) {
//     // Calculate current volume
//     float currentVolume = pulseCount / getCalibrationFactor(targetVolume);
    
//     // Debug output every second
//     static unsigned long lastPrint = 0;
//     if (millis() - lastPrint >= 1000) {
//       lastPrint = millis();
//       Serial.print("📟 Pulses: ");
//       Serial.print(pulseCount);
//       Serial.print(" | Flow: ");
//       Serial.print(currentVolume - dispensedVolume, 1);
//       Serial.print(" mL/s | Total: ");
//       Serial.print(currentVolume, 1);
//       Serial.print("/");
//       Serial.print(targetVolume);
//       Serial.println(" mL");
//     }
    
//     // Check completion
//     if (currentVolume >= targetVolume) {
//       stopPump();
//       Serial.println("🎯 Target reached!");
//     }
//     // Safety timeout
//     else if (millis() - lastPulseTime > 2000) {
//       stopPump();
//       Serial.println("⚠️ No flow detected - Pump stopped!");
//     }
//   }
// }