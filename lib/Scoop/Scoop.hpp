#include <Arduino.h>
#include <Servo.h>

/**
 * @class Scoop
 * @brief A simple interface for opening and closing the scoop declaratively.
 */
class Scoop : private Servo
{
private:
    uint8_t upPos;
    uint8_t downPos;
    bool isUp;

public:
    /**
     * @brief Attaches the scoop to a pin.
     * 
     * @param pin The pin to attach the scoop servo to.
     * @param up The value from 0 - 180 which represents the up state of the scoop.
     * @param down The value from 0 - 180 which represents the down state of the scoop.
     
     */
    void attach(uint8_t pin, uint8_t up, uint8_t down);

    /**
     * @brief Move the scoop up.
     */
    void up();

    /**
     * @brief Moves the scoop down.
     */
    void down();

    /**
     * @brief Whether the scoop is up or not.
     */
    boolean getIsUp();
};
