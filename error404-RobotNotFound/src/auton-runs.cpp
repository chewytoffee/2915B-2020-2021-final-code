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
    leftIntake.move_voltage(0);
    rightIntake.move_voltage(0);
    return true;
}

bool launchForTime(int runTime, int voltage, int entryTime){
    while( (pros::millis() - entryTime) <runTime){
        lowerRollers.move_voltage(voltage);
        upperRollers.move_voltage(voltage);
    }
    lowerRollers.move_voltage(0);
    upperRollers.move_voltage(0);
    return true;
}

// tune respective kP, kD, maxVolts and settle time
myPID translateP(1.25, 0.0, 7000, 900);
myPID angleP(4.5, 0.0, 0.0, 0.0);
myPID rotationP(1.35, 0.0, 10000, 250);

// left 1 ball
void left1B() {
    /* START AUTON SEQUENCE */
    /* END AUTON SEQUENCE */
}

// left 2 ball
void left2B() {

}

// right 1 ball
void right1B() {
    /* START AUTON SEQUENCE */
    /* END AUTON SEQUENCE */
}

// right 2 ball
void right2B() {

}

// no auton run (sets voltage to 0)
void noAuto() {
    translateP.setDriveVoltage(0, 0);
}