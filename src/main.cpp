#include <Arduino.h>
#include <pins.h>

//Arduino PWM Speed Control：
int E1 = 5;  // Motor2 Speed
int M1 = 4;  // Motor2 Dir
int E2 = 6;   // Motor1 Speed                   
int M2 = 7;   // Motor1 Dir 


void setup() {
  // put your setup code here, to run once:
  motorOnWithSpeed();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void motorOnWithSpeed(){
    digitalWrite(M1,LOW);   
    digitalWrite(M2, LOW);       
    analogWrite(E1,80);
    analogWrite(E2,80);
}
