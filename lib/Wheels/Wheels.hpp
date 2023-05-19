#include <Arduino.h>
#include <AFMotor.h>

class Wheels
{
private:
    AF_DCMotor motors[4];
    uint8_t speed;

public:
    Wheels();

    /**
     * @brief Attaches the wheels to the motor shield.
     *
     * @param speed The speed of the wheels.
     * @param multipliers The speed multipliers for each wheel. This is used to account for differences in the wheels.
     */
    void attach(uint8_t speed, const float multipliers[4]);

    /**
     * @brief Moves all the wheels forwards.
     *
     * @param time The time in milliseconds to move the wheels for.  Defaults to 0.  If the time is 0, the wheels will move forever.
     */
    void forwards(uint32_t time = 0);

    /**
     * @brief Moves all the wheels backwards.
     *
     * @param time The time in milliseconds to move the wheels for.  Defaults to 0.  If the time is 0, the wheels will move forever.
     */
    void backwards(uint32_t time = 0);

    /**
     * @brief Moves the left wheels backwards and the right wheels forwards.
     * 
     * @param time The time in milliseconds to move the wheels for.  Defaults to 0.  If the time is 0, the wheels will move forever.
     */
    void left(uint32_t time = 0);

    /**
     * @brief Moves the right wheels backwards and the left wheels forwards.
     * 
     * @param time The time in milliseconds to move the wheels for.  Defaults to 0.  If the time is 0, the wheels will move forever.
     */
    void right(uint32_t time = 0);

    /**
     * @brief Stops all the wheels.
     */
    void stop();
};
