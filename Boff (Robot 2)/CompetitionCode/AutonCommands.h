/*
  AutonFunction
*/
#include "Commands.h"
bool red = true;
bool autoLoad = false;
bool preloading = true;


void testTask() //temp
{

}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void autonGo()
{
	if (red)
	{	//needs to have fresh batteries and good rubber bands. starts at 7 inches from the wall
		if (preloading)
		{
		  PreLoad();
		  wait1Msec(1000); // 1/4 of second to clear cone, not
		}
		tinyLiftDown(1.75);
		//wait10Msec(25);
		PIDDrive(61); //was 60, is split into two 30s
		//wait10Msec(25);
		//TurnTo(0);
		//wait10Msec(20);
		//PIDDrive(31);
		//wait10Msec(25);
		tinyLiftUp();
		//wait10Msec(15);
		if (preloading)
		{
		  AutoLift();
		  //wait1Msec(250);
		}
		if (autoLoad)
			{
		}
		else
		{
			PIDDrive(-47);
			//wait10Msec(25);


			//--- good for 10 points
			/*
			TurnTo(170);
			wait10Msec(200);
			PIDDrive(50);
			wait10Msec(100);
			tinyLiftDown(1.75);
			wait10Msec(100);
			*/


			//new Code
			//--good for 20 points
			TurnTo(310); //170
			wait10Msec(100); // was at 200
			PIDDrive(-33);

			//scoring ----
			TurnTo(225);
			wait10Msec(100); // was 50
			PIDDrive(6); //was 10
			//wait10Msec(25);
			//TurnTo(225);
			//wait10Msec(75);

			score(115, 115, 1.25);
			//wait10Msec(20);
			tinyLiftDown(1.75);
			//wait10Msec(100);
			tinyLiftUpTmp(0.15);
			//wait10Msec(100);
			score(80, 80, 0.75);
			//wait10Msec(100);
			driveBack(127,127, 0.85);

			////--good for 20 points
			//TurnTo(350); //170
			//wait10Msec(100); // was at 200
			//PIDDrive(-27);
			////wait10Msec(25);
			//TurnTo(125);
			//wait10Msec(200);
			//PIDDrive(23); //was 25
			////wait10Msec(25);
			//TurnTo(225);
			//wait10Msec(100); // was 50
			//PIDDrive(-9); //was 10
			////wait10Msec(25);
			//TurnTo(225);
			//wait10Msec(75);

			////scoring ----

			////PIDDrive(40);
			//score(127, 127, 2.0);
			////wait10Msec(20);
			//tinyLiftDown(1.75);
			////wait10Msec(100);
			//tinyLiftUpTmp(0.25);
			////wait10Msec(100);
			//score(80, 80, 0.75);
			////wait10Msec(100);
			//driveBack(127,127, 0.90);

			//PIDDrive(-50);
			//wait10Msec(100);
			//PIDDrive(10);
			//wait10Msec(100);
			TurnTo(95);
			wait10Msec(150);

			//nextGoal----
			tinyLiftUp();
			//wait10Msec(100);

			PIDDrive(35);

			//wait10Msec(100);
			TurnTo(355);
			wait10Msec(150);
			driveBack(50,50,1.5);
			//wait10Msec(100);
			PIDDrive(7);
			//wait10Msec(100);
			TurnTo(88);
			//wait10Msec(250);

			tinyLiftDown(1.9);
			//wait10Msec(100);

			PIDDrive(31);
			wait10Msec(100);

			//TurnTo(80);
			//wait10Msec(200);

			//PIDDrive(30);
			//wait10Msec(100);

			tinyLiftUp();
			//wait10Msec(100);
			TurnTo(100);

			wait10Msec(25);

			driveBack(127,127, 1.0);

			TurnTo(275);

			wait10Msec(50);

			score(127, 127, 0.8);
			wait10Msec(75);
			tinyLiftDown(1.75);
			wait10Msec(150);

			driveBack(127, 127, 1.5);


		}
      tasksFinished();
  }
  else { //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    //needs to have fresh batteries and good rubber bands. starts at 7 inches from the wall
		if (preloading)
		{
		  PreLoad();
		  wait1Msec(1000); // 1/4 of second to clear cone, not
		}
		tinyLiftDown(1.75);
		//wait10Msec(25);
		PIDDrive(61); //was 60, is split into two 30s
		//wait10Msec(25);
		//TurnTo(0);
		//wait10Msec(20);
		//PIDDrive(31);
		//wait10Msec(25);
		tinyLiftUp();
		//wait10Msec(15);
		if (preloading)
		{
		  AutoLift();
		  //wait1Msec(250);
		}
		if (autoLoad)
			{
		}
		else
		{
			PIDDrive(-47);
			//wait10Msec(25);


			//--- good for 10 points
			/*
			TurnTo(170);
			wait10Msec(200);
			PIDDrive(50);
			wait10Msec(100);
			tinyLiftDown(1.75);
			wait10Msec(100);
			*/


			//new Code
			//--good for 20 points
			TurnTo(50); //170
			wait10Msec(100); // was at 200
			PIDDrive(-33);

			//scoring ----
			TurnTo(135);
			wait10Msec(100); // was 50
			PIDDrive(6); //was 10
			//wait10Msec(25);
			//TurnTo(225);
			//wait10Msec(75);

			score(115, 115, 1.25);
			//wait10Msec(20);
			tinyLiftDown(1.75);
			//wait10Msec(100);
			tinyLiftUpTmp(0.15);
			//wait10Msec(100);
			score(80, 80, 0.75);
			//wait10Msec(100);
			driveBack(127,127, 0.85);

			////--good for 20 points
			//TurnTo(350); //170
			//wait10Msec(100); // was at 200
			//PIDDrive(-27);
			////wait10Msec(25);
			//TurnTo(125);
			//wait10Msec(200);
			//PIDDrive(23); //was 25
			////wait10Msec(25);
			//TurnTo(225);
			//wait10Msec(100); // was 50
			//PIDDrive(-9); //was 10
			////wait10Msec(25);
			//TurnTo(225);
			//wait10Msec(75);

			////scoring ----

			////PIDDrive(40);
			//score(127, 127, 2.0);
			////wait10Msec(20);
			//tinyLiftDown(1.75);
			////wait10Msec(100);
			//tinyLiftUpTmp(0.25);
			////wait10Msec(100);
			//score(80, 80, 0.75);
			////wait10Msec(100);
			//driveBack(127,127, 0.90);

			//PIDDrive(-50);
			//wait10Msec(100);
			//PIDDrive(10);
			//wait10Msec(100);
			TurnTo(265);
			wait10Msec(150);

			//nextGoal----
			tinyLiftUp();
			//wait10Msec(100);

			PIDDrive(20);

			//wait10Msec(100);
			TurnTo(5);
			wait10Msec(150);
			driveBack(50,50,1.5);
			//wait10Msec(100);
			PIDDrive(7);
			//wait10Msec(100);
			TurnTo(272);
			//wait10Msec(250);

			tinyLiftDown(1.9);
			//wait10Msec(100);

			PIDDrive(48);
			wait10Msec(100);

			//TurnTo(80);
			//wait10Msec(200);

			//PIDDrive(30);
			//wait10Msec(100);

			tinyLiftUp();
			//wait10Msec(100);
			TurnTo(260);

			wait10Msec(25);

			driveBack(127,127, 1.0);

			TurnTo(85);

			wait10Msec(50);

			score(127, 127, 0.8);


			tinyLiftDown(1.75);
			wait10Msec(150);

			driveBack(127, 127, 1.5);



		}
      tasksFinished();
  }
}
