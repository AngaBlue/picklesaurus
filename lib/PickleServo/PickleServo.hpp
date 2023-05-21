#include <Arduino.h>
#include <Servo.h>

/**
 * @brief A simple interface for moving the scoop smoothly & declaratively.
 */
class PickleServo : private Servo
{
public:
    /**
     * @brief Attaches the scoop to a pin.
     *
     * @param pin The pin to attach the scoop servo to.
     * @param start The value from 0 - 180 which represents starting position of the scoop.
     */
    void attach(uint8_t pin, uint8_t start);

    /**
     * @brief Smoothly moves the servo to the specified angle.
     *
     * @param angle The angle to move the servo to.
     * @param time The time in milliseconds to take to move the servo.  Defaults to 0.  If the time is 0, the servo will move as fast as possible.
     */
    void move(int32_t angle, uint32_t time = 0);
};
