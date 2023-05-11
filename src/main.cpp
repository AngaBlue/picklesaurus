#include "config.hpp"
#include <Arduino.h>
#include <Scoop.hpp>
#include <Wheels.hpp>
#include <QMC5883LCompass.h>
#include <Arm.hpp>
#include "main.hpp"

static Wheels wheels(SPEED);
static Scoop scoop;
static Arm arm;
static QMC5883LCompass compass;

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
  compass.init();
  //scoop.attach(SCOOP_SERVO,SCOOP_UP,SCOOP_DOWN);
  //float multipliers[4] = {WHEEL_1_MULT, WHEEL_2_MULT, WHEEL_3_MULT, WHEEL_4_MULT};
  //wheels.attach(multipliers);
  //arm.attach(ARM_SERVO,ARM_UP,ARM_DOWN);
}

void loop()
{
  if (digitalRead(PUSH_BUTTON) == HIGH)
  {
    scoop.down();
    delay(3000);
    scoop.up();
    delay(1000);
    arm.down();
    wheels.left_reverse();
    wheels.stop();
  } else {
    //scoop.up();
    //arm.down();

    // Read compass
    compass.read();
    int a = compass.getAzimuth();
#ifdef LOGGING
    Serial.println(a);
#endif
  }
}
