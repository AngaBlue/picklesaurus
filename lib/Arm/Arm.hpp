#include <Arduino.h>
#include <Servo.h>

/**
 * @class Arm
 * @brief A simple interface for manoeuvring the robotic arm to lift and retract the collection mechanism.
 */
class Arm : private Servo
{
private:
    uint8_t armUpPos;
    uint8_t armDownPos;
    bool armIsUp;

public:
    /**
     * @brief Attaches the arm to a pin.
     * 
     * @param armPin The pin to attach the arm servo to.
     * @param armUp The value from 0 - 180 which represents the up state of the arm.
     * @param armDown The value from 0 - 180 which represents the down state of the arm.
     
     */
    void attach(uint8_t armPin, uint8_t armUp, uint8_t armDown);

    /**
     * @brief moves the arm up.
     */
    void up();

    /**
     * @brief moves the arm down.
     */
    void down();

    /**
     * @brief checks whether the arm is up or down.
     */
    boolean getIsUp();
};