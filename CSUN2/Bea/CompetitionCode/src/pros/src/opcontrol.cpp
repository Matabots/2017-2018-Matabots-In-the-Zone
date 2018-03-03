#include "main.h"
#include "robot.h"


void operatorControl() {
  robot bot = robot();

	while (1) {
    // bot.printFirst();
    //bot.digital.resetEncoders();
    //bot.digital.printEncoderValues();
    bot.motors.printhuh();
    delay(25);
	}
}
