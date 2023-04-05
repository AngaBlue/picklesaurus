# Picklesaurus - 2023 Weir Warman Competition Entry
Welcome to the Picklesaurus code repository bootstrapped with PlatformIO.

## Structure
This project uses PlatformIO's default project structure.

- `src/`: the high-level project logic.
  - `main.cpp`: the entry point of the project.  Contains logic that brings together all sensors, timing and actions.
- `lib/`: libraries created for this project.  These are abstractions that provide a declarative API for performing actions involving multiple inputs and outputs.
  - `Claw/`: a class for controlling the opening and closing of the claw.
  - `Wheels/`: a class for controlling the direction the robot moves using the wheels.
- `test/`: currently unused.

## Configuration
Pins and other settings can be configured in `include/pins.hpp` and `include/config.hpp` respectively.
