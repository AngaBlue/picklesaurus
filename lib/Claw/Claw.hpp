#include <Arduino.h>
#include <Servo.h>

/**
 * @class Claw
 * @brief A simple interface for opening and closing the claw declaratively.
 */
class Claw : private Servo
{
private:
    uint8_t opened;
    uint8_t closed;
    bool isOpen;

public:
    /**
     * @brief Attaches the claw to a pin.
     * 
     * @param pin The pin to attach the claw servo to.
     * @param opened The value from 0 - 179 which represents the opened state of the claw.
     * @param closed The value from 0 - 179 which represents the closed state of the claw.
     
     */
    void attach(uint8_t pin, uint8_t opened, uint8_t closed);

    /**
     * @brief Opens the claw.
     */
    void open();

    /**
     * @brief Closes the claw.
     */
    void close();

    /**
     * @brief Whether the claw is open or not.
     */
    boolean getIsOpen();
};
