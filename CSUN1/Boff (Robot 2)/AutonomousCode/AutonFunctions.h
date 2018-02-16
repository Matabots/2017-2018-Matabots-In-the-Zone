/*
Auton Functions (some PID code taken from DriveControls)
*/
#include "Commands.h"
bool blue = true;

void autonGo()
{

	if (blue)
	{


		//needs to have fresh batteries and good rubber bands
		//StackNeut();
		//wait10Msec(500);
		TurnTo(90);
		MoveArmTo(0);
		tasksFinished();
		/*
		StackGro();
		wait10Msec(200);
		StackLoad();
		wait10Msec(200);
		StackNeut();
		AutoLift();
		wait10Msec(200);
		/*
	  moveInchTwo(0,80,5.75);//moving //works with 5.75 and fresh battery
	  wait10Msec(50);
	  moveInchTwo(127,127,28);
	  wait10Msec(100);
	  moveInchTwo(60,-60,4);
	  wait10Msec(50);
	  moveInchTwo(60,60,5);
	  moveInchTwo(-127,-127,11);
	  wait10Msec(50);

	  moveInchTwo(127,127,1.7); //grabbing
	  wait10Msec(50);
	  moveInchTwo(-127,127,5.75);
	  wait10Msec(50);
	  moveInchTwo(80,80,8.5);
	  wait10Msec(50);
	  moveInchTwo(80,80,2);
	  wait10Msec(50);
	  moveInchTwo(0,80,3);
	  wait10Msec(50);
	  mobileUp();
	  wait10Msec(100);
	  tinyLift(127, 80);
	  wait10Msec(100);

	  MoveClawTwo();
	  wait10Msec(100);
	  MoveClawTwo();
	  wait10Msec(100);

	  moveInchTwo(-80,0,3);
	  wait10Msec(50);
	  moveInchTwo(-127,-127,9);
	  wait10Msec(50);

	  moveInchTwo(-75,75,12); //returning
	  wait10Msec(50);
	  moveInchTwo(100,100,27.75); //scored on 28
	  wait10Msec(50);
	  moveInchTwo(75,-75,6); //scored on 5
	  wait10Msec(50);

	  moveInchTwo(-80,-80,6); // Scoring
	  wait10Msec(100);
	  moveInchTwo(127,127,17);
	  wait10Msec(90);
	  moveInchTwo(-70,-70,1);
	  moveInchTwo(-127,127,.5);
	  wait10Msec(90);
	  wait10Msec(50);
	  moveInchTwo(-127,-127,5);
	  wait10Msec(50);
	  moveInchTwo(-75,75,8);
	  wait10Msec(50);

	  mobileUp();
	  wait10Msec(50);
	  moveInchTwo(100,100,3);
	  wait10Msec(50);
	  moveInchTwo(127,127,7);
	  wait10Msec(50);*/
  }
  else { //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  	reSetDEnc();
		/*
	  moveInchTwo(80,0,5.75);//moving //works with 5.75 and fresh battery //checked
	  wait10Msec(50);
	  moveInchTwo(127,127,27.5);
	  wait10Msec(100);
	  moveInchTwo(-60,60,4); //checked
	  wait10Msec(50);
	  moveInchTwo(60,60,5);
	  moveInchTwo(-127,-127,11);
	  wait10Msec(50);

	  moveInchTwo(127,127,1.7); //grabbing
	  wait10Msec(50);
	  moveInchTwo(127,-127,5.75);//checked
	  wait10Msec(50);
	  moveInchTwo(80,80,8.5);
	  wait10Msec(50);
	  moveInchTwo(80,80,2);
	  wait10Msec(50);
	  moveInchTwo(80,0,3);//checked
	  wait10Msec(50);
	  mobileUp();
	  wait10Msec(100);
	  tinyLift(127, 80);
	  wait10Msec(100);

	  MoveClawTwo();
	  wait10Msec(100);
	  MoveClawTwo();
	  wait10Msec(100);

	  moveInchTwo(0,-80,3);//checked
	  wait10Msec(50);
	  moveInchTwo(-127,-127,9);
	  wait10Msec(50);

	  moveInchTwo(75,-75,12); //returning //checked
	  wait10Msec(50);
	  moveInchTwo(100,100,27.75); //scored on 28
	  wait10Msec(50);
	  moveInchTwo(-75,75,6); //scored on 5 //checked
	  wait10Msec(50);

	  moveInchTwo(-80,-80,6); // Scoring
	  wait10Msec(100);
	  moveInchTwo(127,127,17);
	  wait10Msec(90);
	  moveInchTwo(-70,-70,1);
	  moveInchTwo(127,-127,.5); //checked
	  wait10Msec(90);
	  wait10Msec(50);
	  moveInchTwo(-127,-127,5);
	  wait10Msec(50);
	  moveInchTwo(75,-75,8); //checked
	  wait10Msec(50);

	  mobileUp();
	  wait10Msec(50);
	  moveInchTwo(100,100,3);
	  wait10Msec(50);
	  moveInchTwo(127,127,7);
	  wait10Msec(50);*/
  }

}
