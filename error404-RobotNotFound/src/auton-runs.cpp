#include "main.h"
#include "custom/pid.h"
#include "custom/globals.h"
#include "pros/motors.h"

int leftSensors,rightSensors,sensors,switchVal;

void runAuton (int route){
    switch (route){
        case 0:
            break;
    }
}
bool driveFwd(int target, int voltage){
    while(sensors < (target -5 )){
        leftSensors = (backLeft.get_position() + frontLeft.get_position())/2;
        rightSensors = (backRight.get_position() + frontRight.get_position())/2;
        sensors = (leftSensors + rightSensors)/2;
        backLeft.move_voltage(voltage);
        backRight.move_voltage(voltage);
        frontLeft.move_voltage(voltage);
        frontRight.move_voltage(voltage);
    }
    backLeft.move_voltage(0);
    backRight.move_voltage(0);
    frontLeft.move_voltage(0);
    frontRight.move_voltage(0);
    return true;
}

bool turnRight(int target, int voltage){
    while(sensors < (target -5 )){
        leftSensors = (backLeft.get_position() + frontLeft.get_position())/2;
        rightSensors = (backRight.get_position() + frontRight.get_position())/2;
        sensors = (leftSensors + rightSensors)/2;
        backLeft.move_voltage(-voltage);
        backRight.move_voltage(-voltage);
        frontLeft.move_voltage(voltage);
        frontRight.move_voltage(voltage);
    }
    backLeft.move_voltage(0);
    backRight.move_voltage(0);
    frontLeft.move_voltage(0);
    frontRight.move_voltage(0);
    return true;
}

bool intakeForTime(int runTime, int voltage,int entryTime){
    while( (pros::millis() - entryTime) < runTime){
        leftIntake.move_voltage(voltage);
        rightIntake.move_voltage(voltage);
    }
    leftIntake.move(0);
    rightIntake.move(0);
    return true;
}

bool launchForTime(int runTime, int voltage, int entryTime){
    while( (pros::millis() - entryTime) <runTime){
        lowerRollers.move_voltage(voltage);
        upperRollers.move_voltage(voltage);
    }
}
void auton1(){
    switch (switchVal){
        case 0 :
            if (driveFwd(1200,600)){
                switchVal = 1;
            }
    }
}