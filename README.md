# Retro2Cbot
Bot race

## Layout

1. common/
The common folder contains all reusable functions, helpers, and modules that can be shared across different robots or by others.
Think of this folder as a shared library that simplifies coding and prevents duplication.
1.1 constant/
This folder includes all constant variables used throughout the robot project.
Contents typically include:
Pin assignments for engine, sonar, motor, reflective sensors.
Robot configuration values
Global constants used across modules
Important Note
Inside motor.h, each robot model has its own pin values.
Make sure to select the correct robot model before compiling, because every robot uses different pin configurations.
1.2 robot/
Contains all functionality that controls robot behavior. The main area where robot actions are implemented.

This folder also includes any necessary setup functions for hardware pins.

Example:
src/common/robot/motor/motor.h → Provides the setupMotor() function.
1.2.1 motor
Contains all motor-related functions:
Motor setup and configuration
Pulse counting
1.2.2 movement
Includes movement functions, such as:
forward()
backward()
rotate()
switchDirection()
stopMotors()
These functions use the lower-level motor logic to create complex actions.
1.2.3 sonar
Contains sonar-related operations:
Sonar setup
Distance calculation
Object-detection logic
This module is responsible for gathering environment data from the sonar sensor.
1.3 tools/
A set of additional utility modules that extend functionality.
Think of it as a place for self-made helper libraries.
Example:
Timer - simplifies the use of millis() for time-based operations.
These utilities are optional but make development easier and more modular.
1.3.1 tests/
Contains tests used for validating robot features.
Included examples:
Pulse counting tests
Basic movement tests
Validation of sonar functionality (In the future)
This folder is helpful for debugging and verifying robot behavior before running full programs.



2. maps_program/
This folder contains three different map programs implemented for the robot.
Each map program provides unique logic or navigation strategies for the robot to follow.
This is where high-level robot behavior scenarios are implemented.
3. main.cpp
The entry point of the application.
Responsibilities:
Initializes required modules
Selects which map program or testing logic to run
Starts the robot workflow
The execution of the whole project begins from this file.



## Teamates
- Fumbre[Vladyslav] 
- franciscpime[Francisco]
- Exenytre[Nicolo] 
- Sunnyaaa001[Sunny]
- LocalRaven[Aria] 
- Uraibixn[Uraib]
- Carolina (personal inspiration)


