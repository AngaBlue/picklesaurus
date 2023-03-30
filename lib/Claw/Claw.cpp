#include "Claw.h"
#include <Arduino.h>
#include <Servo.h>

Claw::Claw(uint8_t opened, uint8_t closed)
{
    Servo();

    this->opened = opened;
    this->closed = closed;
}

void Claw::attach(uint8_t pin)
{
    Servo::attach(pin);
    this->open();
}

void Claw::open()
{
    this->isOpen = true;
    this->write(this->opened);
}

void Claw::close()
{
    this->isOpen = false;
    this->write(this->closed);
}

boolean Claw::getIsOpen()
{
    return this->isOpen;
}
