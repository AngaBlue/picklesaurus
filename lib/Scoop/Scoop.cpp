#include "Scoop.hpp"
#include <Arduino.h>
#include <Servo.h>

void Scoop::attach(uint8_t pin, uint8_t up, uint8_t down)
{
    Servo::attach(pin,up,down);

    this->upPos = up;
    this->downPos = down;

    this->up();
}

void Scoop::up()
{
    this->isUp = true;
    this->write(this->upPos);
}

void Scoop::down()
{
    this->isUp = false;
    this->write(this->downPos);
}

boolean Scoop::getIsUp()
{
    return this->isUp;
}
