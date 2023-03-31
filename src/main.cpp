#include "config.h"
#include <Arduino.h>
#include <Claw.hpp>
#include <Wheels.hpp>
#include "main.hpp"

static Wheels wheels;
static Claw claw;

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
  claw.attach(CLAW_SERVO, CLAW_OPEN, CLAW_CLOSED);
  wheels.attach();
}

void loop()
{
  static uint8_t isStarted = LOW;

  // Timing
  static uint32_t servoTime = 0;
  static uint32_t wheelTime = 0;
  uint32_t ms = millis();

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

    // Open/close claw every 3 seconds
    if ((ms - servoTime) > 3000)
    {
      servoTime = ms;

      if (claw.getIsOpen())
        claw.close();
      else
        claw.open();
    }

    // Run wheels for 2 seconds then stop
    if (!wheelTime)
    {
      wheelTime = ms;
    }
    else
    {
      if ((ms - wheelTime) > 2000)
        wheels.stop();
      else
        wheels.forwards();
    }
  }
}
