# Picklesaurus - 2023 Weir Warman Competition Entry
Welcome to the Picklesaurus code repository for entry into the 2023 Wier Warman competition.

## Structure
This project uses PlatformIO's default project structure.

- `src/`: the high-level project logic.
  - `main.cpp`: the entry point of the project.  Contains logic that brings together all sensors, timing and actions.
- `lib/`: libraries created for this project.  These are abstractions that provide a declarative API for performing actions involving multiple inputs and outputs.
  - `PickleServo/`: a class for controlling the movement of a servo motor smoothly.
  - `Wheels/`: a class for controlling the direction the robot moves using the wheels.

## Configuration
Pins and other settings can be configured in `include/pins.hpp` and `include/config.hpp` respectively.

## Picklesaurus
Picklesauras, the name given to our robot came 1st runner-up in the 2023 Weir Warman Monash Malaysia campus competition.  It is capable of completing the entire course in roughly 50 seconds; collecting & depositing 3 squash balls and 3 tennis balls into their respective tubes.
