// #include <Arduino.h>
// #include <stdarg.h>
// #define NUM_SENSORS 9
// #define NUM_PUMPS 9
// #define CLK PB13
// #define DIR PB12
// // Flow sensor input pins (EXTI capable)
// uint8_t flowSensorPins[NUM_SENSORS] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA8};
// volatile uint16_t flowCounts[NUM_SENSORS] = {0};

// // Pump output pins
// uint8_t pumpPins[NUM_PUMPS] = {PB9, PB8, PB7, PB6, PB5, PB4, PB3, PA15, PA12};
// uint16_t test = 1;
// void flowISR0() { flowCounts[0]++; }
// void flowISR1() { flowCounts[1]++; }
// void flowISR2() { flowCounts[2]++; }
// void flowISR3() { flowCounts[3]++; }
// void flowISR4() { flowCounts[4]++; }
// void flowISR5() { flowCounts[5]++; }
// void flowISR6() { flowCounts[6]++; }
// void flowISR7() { flowCounts[7]++; }
// void flowISR8() { flowCounts[8]++; }

// void attachInterrupts()
// {
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[0]), flowISR0, RISING);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[1]), flowISR1, RISING);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[2]), flowISR2, RISING);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[3]), flowISR3, RISING);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[4]), flowISR4, RISING);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[5]), flowISR5, RISING);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[6]), flowISR6, RISING);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[7]), flowISR7, RISING);
//     attachInterrupt(digitalPinToInterrupt(flowSensorPins[8]), flowISR8, RISING);
// }

// // Control pump states based on bitmask
// void runPump(uint16_t data, ...)
// {
//     va_list args;
//     va_start(args, data);
//     uint16_t waterAmount[NUM_PUMPS] = {0};

//     // Extract water amount per pump
//     for (uint8_t i = 0; i < NUM_PUMPS; i++)
//     {
//         if (data & (0x01 << i))
//         {
//             // Serial1.printf("Pump %d: %d\t", i, va_arg(args, int));
//             waterAmount[i] = va_arg(args, int);
//         }
//     }
//     va_end(args);

//     // Turn on selected pumps
//     for (uint8_t i = 0; i < NUM_PUMPS; i++)
//     {
//         if (data & (0x01 << i))
//         {
//             digitalWrite(pumpPins[i], HIGH);
//             flowCounts[i] = 0; // Reset flow count
//         }
//     }

//     // Wait until the required water amount is reached
//     bool running = true;
//     while (running)
//     {
//         running = false;
//         for (uint8_t i = 0; i < NUM_PUMPS; i++)
//         {
//             if ((data & (0x01 << i)) && flowCounts[i] < (waterAmount[i] * 10))
//             {
//                 running = true;
//                 // Serial1.printf("Pump %d Flow: %d\t", i, flowCounts[i]);
//                 for (uint8_t i = 0; i < NUM_PUMPS; i++)
//                 {
//                     Serial1.printf(" %d: %d\t", i, flowCounts[i]);
//                 }
//                 Serial1.println("\n\n\n\n\n");
//             }
//             else
//             {
//                 digitalWrite(pumpPins[i], LOW);
//             }
//         }
//         Serial1.println();
//     }
//     Serial1.printf("Motor data: %d\t", data);
//     for (uint8_t i = 0; i < NUM_PUMPS; i++)
//     {
//         Serial1.printf("P%d: %d\t", i, flowCounts[i]);
//         flowCounts[i] = 0;
//     }
//     Serial1.println("Done");
// }

// void setup()
// {
//     Serial1.begin(115200);
//     pinMode(PC13, OUTPUT);
//     digitalWrite(PC13, LOW);
//     // Configure flow sensor pins as input
//     for (uint8_t i = 0; i < NUM_SENSORS; i++)
//     {
//         pinMode(flowSensorPins[i], INPUT_PULLUP);
//     }
//     attachInterrupts();

//     // Configure pump control pins as output
//     for (uint8_t i = 0; i < NUM_PUMPS; i++)
//     {
//         pinMode(pumpPins[i], OUTPUT);
//         digitalWrite(pumpPins[i], LOW);
//     }
    
//     // delay(10000);
//     Serial1.println("Input : ");
// }

// void loop()
// {


//     if (!Serial1.available()) return;
//     char c = Serial1.read();
//     switch (c)
//     {
//     case 'M':
//         runPump(0x07, 30, 30, 40); // 0b 0000 0111
//         break;
    
//     default:
//         break;
//     }
//     // char c = 0;
//     // uint16_t temp1;
//     // uint16_t temp2;
//     // uint16_t motordata = 0;              // Changed to uint16_t
//     // uint16_t wateramount[NUM_PUMPS] = {0};
//     // uint8_t index = 0;

//     // while (c != 'E')
//     // {
//     //     c = Serial1.read();
//     //     switch (c)
//     //     {
//     //     case 'M':
//     //         temp1 = Serial1.read();
//     //         temp2 = Serial1.read();
//     //         temp2 = temp2 - '0'; // Convert ASCII to integer
//     //         motordata = (temp2 << 8) | temp1; // Ensure 16-bit value
//     //         break;
//     //     case ' ':
//     //         if (index < NUM_PUMPS)
//     //         {
//     //             wateramount[index] = Serial1.parseInt();
//     //             index++;
//     //         }
//     //         break;
//     //     default:
//     //         break;
//     //     }

//     // }
    
//     // if (c != 'E')
//     // {
//     //     Serial1.println("Error: End character 'E' not received.");
//     //     return;
//     // }
//     // runPump(motordata, wateramount[0],wateramount[1],wateramount[2],wateramount[3],wateramount[4],wateramount[5],wateramount[6],wateramount[7],wateramount[8]);
//     // Serial1.println("Input : ");


//     // for (size_t i = 0; i < 9; i++)
//     // {
//     //     // runPump(test << i, 30);
//     //     digitalWrite(pumpPins[i], HIGH);
//     //     delay(1000);
//     // }
    
    
// }
