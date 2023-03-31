#include "Claw.hpp"
#include <Arduino.h>
#include <Servo.h>

void Claw::attach(uint8_t pin, uint8_t opened, uint8_t closed)
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
