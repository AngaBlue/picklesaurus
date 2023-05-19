#include "PickleServo.hpp"
#include <Arduino.h>
#include <Servo.h>

void PickleServo::attach(uint8_t pin, uint8_t start)
{
  Servo::attach(pin);
  this->write(start);
}

void PickleServo::move(int32_t angle, uint32_t time)
{
  // Calculate whether the angle should increment or decrement
  int32_t start = this->read();
  int32_t increment = (start < angle) ? 1 : -1;

  // Calculate the delay time in microseconds (milliseconds is not precise enough)
  uint32_t delayTime = 1000 * time / abs(angle - start);

  if (delayTime)
  {
    for (int32_t current = start; current != angle; current += increment)
    {
      this->write(current);
      delayMicroseconds(delayTime);
    }
  }
  // Ensure servo reaches the finishing angle
  this->write(angle);
}
