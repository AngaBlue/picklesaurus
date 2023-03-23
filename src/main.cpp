#include <Arduino.h>
#include <pins.h>

void setup()
{
  // Initialize pin modes
  pinMode(MOTOR_DIR_1, OUTPUT);
  pinMode(MOTOR_SPEED_1, OUTPUT);
  pinMode(MOTOR_DIR_2, OUTPUT);
  pinMode(MOTOR_SPEED_2, OUTPUT);

  motorOnWithSpeed();
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void motorOnWithSpeed()
{
  // Set the motor direction to forward
  digitalWrite(MOTOR_DIR_1, LOW);
  digitalWrite(MOTOR_DIR_2, LOW);

  // Set the motor speed using PWM
  analogWrite(MOTOR_SPEED_1, 80);
  analogWrite(MOTOR_SPEED_2, 80);
}
