#include "main.h"

// GLOBALS
pros::Motor backLeft (2,true);
pros::Motor frontLeft (4,true);  //reversed
pros::Motor backRight (3,false);
pros::Motor frontRight (5,false);
pros::Motor upperRollers (7,false);
pros::Controller master (pros::E_CONTROLLER_MASTER);
pros::Optical optical (10);
