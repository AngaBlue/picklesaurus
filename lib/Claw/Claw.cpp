#include "Claw.h"
#include <Arduino.h>
#include <Servo.h>

Claw::Claw(uint8_t pin, uint8_t opened, uint8_t closed)
{
    Servo();

    this->opened = opened;
    this->closed = closed;

    // Attach the instance to the pin and set the min & max values
    this->attach(pin, 0, 179);

    // Start the claw open
    this->open();
}

void Claw::open()
{
    this->isOpen = true;
    this->write(this->opened);
    #ifdef LOGGING
    Serial.println("Claw: open");
    #endif
}

void Claw::close()
{
    this->isOpen = false;
    this->write(this->closed);
    #ifdef LOGGING
    Serial.println("Claw: closed");
    #endif
}

boolean Claw::getIsOpen()
{
    return this->isOpen;
}
