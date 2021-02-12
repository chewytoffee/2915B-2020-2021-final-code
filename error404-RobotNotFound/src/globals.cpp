#include "main.h"

// GLOBALS
pros::Motor backLeft (2,false);
pros::Motor frontLeft (4,false);  //reversed
pros::Motor backRight (3,true);
pros::Motor frontRight (5,true);
pros::Motor lowerRollers (6,false);
pros::Motor upperRollers (7,true);
pros::Motor leftIntake (8,false);
pros::Motor rightIntake (9,true);
pros::Controller master (pros::E_CONTROLLER_MASTER);
pros::Optical optical (10);
