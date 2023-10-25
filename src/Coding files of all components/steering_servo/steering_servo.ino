//note : This is a sample code and variables can be changed in final code

#include<Servo.h>
Servo s;

void setup(){
s.attach(19);
}
void loop(){
s.write(95);
delay(1000);
s.write(180);
delay(1000);
}