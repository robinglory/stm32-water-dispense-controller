// with flow sensor!!
// #include <Arduino.h>

// // Define pump and sensor pin mappings
// const uint8_t pumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
// const uint8_t flowSensorPins[9] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8};

// // Flow count per sensor
// volatile uint16_t flowCounts[9] = {0};
// int currentPump = -1;
// bool pumpRunning = false;
// const uint16_t targetPulses = 500; // 200 mL if 10 pulses per mL


// // ISR for each flow sensor
// void flowISR0() { flowCounts[0]++; }
// void flowISR1() { flowCounts[1]++; }
// void flowISR2() { flowCounts[2]++; }
// void flowISR3() { flowCounts[3]++; }
// void flowISR4() { flowCounts[4]++; }
// void flowISR5() { flowCounts[5]++; }
// void flowISR6() { flowCounts[6]++; }
// void flowISR7() { flowCounts[7]++; }
// void flowISR8() { flowCounts[8]++; }

// void (*flowISRs[9])() = {
//   flowISR0, flowISR1, flowISR2, flowISR3, flowISR4,
//   flowISR5, flowISR6, flowISR7, flowISR8
// };

// void setup() {
//   Serial1.begin(9600);
//   Serial1.println("System initialized. Press 1-9 to run pumps, 0 to stop.");

//   for (int i = 0; i < 9; i++) {
//     pinMode(pumpPins[i], OUTPUT);
//     digitalWrite(pumpPins[i], LOW);  // Ensure all pumps are OFF

//     pinMode(flowSensorPins[i], INPUT_PULLUP);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[i]), flowISRs[i], RISING);
//   }
// }

// void loop() {
//   if (Serial1.available()) {
//     char cmd = Serial1.read();

//     if (cmd >= '1' && cmd <= '9') {
//       int index = cmd - '1';

//       if (!pumpRunning) {
//         currentPump = index;
//         flowCounts[currentPump] = 0;
//         digitalWrite(pumpPins[currentPump], HIGH);  // Start the pump
//         pumpRunning = true;

//         Serial1.printf("Pump %d started. Target: 500 mL\n", currentPump + 1);
//       } else {
//         Serial1.println("Another pump is already running. Stop it first.");
//       }

//     } else if (cmd == '0') {
//       if (pumpRunning) {
//         digitalWrite(pumpPins[currentPump], LOW);  // Stop the pump manually
//         Serial1.printf("Pump %d stopped manually.\n", currentPump + 1);
//       }
//       currentPump = -1;
//       pumpRunning = false;
//       memset((void*)flowCounts, 0, sizeof(flowCounts));  // Reset flow counts
//       Serial1.println("All pumps OFF. System reset.");
//     } else {
//       Serial1.println("Invalid input. Use 1–9 to start, 0 to stop.");
//     }
//   }

//   if (pumpRunning && currentPump >= 0) {
//     if (flowCounts[currentPump] >= targetPulses) {
//       digitalWrite(pumpPins[currentPump], LOW);  // Stop the pump when target is reached
//       Serial1.printf("Pump %d completed: 500 mL dispensed.\n", currentPump + 1);
//       Serial1.printf("Total Pulses: %d\n", flowCounts[currentPump]);

//       pumpRunning = false;
//       currentPump = -1;
//     } else {
//       Serial1.printf("Pump %d — Pulses: %d\n", currentPump + 1, flowCounts[currentPump]);
//       delay(500);  // Delay to make serial output readable
//     }
//   }
// }


  // without using the flow senosr. (The raw method)
  // #include <Arduino.h>

  // const uint8_t pumpPins[9] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};

  // #define MAX_FLOW_RATE_ML_PER_MIN 2500.0
  // const float flowRate_mL_per_sec = MAX_FLOW_RATE_ML_PER_MIN / 60.0;  // 41.67 mL/sec
  // const int compensationVolume = 80; // Add 110 mL to correct under-dispensing

  // bool pumpRunning = false;
  // int currentPump = -1;
  // unsigned long pumpStartTime = 0;
  // unsigned long pumpRunDuration = 0;

  // void setup() {
  //   Serial1.begin(9600);
  //   Serial1.println("🟢 Pump system ready. Use D:<pump>:<volume_ml> to start, or S to stop.");

  //   for (int i = 0; i < 9; i++) {
  //     pinMode(pumpPins[i], OUTPUT);
  //     digitalWrite(pumpPins[i], LOW);
  //   }
  // }

  // void loop() {
  //   if (Serial1.available()) {
  //     String input = Serial1.readStringUntil('\n');
  //     input.trim();
  //     input.toUpperCase(); // Allow lower case commands

  //     if (input.startsWith("D:")) {
  //       if (pumpRunning) {
  //         Serial1.println("⚠️ A pump is already running. Stop it first (send 'S').");
  //         return;
  //       }

  //       int firstColon = input.indexOf(':');
  //       int secondColon = input.indexOf(':', firstColon + 1);
  //       if (secondColon == -1) {
  //         Serial1.println("❌ Invalid format. Use D:<pump>:<volume_ml>");
  //         return;
  //       }

  //       int pump = input.substring(firstColon + 1, secondColon).toInt();
  //       int volume = input.substring(secondColon + 1).toInt();

  //       if (pump < 1 || pump > 9 || volume <= 0) {
  //         Serial1.println("❌ Invalid pump number or volume.");
  //         return;
  //       }

  //       int correctedVolume = volume + compensationVolume;
  //       currentPump = pump - 1;
  //       pumpRunDuration = (unsigned long)((float)correctedVolume / flowRate_mL_per_sec * 1000.0);  // in ms
  //       pumpStartTime = millis();
  //       digitalWrite(pumpPins[currentPump], HIGH);
  //       pumpRunning = true;

  //       Serial1.printf("✅ Pump %d started for %d mL (+%d mL correction, ~%.2f sec).\n", pump, volume, compensationVolume, pumpRunDuration / 1000.0);

  //     } else if (input == "S") {
  //       if (pumpRunning && currentPump >= 0) {
  //         digitalWrite(pumpPins[currentPump], LOW);
  //         unsigned long elapsed = millis() - pumpStartTime;
  //         Serial1.printf("⛔ Pump %d stopped manually after %.2f sec.\n", currentPump + 1, elapsed / 1000.0);
  //       }
  //       pumpRunning = false;
  //       currentPump = -1;

  //     } else {
  //       Serial1.println("❓ Unknown command. Use D:<pump>:<volume_ml> or S to stop.");
  //     }
  //   }

  //   if (pumpRunning && millis() - pumpStartTime >= pumpRunDuration) {
  //     digitalWrite(pumpPins[currentPump], LOW);
  //     Serial1.printf("✅ Pump %d finished. Dispensed volume complete.\n", currentPump + 1);
  //     pumpRunning = false;
  //     currentPump = -1;
  //   }
  // }

