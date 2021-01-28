#include "main.h"

// GLOBALS
pros::Motor backLeft (2,false);
pros::Motor frontLeft (4,false);  //reversed
pros::Motor backRight (3,true);
pros::Motor frontRight (5,true);
pros::Motor upperRollers (7,false);
pros::Controller master (pros::E_CONTROLLER_MASTER);
