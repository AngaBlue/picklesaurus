#include "Wheels.hpp"

Wheels::Wheels() : motors{AF_DCMotor(1), AF_DCMotor(2), AF_DCMotor(3), AF_DCMotor(4)} {}

void Wheels::attach(uint8_t speed, float multipliers[4])
{
    this->speed = speed;

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
    this->motors[0].run(FORWARD);
    this->motors[1].run(FORWARD);
    this->motors[2].run(FORWARD);
    this->motors[3].run(FORWARD);
}

void Wheels::backwards()
{
    this->motors[0].run(BACKWARD);
    this->motors[1].run(BACKWARD);
    this->motors[2].run(BACKWARD);
    this->motors[3].run(BACKWARD);
}

void Wheels::left()
{
    this->motors[0].run(FORWARD);
    this->motors[1].run(BACKWARD);
    this->motors[2].run(BACKWARD);
    this->motors[3].run(FORWARD);
}

void Wheels::right()
{
    this->motors[0].run(BACKWARD);
    this->motors[1].run(FORWARD);
    this->motors[2].run(FORWARD);
    this->motors[3].run(BACKWARD);
}
