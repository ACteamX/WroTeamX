// Include libraries

#include <Wire.h>
#include <Adafruit_TCS34725.h>


// Initialize Color Sensor object
// See parameters: https://learn.adafruit.com/adafruit-color-sensors/program-it
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_60X);


char col, currentCol, prevCol = 'g';
int colCount = -1;

// setup() is executed once when the Arduino starts
void setup() {

  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);

  // Serial communication to output the value in the serial monitor
  Serial.begin(9600);
  Serial.println("Makerblog.at - MuMs Color Sensor");

  // Check whether Color Sensor also reports back
  if (tcs.begin()) {
    // Everything OK
    Serial.println("Sensor found");
  } else {
    // No sensor found. Freeze program at this point
    Serial.println("TCS34725 not found... process stopped!");
    while (1)
      ;  // Stop!
  }
}

// loop() repeats as long as the Arduino is running
void loop() {

  // The sensor returns values for R, G, B, and a clear value
  uint16_t clearcol, red, green, blue;
  float average, r, g, b;
  delay(10);  // Color measurement takes c. 50ms
  tcs.getRawData(&red, &green, &blue, &clearcol);

  // My attempt at color determination for
  // the 5 M&M colors red, green, blue, orange, and yellow

  // Find the average of RGB
  average = (red + green + blue) / 3;
  // Color values by average,
  // all values now move around 1
  r = red / average;
  g = green / average;
  b = blue / average;


  if (r > g && r > b) {
    currentCol = 'r';
    analogWrite(A2, 168);
    analogWrite(A3, 0);
  }
  if (b > r && b > g) {
    currentCol = 'b';
    analogWrite(A2, 0);
    analogWrite(A3, 168);
  }
  if (g > r && g > b) {
    currentCol = 'g';
    analogWrite(A2, 0);
    analogWrite(A3, 0);
  }

  if (currentCol != prevCol) {
    colCount++;
    prevCol = currentCol;
    Serial.println(colCount);
  }
}