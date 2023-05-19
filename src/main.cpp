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

    scoop.move(SCOOP_DOWN, 250);
    delay(500);

    // Collect squash balls
    wheels.forwards();
    delay(1250);
    scoop.move(SCOOP_UP, 250);
    wheels.stop();
    arm.move(ARM_UP, 2000);

    // Move backwards
    wheels.backwards(1069);

    // Turn to the tube
    turn(RIGHT, 80);

    // Move against wall
    wheels.forwards(1800);

    // Drop balls
    scoop.move(SCOOP_DEPOSIT, 500);
    scoop.move(SCOOP_DEPOSIT, 500);
    delay(2000);
    // Shake the tube
    for (int i = 0; i < 2; i++)
    {
      scoop.move(SCOOP_DEPOSIT - 45, WIGGLE_TIME);
      delay(WIGGLE_TIME / 3);
      scoop.move(SCOOP_DEPOSIT);
      // Let the balls roll out
      delay(2400);
    }
    delay(269); // 269 delay arbitrily added seems kinda cool??
    scoop.move(SCOOP_UP, 500);

    // Move backwards from tube
    wheels.backwards(750);

    /**
     * Tennis ball collection
     */

    // Move to collect tennis balls
    turn(LEFT, 88);
    wheels.forwards(1100);

    // Move scoop and arm down to collect tennis balls
    turn(LEFT, 50); // was 90 which was too much
    arm.move(ARM_DOWN, 2000);
    scoop.move(SCOOP_DOWN, 500);
    // drive forward and collect the big green balls
    wheels.forwards(1550);
    delay(2000);
    // move away from wall slightly
    wheels.backwards(100);

    // rotate left and right to knock last tennis ball away
    scoop.move(103, 150);
    turn(LEFT, 70);
    delay(333);
    turn(RIGHT, 30 + 70);
    delay(333);
    turn(LEFT, 30);
    delay(333);
    scoop.move(SCOOP_UP, 1000);
    arm.move(ARM_UP + 5, 1000);

    // Move backwards &  turn around
    wheels.backwards(400);
    // start turning the robot around 180 degrees to get into position for tennis deposit:
    turn(RIGHT, 148);

    wheels.backwards(950);
    // ideally we are now facing the tube and flush against the cardboard

    // now deposit the big green balls
    scoop.move(SCOOP_TENNIS_DEPOSIT, 1000);

    for (int i = 80; i < 161; i = i + 5)
    {
      arm.move(i, 500);
      delay(300);
    }
    delay(250);           // probably not necassary
    scoop.move(84, 2000); // here is where they ought to drop out?
    delay(4000);

    /**
     * Return to start
     */

    arm.move(ARM_DOWN, 2000);
    delay(2000);
    wheels.forwards(600);
    // 75 to clear the zone of where a tennis ball may potentially be lying
    turn(RIGHT, 75); 
    wheels.forwards(700);
    turn(RIGHT, 35);
    wheels.forwards(1550);

    // Reset scoop & arm position
    arm.move(ARM_DOWN, 2000);
    scoop.move(SCOOP_START);

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
