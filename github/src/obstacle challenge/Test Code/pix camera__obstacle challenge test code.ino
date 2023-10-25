#include <Servo.h>
#include <Pixy2.h>
Pixy2 pixy;



const int TRIGGER_PIN_FRONT =36;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 37;     // Front sonar sensor echo pin
const int TRIGGER_PIN_LEFT = 38;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT = 39;     // Left sonar sensor echo pin
const int TRIGGER_PIN_RIGHT = 40;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT = 41;     // Right sonar sensor echo pin


const int motor1 = 4;const int motor2 =9;const int pwm=6;
Servo steeringServo;

//red and green led
int red=52;
int green=53;

const int forwardSpeed = 150; // Adjust this value for the desired forward speed
const int turnSpeed = 130;     // Adjust this value for the desired turn speed  
void setup(){
 Serial.begin(9600);
   pixy.init();
   //red and green leds
  pinMode(red, OUTPUT);pinMode(green, OUTPUT);  
  steeringServo.attach(15);
  // Motor
  pinMode(motor1, OUTPUT);pinMode(pwm, OUTPUT);pinMode(motor2, OUTPUT);
  // Sonar Sensors
  pinMode(TRIGGER_PIN_FRONT, OUTPUT);pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);pinMode(ECHO_PIN_RIGHT, INPUT);
  pixy.setLamp(0, 0);  // Turn on the lamp (LED) on Pixy2

}

  int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  unsigned long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.0343 / 2;
  return distance;  }

void loop(){
digitalWrite(green , LOW);
digitalWrite(red , LOW);

int distanceFront = getDistance(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
int distanceLeft = getDistance(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
int distanceRight = getDistance(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);

Serial.print("Front Distance: ");
Serial.print(distanceFront);
Serial.print(" cm, Left Distance: ");
Serial.print(distanceLeft);
Serial.print(" cm, Right Distance: ");
Serial.print(distanceRight);
Serial.println(" cm");

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
      digitalWrite(green , HIGH);
      digitalWrite(red ,LOW);
      steeringServo.write(110);
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      analogWrite(pwm, 130);
      delay(200);
        
          if (distanceLeft<=25){    
      steeringServo.write(70);
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      analogWrite(pwm, 130);
      delay(50);
      }
      
      } 
      else if (closestColor == 2) {
      Serial.print("Red obstacle detected. ");
      digitalWrite(red,HIGH);
      digitalWrite(green , LOW);
      steeringServo.write(70);
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      analogWrite(pwm, 130);
      delay(200);
      
      if (distanceRight<=25){    
      steeringServo.write(140);
      digitalWrite(motor1, HIGH);
      digitalWrite(motor2, LOW);
      analogWrite(pwm, 130);
      delay(50);
      }
    }
if (distanceFront >= 0  && distanceFront <= 50 && closestColor != 2 && closestColor != 1) {
if ( distanceLeft < distanceRight ) {
    steeringServo.write(70);
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
    analogWrite(pwm, turnSpeed);
    delay(600);}
else if ( distanceRight < distanceLeft ) {
    // Turn left
    steeringServo.write(160);
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
    analogWrite(pwm, turnSpeed);
    delay(600);}}
else {
  steeringServo.write(120);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  analogWrite(pwm, forwardSpeed);}

if ( distanceFront >=40 && closestColor != 2 && closestColor != 1)
  {
if ( distanceLeft < distanceRight ) {
    // Obstacle detected on the left as well
    // Turn right
    steeringServo.write(105);
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
    analogWrite(pwm, 130);
    delay(50);}
if ( distanceRight < distanceLeft ) {
    // Obstacle detected on the left as well
    // Turn right
    steeringServo.write(135);
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);
    analogWrite(pwm, 130);
    delay(50);}}

}









