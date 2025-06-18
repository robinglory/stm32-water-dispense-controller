// #include <Arduino.h>

// // ACTIVE pump and sensor pins
// const int pumpPin = PB5;
// const int flowSensorPin = PA4;

// volatile uint16_t pulseCount = 0;
// unsigned long pumpStartTime = 0;
// unsigned long pumpDuration = 0;
// bool pumpRunning = false;

// void pulseCounter() {
//   pulseCount++;
// }

// void setup() {
//   Serial.begin(9600);

//   // Configure pump pin
//   pinMode(pumpPin, OUTPUT);
//   digitalWrite(pumpPin, LOW);

//   // Configure sensor pin with interrupt
//   pinMode(flowSensorPin, INPUT_PULLUP);
//   attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

//   Serial.println("Ready! Type duration in seconds (e.g., '5') to run pump for 5 seconds.");
// }

// void loop() {
//   // Handle serial input
//   if (Serial.available()) {
//     String input = Serial.readStringUntil('\n');
//     input.trim();
    
//     unsigned long duration = input.toInt();
//     if (duration > 0) {
//       pumpDuration = duration * 1000; // Convert to milliseconds
//       pulseCount = 0; // Reset pulse counter
//       pumpStartTime = millis();
//       pumpRunning = true;
//       digitalWrite(pumpPin, HIGH);
//       Serial.print("⏳ Pump ON for ");
//       Serial.print(duration);
//       Serial.println(" seconds...");
//     }
//   }

//   // Check if pump should be turned off
//   if (pumpRunning && (millis() - pumpStartTime >= pumpDuration)) {
//     digitalWrite(pumpPin, LOW);
//     pumpRunning = false;
    
//     Serial.print("🛑 Pump OFF | Total pulses: ");
//     Serial.println(pulseCount);
//   }
// }