// #include <Arduino.h>

// // Function prototypes
// void pulseCounter0();
// void pulseCounter1();
// void pulseCounter2();
// void pulseCounter3();
// void pulseCounter4();
// void pulseCounter5();
// void setupFlowSensors();
// void calculateFlowRates();
// void displayFlowData();
// void checkLevelReached();

// // Sensor pins (PA0 to PA5)
// const byte flowSensorPins[6] = {PA0, PA1, PA2, PA3, PA4, PA5};
// float calibrationFactor = 4.5; // Adjust based on your sensor

// // Sensor variables
// volatile uint16_t pulseCount[6] = {0};
// float flowRates[6] = {0};
// unsigned long totalMilliLitres[6] = {0};
// bool levelReached[6] = {false};

// unsigned long previousMillis = 0;
// const unsigned long interval = 1000; // 1 second interval
// const unsigned int targetML = 500; // Target level in mL

// // Interrupt handlers array
// void (*interruptHandlers[6])() = {
//   pulseCounter0, pulseCounter1, pulseCounter2, 
//   pulseCounter3, pulseCounter4, pulseCounter5
// };

// void setup() {
//   Serial.begin(9600);
//   while (!Serial); // Wait for serial connection
  
//   setupFlowSensors();
//   Serial.println("\nFlow Sensor Test - 6 Channels");
//   Serial.println("----------------------------");
//   Serial.println("Target: 500mL per sensor");
//   Serial.println();
// }

// void loop() {
//   if (millis() - previousMillis >= interval) {
//     previousMillis = millis();
//     calculateFlowRates();
//     checkLevelReached();
//     displayFlowData();
//   }
// }

// // Individual interrupt handlers
// void pulseCounter0() { pulseCount[0]++; }
// void pulseCounter1() { pulseCount[1]++; }
// void pulseCounter2() { pulseCount[2]++; }
// void pulseCounter3() { pulseCount[3]++; }
// void pulseCounter4() { pulseCount[4]++; }
// void pulseCounter5() { pulseCount[5]++; }

// void setupFlowSensors() {
//   for (int i = 0; i < 6; i++) {
//     pinMode(flowSensorPins[i], INPUT_PULLUP);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[i]), 
//                    interruptHandlers[i], FALLING);
//   }
// }

// void calculateFlowRates() {
//   // Disable interrupts during calculation
//   for (int i = 0; i < 6; i++) {
//     detachInterrupt(digitalPinToInterrupt(flowSensorPins[i]));
//   }

//   for (int i = 0; i < 6; i++) {
//     flowRates[i] = ((1000.0 / interval) * pulseCount[i]) / calibrationFactor;
//     totalMilliLitres[i] += (flowRates[i] / 60) * 1000;
//     pulseCount[i] = 0;
//   }

//   // Re-enable interrupts
//   for (int i = 0; i < 6; i++) {
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[i]), 
//                   interruptHandlers[i], FALLING);
//   }
// }

// void checkLevelReached() {
//   for (int i = 0; i < 6; i++) {
//     if (totalMilliLitres[i] >= targetML && !levelReached[i]) {
//       levelReached[i] = true;
//     }
//   }
// }

// void displayFlowData() {
//   Serial.println("Sens\tL/min\tmL\tTotal mL\tStatus");
//   Serial.println("--------------------------------------");
  
//   for (int i = 0; i < 6; i++) {
//     Serial.print(i); Serial.print("\t");
//     Serial.print(flowRates[i], 2); Serial.print("\t");
//     Serial.print((flowRates[i] / 60) * 1000, 0); Serial.print("\t");
//     Serial.print(totalMilliLitres[i]); Serial.print("\t\t");
    
//     if (levelReached[i]) {
//       Serial.print("REACHED");
//     } else {
//       Serial.print("-");
//     }
//     Serial.println();
//   }
//   Serial.println();
// }