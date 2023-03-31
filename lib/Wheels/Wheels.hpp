#include <Arduino.h>
#include <AFMotor.h>

class Wheels
{
private:
    AF_DCMotor motors[4];

public:
    Wheels();

    void attach();

    void forwards();
    void backwards();
    void left();
    void right();
    void stop();
};
