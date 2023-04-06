#include "Wheels.hpp"

Wheels::Wheels(uint8_t speed) : motors{AF_DCMotor(1), AF_DCMotor(2), AF_DCMotor(3), AF_DCMotor(4)}
{
    this->speed = speed;
}

void Wheels::attach(float multipliers[4])
{
    for (int i = 0; i < 4; i++)
    {
        this->motors[i].setSpeed(this->speed * multipliers[i]);
        this->motors[i].run(RELEASE);
    }
}

void Wheels::stop()
{
    for (int i = 0; i < 4; i++)
    {
        this->motors[i].run(RELEASE);
    }
}

void Wheels::forwards()
{
    for (int i = 0; i < 4; i++)
    {
        this->motors[i].run(FORWARD);
    }
}

void Wheels::backwards()
{
    for (int i = 0; i < 4; i++)
    {
        this->motors[i].run(BACKWARD);
    }
}

void Wheels::left()
{
    for (int i = 0; i < 4; i++)
    {
        this->motors[i].run(i % 2 == 0 ? FORWARD : BACKWARD);
    }
}

void Wheels::right()
{
    for (int i = 0; i < 4; i++)
    {
        this->motors[i].run(i % 2 != 0 ? FORWARD : BACKWARD);
    }
}
