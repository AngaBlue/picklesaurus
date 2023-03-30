#include <Arduino.h>
#include <Servo.h>
#include "main.h"
#include "pins.h"

static Servo claw;

void setup()
{
  // Initialize pin modes
  pinMode(MOTOR_DIR_1, OUTPUT);
  pinMode(MOTOR_SPEED_1, OUTPUT);
  pinMode(MOTOR_DIR_2, OUTPUT);
  pinMode(MOTOR_SPEED_2, OUTPUT);
  pinMode(PUSH_BUTTON, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  claw.attach(CLAW_SERVO);
  claw.write(0);

  motorOnWithSpeed();
}

void loop()
{
  static uint8_t isStarted = LOW;

  static uint32_t last_time = 0;
  uint32_t ms = millis();

  // Write indicator LED
  digitalWrite(LED_BUILTIN, isStarted);

  if (!isStarted)
  {
    isStarted = digitalRead(PUSH_BUTTON);
  }
  else
  {
    // Main active loop
    static uint8_t position_counter = 0;

    if ((ms - last_time) > 20)
    {
      last_time = ms;

      uint8_t pos;

      position_counter++;
      if (position_counter < 180) {
        pos = position_counter;
      } else {
        pos = 359 - position_counter;

        if (position_counter >= 359) {
          position_counter = 0;
        }
      }

      claw.write(pos);
    }
  }
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
