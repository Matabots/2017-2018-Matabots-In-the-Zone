/*
The purpose of this file is to setup up functions for PID, XYTheta,
Linear Controls, etc...
*/

typedef struct{
  tMotor name1;
  tSensors sensorname;
  float target; 						//speed desired to the motor
  float error;
  float prevError;			 	//last error calculated for that motor
  float totalError;
  float kP;
  float kI;
  float kD;
  float controller_output; 	//controller output to the motor
  float speedRead; 					//speed calculated from the encoder values
  float lastRead;			//last encoder read. Necessary to calulate the speed
  bool proportionalEnabled;
  bool integralEnabled;
  bool derivativeEnabled;
} Control;

void SetupControl(float target, float kp,bool enableP, float ki, bool enableI, float kd,bool enableD)
{

}

void PID(Control* control)
{

}
