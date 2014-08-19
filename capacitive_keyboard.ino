// Capacitive Keyboard + LED Matrix bubbles
// by J.D. Zamfirescu
// Last update: June 2014
// capacitive_keyboard.ino

#include <CapacitiveSensor.h>

const int numSensors = 6;
const int inputPins[] = {6, 7, 8, 9, 10, 11};

HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
CapacitiveSensor *sensors[6];

void setup() {
  for (int i = 0; i < numSensors; ++i) {
    sensors[i] = new CapacitiveSensor(12, inputPins[i]);
  }
  Serial.begin(9600);
}

void loop() {
  loadTimings();
  printTimings();

  delay(20);
}

long timings[] = {0, 0, 0, 0, 0, 0};

void loadTimings() {
  for (int i = 0; i < numSensors; ++i) {
    timings[i] = sensors[i]->capacitiveSensor(10);
  }
}

void printTimings() {
  for (int i = 0; i < numSensors; ++i) {
    if (i != 0) {
      Serial.print(",");
    }
    Serial.print(timings[i]);
  }
  Serial.println();
}
