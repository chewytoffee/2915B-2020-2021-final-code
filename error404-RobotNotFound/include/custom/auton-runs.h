#include "main.h"
#include "custom/pid.h"
#include "custom/globals.h"

extern bool intakeForTime(int runTime, int voltage,int entryTime);
extern bool launchForTime(int runTime, int voltage, int entryTime);
// auton run declaration
void left1B();
void left2B();
void right1B();
void right2B();
void noAuto();