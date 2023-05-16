#include "PickleServo.hpp"
#include <Arduino.h>
#include <Servo.h>

void PickleServo::attach(uint8_t pin, uint8_t start)
{
  Servo::attach(pin);
  this->write(start);
}

void PickleServo::move(uint8_t angle, uint32_t time = 1000)
{
  // Calculate whether the angle should increment or decrement
  int start = this->read();
  int increment = (start < angle) ? 1 : -1;

  // Calculate the delay time in microseconds (milliseconds is not precise enough)
  int delayTime = 1000 * time / abs(angle - start);

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
