/*
  autonomous data (Copied and modified from autoData.h)
*/
bool blue = false;

bool opened = false;
void reSetDEnc()
{
	SensorValue[rightEnc] = 0;
	SensorValue[leftEnc] = 0;
}
void Halt()
{
	motor[RRevs] = 0;
	motor[RFors] = 0;
	motor[LRevs] = 0;
	motor[LFors] = 0;
}
void Right(int speed)
{
	motor[RRevs] = speed;
  motor[RFors] = speed;
}
void Left(int speed)
{
	motor[LRevs] = speed;
	motor[LFors] = speed;
}
float degToInt(float deg)
{
	return ((deg * (3.14 * 4))/360);
}
void moveInchTwo(int powerLeft, int powerRight, int inch)
{
  reSetDEnc();
	while (abs(degToInt(SensorValue[leftEnc])) < inch && abs(degToInt(SensorValue[rightEnc])) < inch)
	{
		Right(powerLeft);
  	Left(powerRight);
  }
  Halt();
}
void mobileUp()
{
	if (SensorValue[pneuBase] == 0) {
		SensorValue[pneuBase] = 1;
		wait10Msec(20);
  }else if (SensorValue[pneuBase] == 1) {
	  SensorValue[pneuBase] = 0;
		wait10Msec(20);
  }

}
void MoveClawTwo() //copied from drive, then modified
{

	if(!opened) //&& abs(SensorValue[CMEnc]) < 90)
	{
		motor[CMot] = 127;
		opened = true;
		wait10Msec(100);
  }
  else if(opened) //&& abs(SensorValue[CMEnc]) > 0)
  {
    motor[CMot] = -127;
    opened = false;
    wait10Msec(100);
  }
  else
  {
  	motor[CMot] = 0;
  }
  displayLCDNumber(1,3,getMotorEncoder(CMot));
}
int full = 80;
int small = 40;

void tinyLift(int power, int time)
{
    	motor[CLift] = power;
    	wait10Msec(time);

		  motor[CLift] = 0;

}

void autoGO()
{
	if (blue)
	{

		//needs to have a full tank of air and fresh batteries
		reSetDEnc();
	  SensorValue[pneuBase] = 1;

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
	  tinyLift(127, full);
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
	  wait10Msec(50);
  }
  else { //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  	reSetDEnc();
	  SensorValue[pneuBase] = 1;

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
	  tinyLift(127, full);
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
	  wait10Msec(50);
  }

}
