#include <Arduino.h>
#include <Claw.h>
#include "main.h"
#include "config.h"

static Claw claw = Claw(CLAW_SERVO, CLAW_OPEN, CLAW_CLOSED);

void setup()
{
  // Logging
  #ifdef LOGGING
  Serial.begin(115200);
  #endif

  // Initialize pin modes
  pinMode(MOTOR_DIR_1, OUTPUT);
  pinMode(MOTOR_SPEED_1, OUTPUT);
  pinMode(MOTOR_DIR_2, OUTPUT);
  pinMode(MOTOR_SPEED_2, OUTPUT);
  pinMode(PUSH_BUTTON, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  static uint8_t isStarted = LOW;

  // Timing
  static uint32_t servoTime = 0;
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

    // Open/close claw every second
    if ((ms - servoTime) > 1000)
    {
      #ifdef LOGGING
      Serial.println("Changing");
      #endif
      servoTime = ms;

      if (claw.getIsOpen())
        claw.close();
      else
        claw.open();
    }
  }
}
