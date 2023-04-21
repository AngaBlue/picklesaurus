#include "config.hpp"
#include <Arduino.h>
#include <Scoop.hpp>
#include <Wheels.hpp>
#include "main.hpp"

static Wheels wheels(SPEED);
static Scoop scoop;
static Servo arm;

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
  arm.attach(ARM_SERVO);
}

void loop()
{
  if (digitalRead(PUSH_BUTTON) == HIGH)
  {
    wheels.forwards();
    scoop.down();
    delay(2000);
    wheels.stop();
  } else {
    scoop.up();
  }
}
