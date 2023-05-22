#include "PickleServo.hpp"

void PickleServo::attach(int pin, int start)
{
  Servo::attach(pin);
  this->write(start);
}

void PickleServo::move(int angle, unsigned int time)
{
  int start = this->read();

  // The servo is already at the angle
  if (start == angle)
    return;

  // Calculate whether the angle should increment or decrement
  int increment = (start < angle) ? 1 : -1;

  // Calculate the delay time in microseconds (milliseconds is not precise enough)
  // 'time' is casted to a float to ensure we don't overflow before dividing
  unsigned long delayTime = (float) time * 1000 / abs(angle - start);

  if (delayTime)
  {
    for (int current = start; current != angle; current += increment)
    {
      this->write(current);
      delayMicroseconds(delayTime);
    }
  }
  
  // Ensure servo reaches the finishing angle
  this->write(angle);
}
