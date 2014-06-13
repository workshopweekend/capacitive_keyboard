// Circular Grapher
// by J.D. Zamfirescu
// Last update: June 2014
// circular_graph.pde

import processing.serial.*;

Serial port;
String serialInterface = "/dev/tty.usbmodem1411";

final int numSamples = 60;
final int numSources = 6;
int[][] values;
int[] hues = {0, 40, 60, 120, 240, 300};

void setup() {
  size(512, 512);
  background(255);
  port = new Serial(this, serialInterface, 9600);
  values = new int[numSources][numSamples];
  colorMode(HSB, 360, 100, 100);
}

int ptr = 0;

void drawValues() {
  background(0);
  strokeWeight(4);
  strokeCap(SQUARE);
  for (int i = 0; i < numSamples; ++i) {
    float startx = width/2 + width/8*cos(TWO_PI/numSamples * i);
    float starty = height/2 + height/8*sin(TWO_PI/numSamples * i);
    for (int source = 0; source < numSources; ++source) {
      stroke(hues[source], 100, 100);
      float x = startx + max(values[source][i] * width/120/numSources, 3) * cos(TWO_PI/numSamples * i);
      float y = starty + max(values[source][i] * height/120/numSources, 3) * sin(TWO_PI/numSamples * i); 
      line(startx, starty, x, y);
      // add some buffer between segments
      startx = x + width/100 * cos(TWO_PI/numSamples * i);
      starty = y + height/100 * sin(TWO_PI/numSamples * i);
    }
  }
}

void handleData(int[] samples) {
  for (int source = 0; source < samples.length; ++source) {
    values[source][ptr] = samples[source];
  }
  ptr = (ptr + 1) % numSamples;
  drawValues();
}  

void draw() {
  readSerial();
}

void readSerial() {
  String s = null;
  while ((s = port.readStringUntil('\n')) != null) {
    String[] parts = s.substring(0, s.length()-2).split(",");

    if (parts.length == numSources) {
      int[] samples = new int[numSources];
      for (int i = 0; i < numSources; ++i) {
        samples[i] = int(parts[i]);
      }
      handleData(samples);
    }
  }
}