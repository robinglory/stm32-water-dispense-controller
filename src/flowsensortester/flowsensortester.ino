volatile int pulseCount = 0;
float calibrationFactor = 4.5;

unsigned long previousMillis = 0;
const unsigned long interval = 1000;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres = 0;

// Mega interrupt-capable pin
const byte flowSensorPin = 18;

void setup() {
  Serial.begin(9600);
  pinMode(flowSensorPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

  Serial.println("Flow Sensor Tester Started (Arduino Mega on D18)");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    detachInterrupt(digitalPinToInterrupt(flowSensorPin));

    flowRate = ((1000.0 / interval) * pulseCount) / calibrationFactor;
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;

    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.print(" L/min\t");
    Serial.print("This Interval: ");
    Serial.print(flowMilliLitres);
    Serial.print(" mL\t");
    Serial.print("Total: ");
    Serial.print(totalMilliLitres);
    Serial.println(" mL");

    pulseCount = 0;

    attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);
  }
}

void pulseCounter() {
  pulseCount++;
}
