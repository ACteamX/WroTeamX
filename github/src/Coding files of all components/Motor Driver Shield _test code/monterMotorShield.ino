int motorForward=4; int motorBackward=9; 
int speed=6;

void setup() {
  pinMode motorForward,OUTPUT);pinMode motorBackward,OUTPUT);pinMode(speed,OUTPUT);
}

void loop() {
digitalWrite motorForward,1);digitalWrite motorBackward,0);analogWrite(speed,200);
delay(2000);

digitalWrite motorForward,0);digitalWrite motorBackward,1);analogWrite(speed,200);
delay(2000);
/*
s.write(180);digitalWrite motorForward,1);digitalWrite motorBackward,0);analogWrite(speed,200);
delay(2000);
s.write(90);digitalWrite motorForward,0);digitalWrite motorBackward,0);analogWrite(speed,100);
delay(1000);
*/
}
