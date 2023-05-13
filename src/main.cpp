#include "config.hpp"
#include <Arduino.h>
#include <Scoop.hpp>
#include <Wheels.hpp>
#include <QMC5883LCompass.h>
#include <Ultrasonic.h>
#include "main.hpp"

static Wheels wheels(SPEED);
static Scoop scoop;
static QMC5883LCompass compass;
static Ultrasonic ultrasonic(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO);

int startingAzimuth = 0;

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
  scoop.attach(SCOOP_SERVO,SCOOP_UP,SCOOP_DOWN);
  float multipliers[4] = {WHEEL_1_MULT, WHEEL_2_MULT, WHEEL_3_MULT, WHEEL_4_MULT};
  wheels.attach(multipliers);

  compass.read();
  startingAzimuth = compass.getAzimuth();
}

void loop()
{
  if (digitalRead(PUSH_BUTTON) == HIGH)
  {
    // Pick up & dump tennis balls
    pickup();
    dump();

    // Turn right 90 degrees
    turn(-90);
    wheels.stop();

    // Pick up & dump squash balls
    pickup();
    dump();

    // Turn right 90 degrees
    turn(-90);

    // Go home
    wheels.forwards();
    delay(1500);
    wheels.stop();
  } else {
    scoop.up();

    // Read compass
    compass.read();
    int azimuth = compass.getAzimuth();
#ifdef LOGGING
    char output[32];
    sprintf(output, "Starting Azimuth: %3d Azimuth: %3d", startingAzimuth, azimuth);
    Serial.println(output);
#endif
  }
}

void fix_range(range_t *range)
{
  // Fix minimum
  if (range->min < 0) range->min += 360;
  else if (range->min >= 360) range->min -= 360;

  // Fix maximum
  if (range->max < 0) range->max += 360;
  else if (range->max >= 360) range->max -= 360;
}

bool check_range(range_t *range, int azimuth)
{
  #ifdef LOGGING
    char output[32];
    sprintf(output, "Starting Azimuth: %3d Azimuth: %3d", startingAzimuth, azimuth);
    Serial.println(output);
#endif

  if (range->min < range->max) return azimuth >= range->min && azimuth <= range->max;
  else return azimuth >= range->min || azimuth <= range->max;
}

void turn(int degrees)
{
  int direction = degrees < 0 ? -1 : 1;
  // if (direction == LEFT) degrees = degrees * 1.1;
  // else degrees = degrees * 0.9;

  // Get the starting azimuth and the sign of the degrees
  compass.read();
  int start = compass.getAzimuth();

  // For positive degrees: turn left, for negative degrees: turn left
  if (direction == LEFT) wheels.left();
  else wheels.right();

  // Calculate the range of azimuths to turn through
  range_t range = {start + degrees, start + degrees + 5 * direction};
  if (direction == RIGHT) range = {range.max, range.min};
  fix_range(&range);

  // Stop when the azimuth is within the range
  while (!check_range(&range, compass.getAzimuth()))
  {
    compass.read();
  }  
}

void pickup()
{
    scoop.down();
    delay(500);
    wheels.forwards();
    delay(2000);
    scoop.up();
    delay(500);
}

void dump()
{
  // Dump tennis balls
  scoop.down();
  delay(500);
  wheels.backwards();
  delay(500);
  wheels.stop();
  delay(1000);
  scoop.up();
} 
