#include "config.h"
#include <Arduino.h>
#include <Claw.hpp>
#include <Wheels.hpp>
#include <Servo.h>
#include <Ultrasonic.h>
#include "main.hpp"

static Wheels wheels;
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
  wheels.attach();
}

void loop()
{
  static uint8_t isStarted = LOW;

  // Timing
  uint32_t ms = millis();
  static uint32_t servoTime = 0;
  static uint32_t wheelTime = 0;
  static uint32_t ultrasonicTime = 0;

  // Write indicator LED
  digitalWrite(LED_BUILTIN, isStarted);

  // Log ultrasonic distance
#ifdef LOGGING
  if ((ms - ultrasonicTime) > 100)
  {
    ultrasonicTime = ms;
    Serial.print("Distance: ");
    Serial.println(ultrasonic.read());
  }
#endif

  if (!isStarted)
  {
    isStarted = digitalRead(PUSH_BUTTON);
  }
  else
  {
    /**
     * Main active loop
     */
    // Run wheels for 2 seconds then stop
    if (!wheelTime)
      wheelTime = ms;

    if ((ms - wheelTime) < 2000)
      wheels.forwards();
    else if ((ms - wheelTime) < 2100)
      wheels.stop();

    // Open/close claw every second
    if ((ms - servoTime) > 1000)
    {
      servoTime = ms;

      if (claw.getIsOpen())
        claw.close();
      else
        claw.open();
    }
  }
}
