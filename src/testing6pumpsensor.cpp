// #include <Arduino.h>

// // ACTIVE pump and sensor pins
// const int pumpPin = PB4;
// const int flowSensorPin = PA5;
// const int pumpPin1 = PA15;
// const int pumpPin2 = PA12;

// volatile uint16_t pulseCount = 0;
// float calibrationFactor = 4; // Adjust according to your sensor
// unsigned long previousMillis = 0;
// unsigned long interval = 1000; // 1 second interval
// unsigned long totalMilliLitres = 0;
// unsigned long targetMilliLitres = 0;
// bool pumpOn = false;

// void pulseCounter() {
//   pulseCount++;
// }

// void setup() {
//   Serial.begin(9600);

//   // 🔌 Disable JTAG to allow PA15, PB3, PB4 to work as GPIO
//   AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

//   // 🟢 Initialize all pump pins as OUTPUT, then set LOW
//   pinMode(pumpPin, OUTPUT);       // PB4
//   digitalWrite(pumpPin, LOW);

//   pinMode(pumpPin1, OUTPUT);      // PA15
//   digitalWrite(pumpPin1, LOW);

//   pinMode(pumpPin2, OUTPUT);      // PA12
//   digitalWrite(pumpPin2, LOW);

//   // 🌀 Initialize flow sensor pin with pull-up and attach interrupt
//   pinMode(flowSensorPin, INPUT_PULLUP);
//   attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

//   Serial.println("✅ Ready! Type volume in mL (e.g., '100') to start pumping, or '0' to stop.");
// }


// void loop() {
//   // Handle serial input
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();

//     if (input == "0") {
//       pumpOn = false;
//       digitalWrite(pumpPin, LOW);
//       Serial.println("🛑 Pump OFF");
//     } else {
//       targetMilliLitres = input.toInt();
//       if (targetMilliLitres > 0) {
//         totalMilliLitres = 0;
//         pumpOn = true;
//         digitalWrite(pumpPin, HIGH);
//         Serial.print("⚙️ Pump ON - Target: ");
//         Serial.print(targetMilliLitres);
//         Serial.println(" mL");
//       }
//     }
//   }

//   // Measure flow every second
//   unsigned long currentMillis = millis();
//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;

//     noInterrupts();
//     float flowRate = pulseCount / calibrationFactor;  // mL per second
//     pulseCount = 0;
//     interrupts();

//     if (pumpOn) {
//       totalMilliLitres += flowRate;

//       if (totalMilliLitres >= targetMilliLitres) {
//         pumpOn = false;
//         digitalWrite(pumpPin, LOW);
//         Serial.println("🎯 Target volume reached!");
//       }
//     }

//     // Serial monitor feedback
//     Serial.print("💧 Flow: ");
//     Serial.print(flowRate, 2);
//     Serial.print(" mL/s | Total: ");
//     Serial.print(totalMilliLitres);
//     Serial.print(" mL");

//     if (targetMilliLitres > 0) {
//       Serial.print(" (Target: ");
//       Serial.print(targetMilliLitres);
//       Serial.print(" mL)");
//     }

//     Serial.println();
//   }
// }