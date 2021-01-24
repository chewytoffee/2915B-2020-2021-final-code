#include "main.h"
#include "globals.h"


bool enableDrive = false;
bool enableStrafe = false;


//pasted from vexCode PID tutorial
double signnum_c(double x) {
  if (x > 0.0) return 1.0;
  if (x < 0.0) return -1.0;
  return x;
}

//settings for x axis
float kP = 0.0;
float kI = 0.0;
float kD = 0.0;

//settings for y axis

float kPS = 0.0;
float kIS = 0.0;
float kDS = 0.0;

//variables for x axis
int integral, totalError, error, delta, sensors, power, lDriveSensors, rDriveSensors;
int maxIntegral = 300;
int integralBound = 3;
int prevError = 0;

//variables for y axis
int integralStrafe, totalStrafeError, strafeError, deltaStrafe, strafeSensors, strafePower, lStrafeSensors, rStrafeSensors;
int maxStrafeIntegral = 300;
int strafeIntegralBound = 3;
int prevStrafeError = 0;

//for resetting the sensors
void resetSensors(){
  backLeft.tare_position();
  backRight.tare_position();
  frontLeft.tare_position();
  frontRight.tare_position();
}


void driveStraight(int target){
  while(enableDrive){

    lDriveSensors = ((backLeft.get_position() + frontLeft.get_position())/2);
    rDriveSensors = ((backRight.get_position() + frontRight.get_position())/2);
    sensors = ((lDriveSensors +rDriveSensors)/2);

    error = target - sensors;

    if(abs(error) < integralBound){
    totalError += error;
    }  else {
    totalError = 0;
    }

    //caps integral (apparetly i have no idea how this works)
    totalError = abs(totalError) > maxIntegral ? signnum_c(totalError) * maxIntegral : totalError;

    //derivitive
    delta = error - prevError;
    prevError = error;

    //gets the power
    power= error*kP + integral*kI + delta*kD;

    //sends the power to the motors
    backLeft.move(power);
    backRight.move(power);
    frontLeft.move(power);
    frontRight.move(power);

    pros::delay(15);
  }
}

void strafeStraight(int target){
  while (enableStrafe){

    lStrafeSensors = ((frontLeft.get_position() - frontRight.get_position())/2);
    rStrafeSensors = ((backRight.get_position() - backLeft.get_position())/2);
    strafeSensors = ((lStrafeSensors + rStrafeSensors)/2);

    strafeError = target - strafeSensors;

    if (abs(strafeError) < strafeIntegralBound){
      totalStrafeError += strafeError;
    } else {
      totalStrafeError = 0;
    }
    totalStrafeError = abs(totalStrafeError) > maxStrafeIntegral ? signnum_c(totalStrafeError) *maxStrafeIntegral :totalStrafeError;

    //derivitive
    deltaStrafe = strafeError - prevStrafeError;
    prevStrafeError = strafeError;

    //gets the power
    strafePower = strafeError*kPS + integralStrafe *kIS + deltaStrafe * kDS;

    //sends the power to the motors
    backLeft.move(strafePower*-1);
    backRight.move(strafePower);
    frontLeft.move(strafePower);
    frontRight.move(strafePower*-1);

    pros::delay(15);



  }
}
