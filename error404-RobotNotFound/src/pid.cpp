#include "custom/pid.h"
#include "custom/globals.h"


// pid.cpp
// 2915X
// 2020-2021 VRC Change Up


// tick multiplier (converts distance to tick values)
const double tickConst = 90 / (82.55 * M_PI);

// type safe sgn (sign) function
// credit to https://stackoverflow.com/a/4609795
template <typename T> int sgn(T val) { 
  return (T(0) < val) - (val < T(0)); 
}

// class constructor
myPID::myPID(double kP, double kD, int maxVoltage, int settlingTime) {
  this->kP = kP;
  this->kD = kD;
  this->maxVoltage = maxVoltage;
  this->settlingTime = settlingTime;
}

// calculate PID taking error as param, returns calculated output
double myPID::calculatePID(double thisError) {
  error = thisError;

  derivative = lastError - error;

  output = (error * kP) + (derivative * kD);

  // if the output is greater than the maximum voltage we want then we set it to
  // maxVoltage
  if (fabs(output) > 127) {
    output = sgn(output) * 127;
  }

  lastError = error;

  return output;
}

// pid function - calls calculation function which returns calculated output
double myPID::pid(double target, double sensor) {
  return calculatePID(target - sensor);
}

// chassis stuff

// TO BE REPLACED WITH QUADRATURE ENCODERS
// return average encoder ticks
int myPID::getEncoders(void) {
  return (((backLeft.get_position()+frontLeft.get_position())/2) +((backRight.get_position()+frontRight.get_position())/2))/2;
}

// asign voltage to the chassis
void myPID::setDriveVoltage(double left_pct, double right_pct) {
  // calculate voltage of motors from percentage
  float left_mV = (left_pct / 127.0f) * maxVoltage;
  float right_mV = (right_pct / 127.0f) * maxVoltage;

  // assign the power
  backLeft.move_voltage(left_mV);
  frontLeft.move_voltage(left_mV);
  backRight.move_voltage(right_mV);
  frontRight.move_voltage(right_mV);
}

///////////////////////////////////////////////////////////////////////
//                      MOVEMENT FUNCTIONS
///////////////////////////////////////////////////////////////////////

// chassis translation (fwd, backwards)
// takes the an instance of PIDClass for IMU calculation (gyroObj)
void myPID::translateChassis(double target_mm, myPID gyroObj, int timeout_ms) {

  uint32_t currentTime;
  
  reset();

  // double imuCurRotation = inertial.get_rotation(); // store currenet imu rotation

  int direction = sgn(target_mm);

  double targetTicks = target_mm * tickConst;

  // use to time to end the loop, but break if error is within threshold first
  for(currentTime = pros::millis(); currentTime > (pros::millis() - timeout_ms);) {

    // calculate power
    double pwrOut = pid(targetTicks, getEncoders());
    // double gyroPower = gyroObj.pid(imuCurRotation, inertial.get_rotation());

    // set power
    setDriveVoltage(pwrOut, pwrOut);

    // check if we reached target
    if(direction > 0) {
      if(error < 5) { // pos +
        break;
      }
    }
    else if(direction < 0) {  // neg -
      if(error > -5) {
        break;
      }
    }

    pros::delay(GLOBAL_DELAY);
  }

  setDriveVoltage(0, 0);
  pros::delay(settlingTime);
  pros::delay(5);
}

// rotate chassis function (rotate (x) angle)
void myPID::rotateChassis(double angleDeg, int timeout_ms) {

  uint32_t currentTime;
  reset();

  // // store inertial rotation to zero out value
  // double imuCurRotation = inertial.get_rotation();
  double targetAngle = angleDeg;
  // figure out which way we are turning
  int direction = sgn(angleDeg);

  for( currentTime = pros::millis(); currentTime > (pros::millis() - timeout_ms);) {
    double power = pid(targetAngle,getEncoders());
    setDriveVoltage(power, -power);

    // check if we reached target
    if(direction > 0) {
      if(error < 5) { // pos +
        break;
      }
    }
    else if(direction < 0) { // neg -
      if(error > -5) {
        break;
      }
    }

    pros::delay(GLOBAL_DELAY);
  }
  setDriveVoltage(0, 0);
  pros::delay(settlingTime);
  pros::delay(5);
}


// reset all values
void myPID::reset(void) {
  error = 0;
  derivative = 0;
  lastError = 0;
  output = 0;
  // tare encoders
  backLeft.tare_position();
  backRight.tare_position();
  frontLeft.tare_position();
  frontRight.tare_position();
}