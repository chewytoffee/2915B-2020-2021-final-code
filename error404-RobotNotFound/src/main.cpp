#include "main.h"
#include "custom/globals.h"
#include "custom/pid.h"
#include "custom/auton-gui.h"
#include "custom/auton-runs.h"
bool toggle = false;
int chosenAuton = 0;


void toggleIntake() {
	toggle = !toggle;
	if (toggle) {
		master.clear_line(0);
		master.set_text(0,0,"Intakes are on");
	}
	else if (!toggle){
		master.clear_line(1);
		master.set_text(0,0,"Intakes are off");
	}
}


void initialize() {
	backLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    backRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    frontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    frontRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	autoSelection::autoGUI();
	if (buttons[0] == true){
		chosenAuton += 1;
	}
	if (buttons[1]){
		chosenAuton += 2;
	}
	if (buttons[2]){
		chosenAuton += 4;
	}
	if (buttons[3]){
		chosenAuton += 8;
	}
}

void disabled() {
}

void competition_initialize() {}


void autonomous() {

}

void opcontrol(){
	while (true){
		  if(pros::c::battery_get_capacity() < 35) {
			master.clear_line(0);
			master.print(0, 0, "Battery LOW (%dpct)", pros::c::battery_get_capacity());
			master.rumble("-------");
			pros::delay(5000);
			}
		//creates integers for each of the controller axis to help with custom deadzones
		int ch3,ch1;
		ch3 = master.get_analog(ANALOG_LEFT_Y);
		ch1 = master.get_analog(ANALOG_RIGHT_X);

		//custom deadzones
		if (ch3 < 5 && ch3 > -5){
			ch3 = 0;
		}
		
		if (ch1 < 5 && ch1 > -5){
			ch1 = 0;
		}

		//natively add the X and Y axis
		double fL = (double) ch3 ;
		double bL = (double) ch3 ;
		double fR = (double) ch3 ;
		double bR = (double) ch3 ;

		// rotation
		fL = fL - ch1;
		bL = bL - ch1;
		fR = fR + ch1;
		bR = bR + ch1;

		//check if the max value is 127 or if 127 is larger
		double max_raw_sum = std::max(std::abs(fL),std::max(std::abs(bL),std::max(std::abs(fR),std::max(std::abs(bR),127.0))));

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


		//toggle intake
		if (master.get_digital_new_press(DIGITAL_R1)){
			toggleIntake();
		}

		if (master.get_digital(DIGITAL_L2)){
			leftIntake.move(-127);
			rightIntake.move(-127);
			lowerRollers.move_voltage(-12000);
			upperRollers.move_voltage(-12000);
			}
		else if (toggle){
			if (master.get_digital(DIGITAL_L1)){
				leftIntake.move(127);
				rightIntake.move(127);
				lowerRollers.move_voltage(12000);
				upperRollers.move_voltage(12000);
				}
			else if (master.get_digital(DIGITAL_RIGHT)){
				leftIntake.move(-127);
				rightIntake.move(-127);
				lowerRollers.move_voltage(0);
				upperRollers.move_voltage(0);
			}
			else if (master.get_digital(DIGITAL_B)){
				leftIntake.move(127);
				rightIntake.move(127);
				lowerRollers.move_voltage(12000);
				upperRollers.move_voltage(12000);
				}
			else if (master.get_digital(DIGITAL_DOWN)){
				leftIntake.move(127);
				rightIntake.move(127);
				lowerRollers.move_voltage(-12000);
				upperRollers.move_voltage(-12000);
				}
			else {
				leftIntake.move(127);
				rightIntake.move(127);
				lowerRollers.move_voltage(6000);
				upperRollers.move_voltage(0);
				}
			}
		else if (!toggle){
			if (master.get_digital(DIGITAL_L1)){
				leftIntake.move(127);
				rightIntake.move(127);
				lowerRollers.move_voltage(12000);
				upperRollers.move_voltage(12000);
				}
			else if (master.get_digital(DIGITAL_RIGHT)){
				leftIntake.move(-127);
				rightIntake.move(-127);
				lowerRollers.move_voltage(0);
				upperRollers.move_voltage(0);
			}
			else if (master.get_digital(DIGITAL_B)){
				lowerRollers.move_voltage(12000);
				upperRollers.move_voltage(12000);
			}
			else if (master.get_digital(DIGITAL_DOWN)){
				lowerRollers.move_voltage(-12000);
				upperRollers.move_voltage(-12000);
			}
			else {
				leftIntake.move(0);
				rightIntake.move(0);
				lowerRollers.move_voltage(0);
				upperRollers.move_voltage(0);
				}
		}
	}
}
