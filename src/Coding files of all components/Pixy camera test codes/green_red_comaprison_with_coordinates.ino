#include <Pixy2.h>

Pixy2 pixy;

void setup() {
  Serial.begin(9600);
  pixy.init();
}

void printSeparator() {
  Serial.println("------------------------------");
}

void loop() {
  int blocks = pixy.ccc.getBlocks();

  int largestArea = 0;  // Variable to track the largest area
  int closestColor = -1;  // Variable to track the color closest to the camera
  int closestWidth = 0;  // Variable to track the width of the closest color
  int closestHeight = 0;  // Variable to track the height of the closest color
  int closestX = 0;  // Variable to track the X coordinate of the closest color
  int closestY = 0;  // Variable to track the Y coordinate of the closest color

  for (int i = 0; i < blocks; i++) {
    int area = pixy.ccc.blocks[i].m_width * pixy.ccc.blocks[i].m_height;

    // Compare areas to determine the color closest to the camera
    if (area > largestArea) {
      largestArea = area;
      closestColor = pixy.ccc.blocks[i].m_signature;
      closestWidth = pixy.ccc.blocks[i].m_width;
      closestHeight = pixy.ccc.blocks[i].m_height;
      closestX = pixy.ccc.blocks[i].m_x;
      closestY = pixy.ccc.blocks[i].m_y;
    }
  }

  if (closestColor == 1) {
    Serial.print("Green obstacle detected. ");

    // Adjust turn based on X coordinate for green
    if (closestX < 80 || closestX > 240) {
      Serial.println("Make a slight left turn.");
    } else {
      Serial.println("Make a sharp left turn.");
    }

  } else if (closestColor == 2) {
    Serial.print("Red obstacle detected. ");

    if (closestX < 80 || closestX > 240) {
      Serial.println("Make a slight right turn.");
    } else {
      Serial.println("Make a sharp right turn.");
    }
  }

  Serial.print("Width: ");
  Serial.print(closestWidth);
  Serial.print(" Height: ");
  Serial.print(closestHeight);
  Serial.print(" X Coordinate: ");
  Serial.print(closestX);
  Serial.print(" Y Coordinate: ");
  Serial.println(closestY);

  printSeparator();

  delay(100); 
}
