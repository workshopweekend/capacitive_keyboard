// Capacitive Keyboard + LED Matrix bubbles
// by J.D. Zamfirescu
// Last update: June 2014
// capacitive_keayboard.ino

#include "HT1632.h" // Get this library here: http://github.com/workshopweekend/HT1632
#include <CapacitiveSensor.h>

#define DATA 2
#define WR   3
#define CS   4

const int numSensors = 6;
const int inputPins[] = {6, 7, 8, 9, 10, 11};

HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
CapacitiveSensor *sensors[6];

void setup() {
  matrix.begin(HT1632_COMMON_16NMOS);
  matrix.clearScreen();
  for (int i = 0; i < numSensors; ++i) {
    sensors[i] = new CapacitiveSensor(12, inputPins[i]);
  }
  Serial.begin(9600);
}

void loop() {
  // move bubbles up!
  for (int x = 0; x < matrix.width(); ++x) {
    for (int y = 0; y < matrix.height(); ++y) {
      if (matrix.getPixel(x, y)) {
        matrix.clrPixel(x, y);
        if (y > 0) {
          matrix.setPixel(x, y-1);
        }
      }
    }
  }

  loadTimings();
  printTimings();

  // set new bubbles!
  for (int i = 0; i < numSensors; ++i) {
    if (isTriggered(i)) {
      matrix.setPixel(i*4+1+random(2), matrix.height()-1);
    }
  }
  
  matrix.writeScreen();
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

boolean isTriggered(int index) {
  return timings[index] > 20;
}