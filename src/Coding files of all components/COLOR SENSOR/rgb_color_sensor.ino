// Include libraries

#include <Wire.h>
#include <Adafruit_TCS34725.h>


// Initialize Color Sensor object
// See parameters: https://learn.adafruit.com/adafruit-color-sensors/program-it
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

// setup() is executed once when the Arduino starts
void setup() {

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
    while (1); // Stop!
  }

}

int count_blue=0;

// loop() repeats as long as the Arduino is running
void loop() {
void color_sensor();

}


void color_sensor(){

  // The sensor returns values for R, G, B, and a clear value
  uint16_t clearcol, red, green, blue;
  float average, r, g, b;
  delay(10); // Color measurement takes c. 50ms
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


if(r>g && r>b){
  Serial.print(" Red:");
  Serial.println(r);
}
if(b>r && b>g){
   count_blue++;
   Serial.print(count_blue);
  Serial.print("   Blue:");
  Serial.println(b);
 
 
}
if(g>r && g>b){
  Serial.print(" green:");
  Serial.println(g);
}
  delay(1);
}