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
  wheels.attach(SPEED, {WHEEL_1_MULT, WHEEL_2_MULT, WHEEL_3_MULT, WHEEL_4_MULT});
}

void loop()
{
  if (digitalRead(PUSH_BUTTON) == HIGH)
  {
    /**
     * Squash ball collection
     */

    scoop.move(SCOOP_DOWN, 100);
    delay(1000);

    // Collect squash balls
    wheels.forwards();
    delay(1500);
    scoop.move(SCOOP_UP);
    delay(100);
    wheels.stop();
    arm.move(ARM_UP, 1000);

    // Move backwards
    wheels.backwards(950);

    // Turn to the tube
    turn(RIGHT, 65);

    // Move against wall
    wheels.forwards(2200);

    // Drop balls & wait for them to fall
    scoop.move(SCOOP_DEPOSIT - 55);
    delay(250);

    // Shake the tube
    for (uint8_t i = 0; i < 2; ++i)
    {
      scoop.move(SCOOP_DEPOSIT - 45);
      delay(WIGGLE_TIME);
      scoop.move(SCOOP_DEPOSIT);
      // Let the balls roll out
      delay(2400);
    }

    scoop.move(SCOOP_UP, 500);

    // Move backwards from tube
    wheels.backwards(750);

    /**
     * Tennis ball collection
     */

    // Move to collect tennis balls
    turn(LEFT, 62);
    wheels.forwards(950);

    // Move scoop and arm down to collect tennis balls
    turn(LEFT, 62); // was 90 which was too much
    for (int i = ARM_UP; i > ARM_DOWN; i -= 2)
    {
      arm.move(i, 200);
      delay(100);
    }
    scoop.move(SCOOP_DOWN, 500);
    // drive forward and collect the big green balls
    wheels.forwards(1800);
    delay(1000);
    // move away from wall slightly
    wheels.backwards(250);

    // Move scoop & arm up
    scoop.move(103);
    delay(250);
    scoop.move(SCOOP_UP);
    delay(300);
    arm.move(ARM_UP + 5, 1000);

    // Move backwards &  turn around
    wheels.backwards(400);
    // start turning the robot around 180 degrees to get into position for tennis deposit:
    turn(RIGHT, 135);

    wheels.backwards(967);
    // ideally we are now facing the tube and flush against the cardboard

    // now deposit the big green balls
    scoop.move(SCOOP_DEPOSIT_TENNIS, 1000);

    for (int i = 80; i <= ARM_DEPOSIT_TENNIS; i += 5)
    {
      arm.move(i, 500);
      delay(250);
    }

    delay(1000);
    scoop.move(65, 2000); // here is where they ought to drop out?
    delay(2700);

    /**
     * Return to start
     */

    arm.move(ARM_DOWN, 2000);
    // 75 to clear the zone of where a tennis ball may potentially be lying
    wheels.forwards(250);
    turn(RIGHT, 10);
    wheels.forwards(750);
    turn(RIGHT, 75);
    wheels.forwards(2200);

    // Reset scoop & arm position
    arm.move(ARM_DOWN, 2000);
    scoop.move(SCOOP_START+1,1000);

    // profit ???
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
