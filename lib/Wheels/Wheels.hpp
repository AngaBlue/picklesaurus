#include <Arduino.h>
#include <AFMotor.h>

class Wheels
{
private:
    AF_DCMotor motors[4];
    uint8_t speed;

public:
    Wheels(uint8_t speed);

    void attach(float mutlipliers[4]);

    void forwards();
    void backwards();
    void left();
    void right();
    void stop();
};
