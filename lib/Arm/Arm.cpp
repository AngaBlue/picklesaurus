#include "Arm.hpp"
#include <Arduino.h>
#include <Servo.h>

void Arm::attach(uint8_t armPin, uint8_t armUp, uint8_t armDown)
{
    Arm::attach(armPin,armUp,armDown);

    this->armUpPos = armUp;
    this->armDownPos = armDown;

    this->up();
}

void Arm::up()
{
    this->armIsUp = true;
    this->write(this->armUpPos);
}

void Arm::down()
{
    this->armIsUp = false;
    this->write(this->armDownPos);
}

boolean Arm::getIsUp()
{
    return this->armIsUp;
}
