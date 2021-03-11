#pragma once
// pid.h
// 2915X
// 2020-2021 VRC Change Up

#include "main.h"


// just so the linter shuts up
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class myPID {
    private:
        //
        // internal variables for PID
        //
        double error;
        double derivative;
        double lastError;
        double output;
        // tuning factors
        float kP;
        float kD;

        // maximum chassis voltage
        int maxVoltage;
        // settling time (time after control has ended) to allow for settling of chassis
        double settlingTime;

        ///
        /// FUNCTIONS
        ///

        // actual pid calculation function
        double calculatePID(double err);

        // get encoder values
        // returns an integer of the average of l and r quad encoders
        int getEncoders(void);

        // reset all values + tare motors
        void reset(void);

    public: 
        // constructor
        myPID(double kP, double kD, int maxVoltage = 12000, int settlingTime = 2500);

        // returns an calculated PID output power
        double pid(double target, double sensor);

        // sets voltage to the motors (calculates voltage from percentage)
        // bypass v5 motor PId
        void setDriveVoltage(double left_pct, double right_pct);

        // rotate the chassis 
        void rotateChassis(double angleDeg, int timeout_ms);

        // translate the chassis (forward and backwards plane)
        void translateChassis(double target_mm);
        
        // same function above (with overload for gyro object)
        void translateChassis(double target_mm, int timeout_ms);

};