// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
#include <AFMotor.h>

AF_DCMotor motor1(1); // Initialize a DC motor on channel 1 of the motor shield
AF_DCMotor motor2(2); // Initialize a DC motor on channel 1 of the motor shield
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

const int buttonPin = 2; // the number of the pushbutton pin
const int ledPin = 13;   // the number of the LED pin

// variables will change:
int buttonState = 0; // variable for reading the pushbutton status
int motorPin = 3;
void setup()
{
    // initialize the LED pin as an output:
    pinMode(ledPin, OUTPUT);
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
    motor1.setSpeed(200);
    motor2.setSpeed(200); // Set the motor speed to 200 (adjust as necessary)
    motor3.setSpeed(200);
    motor4.setSpeed(200);
}

void loop()
{
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH)
    {
        // turn LED on:
        digitalWrite(ledPin, HIGH);
        digitalWrite(motorPin, HIGH);
        motor1.run(FORWARD); // Run the motor forward
        motor2.run(FORWARD); // Run the motor forward
        motor3.run(FORWARD); // Run the motor forward
        motor4.run(FORWARD); // Run the motor forward
        delay(2000);
        digitalWrite(ledPin, LOW);
        motor1.run(RELEASE); // Run the motor stop
        motor2.run(RELEASE); // Run the motor stop
        motor3.run(RELEASE); // Run the motor stop
        motor4.run(RELEASE); // Run the motor stop
    }
}
