#include "Wheels.hpp"

Wheels::Wheels() : motors{AF_DCMotor(1), AF_DCMotor(2), AF_DCMotor(3), AF_DCMotor(4)} {}

void Wheels::attach(uint8_t speed, const multipliers_t multipliers)
{
    this->speed = speed;

    for (int i = 0; i < 4; ++i)
    {
        this->motors[i].setSpeed(this->speed * ((float *)&multipliers)[i]);
        this->motors[i].run(RELEASE);
    }
}

void Wheels::stop()
{
    this->motors[0].run(RELEASE);
    this->motors[1].run(RELEASE);
    this->motors[2].run(RELEASE);
    this->motors[3].run(RELEASE);
}

void Wheels::forwards(uint32_t time)
{
    this->motors[0].run(FORWARD);
    this->motors[1].run(FORWARD);
    this->motors[2].run(FORWARD);
    this->motors[3].run(FORWARD);

    if (time)
    {
        delay(time);
        this->stop();
    }
}

void Wheels::backwards(uint32_t time)
{
    this->motors[0].run(BACKWARD);
    this->motors[1].run(BACKWARD);
    this->motors[2].run(BACKWARD);
    this->motors[3].run(BACKWARD);

    if (time)
    {
        delay(time);
        this->stop();
    }
}

void Wheels::left(uint32_t time)
{
    this->motors[0].run(FORWARD);
    this->motors[1].run(BACKWARD);
    this->motors[2].run(BACKWARD);
    this->motors[3].run(FORWARD);

    if (time)
    {
        delay(time);
        this->stop();
    }
}

void Wheels::right(uint32_t time)
{
    this->motors[0].run(BACKWARD);
    this->motors[1].run(FORWARD);
    this->motors[2].run(FORWARD);
    this->motors[3].run(BACKWARD);

    if (time)
    {
        delay(time);
        this->stop();
    }
}
