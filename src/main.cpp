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
  static uint8_t isStarted = LOW;

  // Timing
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
    // Log ultrasonic distance every 100ms
#ifdef LOGGING
    static uint32_t ultrasonicTime = 0;
    if (ms - ultrasonicTime > 100)
    {
      ultrasonicTime = ms;
      Serial.print("Distance: ");
      Serial.println(ultrasonic.read());
    }
#endif

    // Move wheels and scoop
    static uint32_t time = ms;
    uint32_t diff = ms - time;

    if (diff < 1000)
    {
      // Move scoop down
      scoop.down();
    }
    else if (diff < 3000)
    {
      // Move forward
      wheels.forwards();
    }
    else if (diff < 4000)
    {
      wheels.stop();
      scoop.up();
    }
  }
}
