#include "main.hpp"

Wheels wheels;
PickleServo scoop;
PickleServo arm;
QMC5883LCompass compass;

void setup()
{
#ifdef LOGGING
  // Begin serial communication for logging
  Serial.begin(115200);
#endif

  /**
   * Initialise pins
   */
  pinMode(PUSH_BUTTON, INPUT);

  /**
   * Initialise components
   */
  compass.init();

  // Attach servos to pins and specify starting positions
  scoop.attach(SCOOP_SERVO, SCOOP_START);
  arm.attach(ARM_SERVO, ARM_DOWN);

  // Attach motors to pins and set speed & speed multipliers for each wheel
  const float MULTIPLIERS[4] = {WHEEL_1_MULT, WHEEL_2_MULT, WHEEL_3_MULT, WHEEL_4_MULT};
  wheels.attach(SPEED, MULTIPLIERS);
}

void loop()
{
  if (digitalRead(PUSH_BUTTON) == HIGH)
  {
    scoop.move(SCOOP_DOWN, 0);

    // Move forwards to collect the tennis balls
    wheels.forwards();
    delay(750);
    scoop.move(SCOOP_UP);
    delay(500);
    wheels.stop();

    // Turn left to face the tube backwards
    turn(RIGHT, 90);

    // Move against the wall
    wheels.backwards();
    delay(1000);
    wheels.stop();

    // Slowly move the arm up to dump the tennis balls
    arm.move(ARM_UP, 2000);
    delay(500);

    // Move the arm down again
    arm.move(ARM_DOWN, 2000);

    // Turn to face the squash balls & move the scoop down
    scoop.move(SCOOP_DOWN);

    // Move forwards to collect the squash balls
    wheels.forwards();
    delay(750);
    scoop.move(SCOOP_UP);
    delay(500);
    wheels.stop();

    // Turn backwards to face the tube
    turn(RIGHT, 180);

    // Move against the wall
    wheels.backwards();
    delay(1000);
    wheels.stop();

    // Slowly move the arm up to dump the tennis balls
    arm.move(ARM_UP, 2000);
    delay(500);

    // Move the arm down again
    arm.move(ARM_DOWN, 2000); 
    scoop.move(SCOOP_START);

    // Turn to face the start area
    turn(LEFT, 90);

    // Move back to the start area
    wheels.forwards();
    delay(750);
    wheels.stop();
  }
  else
  {
#ifdef LOGGING
    // Read & print azimuth
    compass.read();
    int azimuth = compass.getAzimuth();

    char output[32];
    sprintf(output, "Azimuth: %3d", azimuth);
    Serial.println(output);
#endif
  }
}

void fix_range(range_t *range)
{
  // Fix minimum
  if (range->min < 0)
    range->min += 360;
  else if (range->min >= 360)
    range->min -= 360;

  // Fix maximum
  if (range->max < 0)
    range->max += 360;
  else if (range->max >= 360)
    range->max -= 360;
}

bool check_range(range_t *range, int azimuth)
{
  if (range->min < range->max)
    return azimuth >= range->min && azimuth <= range->max;
  else
    return azimuth >= range->min || azimuth <= range->max;
}

void turn(Direction direction, int degrees)
{
  // Get the starting azimuth and the sign of the degrees
  compass.read();
  int start = compass.getAzimuth();

  // For positive degrees: turn left, for negative degrees: turn left
  if (direction == LEFT)
    wheels.left();
  else
    wheels.right();

  // Calculate the range of azimuths to turn through
  range_t range = {start + (degrees * direction), start + (degrees + 5 * direction)};

  // If the direction is negative, switch the minimum and maximum
  if (direction == -1)
    range = {range.max, range.min};
  fix_range(&range);

  // Stop when the azimuth is within the range
  while (!check_range(&range, compass.getAzimuth()))
  {
     compass.read();
  }

  wheels.stop();
}
