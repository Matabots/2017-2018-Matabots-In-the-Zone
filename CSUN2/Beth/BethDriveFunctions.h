/*
  Drive Functions
*/

#define DEADZONE 15

void rightMotors(int speed)
{
  motor[REdgeMots] = -speed;
  motor[RInsideMots] = speed;
}
void leftMotors(int speed)
{
  motor[LEdgeMots] = -speed;
  motor[LInsideMots] = speed;
}
void haltRight()
{
  motor[REdgeMots] = 0;
  motor[RInsideMots] = 0;
}
void haltLeft()
{
  motor[LEdgeMots] = 0;
  motor[LInsideMots] = 0;
}

//void halt()
//{
//	haltRight();
//	haltLeft();
//}

void driveControl()
{
   if (abs(vexRT[Ch2]) > DEADZONE)
	 {
		 rightMotors(vexRT[Ch2]);
	 }
	 else
	 {
	   haltRight();
   }
	 if (abs(vexRT[Ch3]) > DEADZONE)
	 {
	   leftMotors(vexRT[Ch3]);
	 }
	 else
	 {
	   haltLeft();
	 }
}
