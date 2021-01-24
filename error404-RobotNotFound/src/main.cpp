#include "main.h"
#include "globals.h"
#include "pid.h"

bool isBallThere, wrongColour;
int colourOfBall, distance;
bool correctColour = true;

void toggleDefaultColour(){
	correctColour = !correctColour;
	if (correctColour){
		master.set_text(0, 0,"You are on Red team");
	}
	else{
		master.set_text(0, 0,"You are on Blue team");
	}
}

void initialize() {
}

void disabled() {}

void competition_initialize() {}


void autonomous() {
	pros::Task xPID (driveStraight);
	resetSensors();
	driveStraight(500);
}

void opcontrol() {
	optical.set_led_pwm(100);
	master.set_text(0, 0,"You are on Red team");
	while(true){
		distance =  optical.get_proximity();
		if (distance == 255){
			isBallThere = true;
		}
		else {
			isBallThere = false;
		}

		if(master.get_digital_new_press(DIGITAL_X)){
	 	toggleDefaultColour();
	  }

		if (isBallThere){

			colourOfBall = optical.get_hue();

			if ((colourOfBall < 20 || 340 < colourOfBall) && correctColour){

				wrongColour = false;
				pros::delay(5);
				}

			else if ((colourOfBall < 20 || 340 < colourOfBall) && !correctColour){

				wrongColour = true;
				pros::delay(5);
				}

			else if ((215 < colourOfBall && colourOfBall < 310 ) && correctColour){

				wrongColour = true;
				pros::delay(5);
				}

			else if ((215 < colourOfBall && colourOfBall < 310 ) && !correctColour){

				wrongColour = false;
				pros::delay(5);
				}
		}

		else if (!isBallThere && wrongColour){
			pros::delay(250);
			wrongColour = false;
		}

		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && wrongColour){
			upperRollers.move_voltage(-12000);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !wrongColour){
			upperRollers.move_voltage(12000);
		}
		else{
			upperRollers.move_voltage(0);
		}
		//creates integers for each of the controller axis to help with custom deadzones
		int ch3,ch4,ch1;
		ch3 = master.get_analog(ANALOG_LEFT_Y);
		ch4 = master.get_analog(ANALOG_LEFT_X);
		ch1 = master.get_analog(ANALOG_RIGHT_X);

		//custom deadzones
		if (ch3 < 5 && ch3 > -5){
			ch3 = 0;
		}
		if (ch4 < 5 && ch4 > -5){
			ch4 = 0;
		}
		if (ch1 < 5 && ch1 > -5){
			ch1 = 0;
		}

		//natively add the X and Y axis
		double fL = (double) ch3 + ch4;
		double bL = (double) ch3 - ch4;
		double fR = (double) ch3 - ch4;
		double bR = (double) ch3 + ch4;

		//Find the largest possible sum of X and Y
		double max_raw_sum = (double)(abs(ch3) + abs(ch4));

		//Find the largest joystick value
		double max_XYstick_value = (double)(std::max(abs(ch3),abs(ch4)));

		//The largest sum will be scaled down to the largest joystick value, and the others will be scaled by the same amount to preserve directionality
		if (max_raw_sum != 0) {
			fL = fL / max_raw_sum * max_XYstick_value;
			bL = bL / max_raw_sum * max_XYstick_value;
			fR = fR / max_raw_sum * max_XYstick_value;
			bR = bR / max_raw_sum * max_XYstick_value;
		}

		// rotation
		fL = fL + ch1;
		bL = bL + ch1;
		fR = fR - ch1;
		bR = bR - ch1;

		//check if the max value is 127 or if 127 is larger
		max_raw_sum = std::max(std::abs(fL),std::max(std::abs(bL),std::max(std::abs(fR),std::max(std::abs(bR),127.0))));

		//scales everything to have 127 pct as max
		fL = fL  / max_raw_sum * 127.0;
		bL = bL  / max_raw_sum * 127.0;
		fR = fR  / max_raw_sum * 127.0;
		bR = bR  / max_raw_sum * 127.0;

		//convert the values to voltages
		fL = fL / 127 * 16000;
		bL = bL / 127 * 16000;
		fR = fR / 127 * 16000;
		bR = bR / 127 * 16000;

		//throw these values at the motors
		frontLeft .move_voltage(fL);
		backLeft  .move_voltage(bL);
		frontRight.move_voltage(fR);
		backRight .move_voltage(bR);





	}
}
