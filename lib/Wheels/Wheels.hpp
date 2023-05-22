#include <Arduino.h>
#include <AFMotor.h>

struct
{
    float front_left;
    float front_right;
    float back_left;
    float back_right;
} typedef multipliers_t;

/**
 * @brief A simple interface for moving all wheels together & declaratively.
 * 
 * @note The wheels are numbered as follows:
 * 0: Front left
 * 1: Front right
 * 2: Back left
 * 3: Back right
 */
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
    void attach(uint8_t speed, const multipliers_t multipliers);

    /**
     * @brief Moves all the wheels forwards.
     *
     * @param time The time in milliseconds to move the wheels for.  Defaults to 0.  If the time is 0, the wheels will move forever.
     */
    void forwards(unsigned long time = 0);

    /**
     * @brief Moves all the wheels backwards.
     *
     * @param time The time in milliseconds to move the wheels for.  Defaults to 0.  If the time is 0, the wheels will move forever.
     */
    void backwards(unsigned long time = 0);

    /**
     * @brief Moves the left wheels backwards and the right wheels forwards.
     *
     * @param time The time in milliseconds to move the wheels for.  Defaults to 0.  If the time is 0, the wheels will move forever.
     */
    void left(unsigned long time = 0);

    /**
     * @brief Moves the right wheels backwards and the left wheels forwards.
     *
     * @param time The time in milliseconds to move the wheels for.  Defaults to 0.  If the time is 0, the wheels will move forever.
     */
    void right(unsigned long time = 0);

    /**
     * @brief Stops all the wheels.
     */
    void stop();
};
