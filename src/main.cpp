#include "config.hpp"
#include <Arduino.h>
#include <Scoop.hpp>
#include <Wheels.hpp>
#include <Servo.h>
#include <Ultrasonic.h>
#include "main.hpp"

static Wheels wheels(SPEED);
static Scoop scoop;
static Servo servo;
static Ultrasonic ultrasonic(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO);

void setup()
{
#ifdef LOGGING
  // Logging
  Serial.begin(115200);
#endif

  // Initialise pin modes
  pinMode(PUSH_BUTTON, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialise components
  scoop.attach(SCOOP_SERVO, SCOOP_UP, SCOOP_DOWN);
  float multipliers[4] = {WHEEL_1_MULT, WHEEL_2_MULT, WHEEL_3_MULT, WHEEL_4_MULT};
  wheels.attach(multipliers);
}

void loop()
{
  if (digitalRead(PUSH_BUTTON) == HIGH)
  {
    scoop.down();
    delay(3000);
  } else {
    scoop.up();
  }
}
