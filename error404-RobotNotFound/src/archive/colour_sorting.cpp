// #include "main.h"
// #include "globals.h"
//
// bool isBallThere, wrongColour;
// int colourOfBall, distance;
// bool correctColour = true;
//
// void toggleDefaultColour(){
// 	correctColour = !correctColour;
// 	if (correctColour){
// 		master.set_text(0, 0,"You are on Red team");
// 	}
// 	else{
// 		master.set_text(0, 0,"You are on Blue team");
// 	}
// }
//
// void opcontrol() {
// 	optical.set_led_pwm(100);
// 	master.set_text(0, 0,"You are on Red team");
// 	while(true){
// 		distance =  optical.get_proximity();
// 		if (distance == 255){
// 			isBallThere = true;
// 		}
// 		else {
// 			isBallThere = false;
// 		}
//
// 		if(master.get_digital_new_press(DIGITAL_X)){
// 	 	toggleDefaultColour();
// 	  }
//
// 		if (isBallThere){
//
// 			colourOfBall = optical.get_hue();
//
// 			if ((colourOfBall < 20 || 340 < colourOfBall) && correctColour){
//
// 				wrongColour = false;
// 				pros::delay(5);
// 				}
//
// 			else if ((colourOfBall < 20 || 340 < colourOfBall) && !correctColour){
//
// 				wrongColour = true;
// 				pros::delay(5);
// 				}
//
// 			else if ((215 < colourOfBall && colourOfBall < 310 ) && correctColour){
//
// 				wrongColour = true;
// 				pros::delay(5);
// 				}
//
// 			else if ((215 < colourOfBall && colourOfBall < 310 ) && !correctColour){
//
// 				wrongColour = false;
// 				pros::delay(5);
// 				}
// 		}
//
// 		else if (!isBallThere && wrongColour){
// 			pros::delay(250);
// 			wrongColour = false;
// 		}
//
// 		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && wrongColour){
// 			upperRollers.move_voltage(-12000);
// 		}
// 		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !wrongColour){
// 			upperRollers.move_voltage(12000);
// 		}
// 		else{
// 			upperRollers.move_voltage(0);
// 		}
//   }
// }
