//this test code is without gyroscope

#include <Servo.h>

//Declaring pins for Ultrasonic Sensors
const int TRIGGER_PIN_FRONT = 36;  // Front sonar sensor trigger pin
const int ECHO_PIN_FRONT = 37;     // Front sonar sensor echo pin


const int TRIGGER_PIN_LEFT_CORNER = 38;  // Left sonar sensor trigger pin
const int ECHO_PIN_LEFT_CORNER = 39;     // Left sonar sensor echo pin

const int TRIGGER_PIN_RIGHT_CORNER = 40;  // Right sonar sensor trigger pin
const int ECHO_PIN_RIGHT_CORNER = 41;     // Right sonar sensor echo pin

//declaring pins for mian motor
const int ren = 4;
const int len = 9;
const int pwm = 6;

//encoder
const int ENCA = 20; // Encoder pulse input A
const int ENCB = 21; // Encoder pulse input B
volatile long posi = 0;  // Use long to accommodate larger position values
// Stop the car if pulse count is greater than 34000
int lapCount = 1;
const int totalLaps = 3;  // Set the total number of laps


//creating instace for servo control
Servo steeringServo;

//values for Servo control
const int mean_servo_value = 95;                //stering straight
const int extreme_left_servo = 115;              //steering Extreme left 50
const int extreme_right_servo = 75;            //steering Extreme right 150
int current_servo_position = mean_servo_value;  //this will store the position of servo at every instant

//variables to store front, left and right distances
int distanceFront, distanceLeft, distanceRight;

//normal vs turnspeed
const int forwardSpeed = 140;   // Adjust this value for the desired forward speed
const int backwardSpeed = 140;  // Adjust this value for the desired forward speed
const int turnSpeed = 140;      // Adjust this value for the desired turn speed

const int corner_distance = 26;  //robo will move back if detected corner at this distance

//temp
int turn;



void setup() {
  Serial.begin(9600);
  steeringServo.attach(19);

  // Motor
  pinMode(ren, OUTPUT);
  pinMode(len, OUTPUT);
  pinMode(pwm, OUTPUT);

  // Sonar Sensors
  pinMode(TRIGGER_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);
  //cornered left & right
  pinMode(TRIGGER_PIN_LEFT_CORNER, OUTPUT);
  pinMode(ECHO_PIN_LEFT_CORNER, INPUT);
  pinMode(TRIGGER_PIN_RIGHT_CORNER, OUTPUT);
  pinMode(ECHO_PIN_RIGHT_CORNER, INPUT);
  // encoder
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);

  Serial.println("Car position calculation using encoder pulses...");

}

void loop() {
  stopCar();

  move('F');
  while (!checkCorner()) {
    updateDistance();
    //will stay straight if nothing detected
    stayStraight();
    stopCar();
  }

  if (checkCorner()) {
    cornerTurn();
    //Serial.println("corner---");
  }
}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.0343 / 2;
  return distance;
}

void updateDistance() {
  distanceFront = getDistance(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
  distanceLeft = getDistance(TRIGGER_PIN_LEFT_CORNER, ECHO_PIN_LEFT_CORNER);
  distanceRight = getDistance(TRIGGER_PIN_RIGHT_CORNER, ECHO_PIN_RIGHT_CORNER);

  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  Serial.print(" cm, Left Distance: ");
  Serial.print(distanceLeft);
  Serial.print(" cm, Right Distance: ");
  Serial.print(distanceRight);
  Serial.print(" cm");
  Serial.print(" cm, Current position: ");
  Serial.println(posi);
}

int move(char movement) {
  if (movement == 'S') {
    digitalWrite(ren, 0);
    digitalWrite(len, 0);
    analogWrite(pwm, 0);
  }
  if (movement == 'F') {
    digitalWrite(ren, 1);
    digitalWrite(len, 0);
    analogWrite(pwm, forwardSpeed);
  }
  if (movement == 'B') {
    digitalWrite(ren, 0);
    digitalWrite(len, 1);
    analogWrite(pwm, backwardSpeed);
  }
}

//Checking Functions
bool checkCorner() {
  if ((distanceFront <= corner_distance))
    return true;
  else return false;
}


//turning functions
void cornerTurn() {
  turn = current_servo_position;
  int initialTurn = turn;

  move('B');
  if (turn < mean_servo_value) {
    turn = extreme_left_servo;
  } else if (turn > mean_servo_value) {
    turn = extreme_right_servo;
  } else {
    turn = mean_servo_value;
  }

  steeringServo.write(turn);

  while (true) {
    updateDistance();
    if (distanceFront >= 26)
      break;
  }
  move('S');
  delay(40);

  steeringServo.write(initialTurn);
  current_servo_position = initialTurn;
  move('F');
  delay(30);
}


void stayStraight() {
  turn = current_servo_position;

  if (distanceLeft < distanceRight) {
    turn -= 20;
  } else if (distanceRight < distanceLeft) {
    turn += 20;
  }

  if (turn > extreme_left_servo) {
    turn = extreme_left_servo;
  }
  if (turn < extreme_right_servo) {
    turn = extreme_right_servo;
  }

  steeringServo.write(turn);
  current_servo_position = turn;
  delay(30);
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    posi++;
  } else {
    posi--;
  }
}

void stopCar(){
  if (posi > 28000 && (distanceFront > 150 && distanceFront < 170)) {
    // Reset encoder position after each lap
    if (lapCount == totalLaps) {
      digitalWrite(ren, LOW);
      digitalWrite(len, LOW);
      analogWrite(pwm, 0);
      Serial.println("All laps completed. Stopping the car.");
      while (true)
        ;  // This will halt the program and effectively stop the car
    } else {
      // Increment the lap count
      lapCount++;
      posi = 0;
    }
  }
}
