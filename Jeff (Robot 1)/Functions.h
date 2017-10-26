
/*General Equations*/
float Avg(float a, float b);
float degToInt(float deg);

/*Robot Defintion*/
void initializeRobot();
float ClawEndpointTo(float height);
int stackHeight(int towerHeight);
void moveTime(int powerLeft, int powerRight, int time);
void moveDeg(int powerLeft, int powerRight, int deg);
void moveInch(int powerLeft, int powerRight, int inch);
void GoalLift();
void liftBase();

/*Teleoperated Controls*/
void setupController();
void MoveLift();
void MoveClaw();
void MoveChassis();
