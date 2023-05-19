#include "config.hpp"
#include <Arduino.h>
#include <PickleServo.hpp>
#include <Wheels.hpp>
#include <QMC5883LCompass.h>
#include <Ultrasonic.h>

struct
{
  int min;
  int max;
} typedef range_t;

enum
{
  LEFT = -1,
  RIGHT = 1
} typedef Direction;

/**
 * @brief Fix a range so that it is between 0 and 360 degrees.
 *
 * @param range The range to fix.
 */
void fix_range(range_t *range);

/**
 * @brief Check if an azimuth is within a range.
 *
 * @param range The range to check. The minimum azimuth may be greater than the maximum azimuth if the range wraps around 360 degrees.
 * @param azimuth The azimuth to check.
 * @return Whether the azimuth is within the range.
 */
bool check_range(range_t *range, int azimuth);

/**
 * @brief Turn the robot in a direction by a number of degrees.
 *
 * @param direction The direction to turn in, either LEFT or RIGHT.
 * @param degrees The number of degrees to turn by.
 */
void turn(Direction direction, int degrees);
