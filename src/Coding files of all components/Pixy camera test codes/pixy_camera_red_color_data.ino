#include <Pixy2.h>

Pixy2 pixy;

const uint16_t redSignature = 2;  // Red signature ID
int redCount = 0;  // Variable to count red detections

void setup() {
  Serial.begin(9600);
  pixy.init();
  pixy.changeProg("color_connected_components");
  pixy.setLamp(0, 1);  // Turn on the lamp (LEDs) on Pixy
}

void loop() {
  uint16_t blocks = pixy.ccc.getBlocks();

  // Variable to track if red color is detected
  bool redDetected = false;

  // Process each detected block
  for (int i = 0; i < blocks; i++) {
    // Check if red obstacle detected
    if (pixy.ccc.blocks[i].m_signature == redSignature) {
      Serial.println("Red obstacle detected");
      redDetected = true;
      redCount++;  // Increment the red detection count
    }
  }

  // If no red detected, print a message
  if (!redDetected) {
    Serial.println("No red obstacle detected");
  }

  // Print the red detection count
  Serial.print("Red detection count: ");
  Serial.println(redCount);

  delay(100);  // Add a delay to prevent excessive printing
}
