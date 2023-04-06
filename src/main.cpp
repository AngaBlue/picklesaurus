#include "config.hpp"
#include <Arduino.h>
#include <Claw.hpp>
#include <Wheels.hpp>
#include <Servo.h>
#include <Ultrasonic.h>
#include "main.hpp"

static Wheels wheels(SPEED);
static Claw claw;
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
  claw.attach(CLAW_SERVO, CLAW_OPENED, CLAW_CLOSED);
  float multipliers[4] = {WHEEL_1_MULT, WHEEL_2_MULT, WHEEL_3_MULT, WHEEL_4_MULT};
  wheels.attach(multipliers);
}

void loop()
{
  static uint8_t isStarted = LOW;

  // Timing
  uint32_t ms = millis();
  static uint32_t time = 0;

  // Write indicator LED
  digitalWrite(LED_BUILTIN, isStarted);

  if (!isStarted)
  {
    isStarted = digitalRead(PUSH_BUTTON);
  }
  else
  {
    /**
     * Main active loop
     */
    if (!time)
      time = ms;

    uint32_t diff = ms - time;

    if (diff < 1000)
    {
      // Move claw down
      claw.close();
    }
    else if (diff < 3000)
    {
      // Move forward
      wheels.forwards();
    }
    else if (diff < 4000)
    {
      wheels.stop();
      claw.open();
    }
  }
}
