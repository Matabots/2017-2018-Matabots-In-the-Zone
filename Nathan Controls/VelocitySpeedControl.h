

//remenber, remember, variables in define are float. Of course, some of the are int, but just leave the code take care of it

#define P_GAIN 1//0.0 //gain for only proportinal controller
#define PROPORTIONAL_GAIN 1//3.48 //PID controller proportinal
#define INTEGRAL_CONST 1//896.9 //PID controller integral
#define SAMPLE_PERIOD 10  //Sample period for digital control

#define PI_RANGE 5 	//we are switching between proportional controller and PI controller.
										//P is so fast and awesome but does not allow stationary error equals to zero. And have a huge, huge noise.
										//So, as the speed gets close to the target, we change it to PI. This value control how close we want to get before changing.
										//If you dont know how much, jus leave in 5
#define PI_SETUP 76 //You have to choose a value to the PI to start. Do you want to do the easy way? So, run it once, for the value you like,
										//and set the power value on here once it stabilize. Do you wanna do the hard way? well, probably you would have to run an
										//imaginary PI controller, with integral wind-up. And get the value in it.

#define SATURATION_UP 120 //motor up saturation
#define SATURATION_DOWN 0 //motor down saturation, we dont want the motor to fight against movement
#define MOTOR_DEADZONE 20 //all motors have a region where it does not responde to PWM. So, you cannot apply pwm in this regions, unless you want to burn stuff


typedef struct {
  tMotor name1, name2;
  tSensors sensorname;
  int speedSet; 						//speed desired to the motor
  float errorK0speed;			 	//last error calculated for that motor
  float errorK0output;
  float controller_output; 	//controller output to the motor
  float speedRead; 					//speed calculated from the encoder values in RPM
  float linearSpeedRead;		//linear speed of the robot wheels in in/s
  int lastEncoderRead;			//last encoder read. Necessary to calulate the speed
  bool proportional;
} MOTOR_PI;

void ReadSpeed(MOTOR_PI* motorA, int time);
void motor_Control(MOTOR_PI* motorA);
void PI_Control(MOTOR_PI* motorA);
void motorInit (MOTOR_PI* motorA, tMotor title1, tSensors sensor);

//future works in controller involves testing a controller PI with integral wind-up. I don`t have time to do it now, even why the controller implemented here,
//even though I assume is not very elegant, works. So

//Controller constants. I have put that in here so it stay more organized
#define A0 1.0
#define B0 (PROPORTIONAL_GAIN*(1+(SAMPLE_PERIOD/(2*INTEGRAL_CONST))))
#define B1 (PROPORTIONAL_GAIN*(SAMPLE_PERIOD/(2*INTEGRAL_CONST)-1))


void ReadSpeed(MOTOR_PI* motorA, int time){
  int encoder;
  encoder = SensorValue[(*motorA).sensorname];
  (*motorA).speedRead = abs(0.16667*(float)(encoder - (*motorA).lastEncoderRead)/((float)time/1000));//*5.88235; //that is not a unit. You should multiply for a constant. I will leave this way by now.
  (*motorA).lastEncoderRead = encoder;

}
float
calculateVelocityBetter( tMotor port, float gear_ratio = 1.0 )
{
    static  long  nSysTime_last;
    static  long  encoder_counts_last;
    static  float ticks_per_rev = SMLIB_TPR_393Speed; // fixed, known motor
    int     delta_ms;
    int     delta_enc;
    long    encoder_counts;
    float   motor_velocity;
    // Get current encoder value
    encoder_counts = nMotorEncoder[ port ];
    // This is just used so we don't need to know how often we are called
    // how many mS since we were last here
    delta_ms = nSysTime - nSysTime_last;
    nSysTime_last = nSysTime;
    // Change in encoder count
    delta_enc = (encoder_counts - encoder_counts_last);
    // save last position
    encoder_counts_last = encoder_counts;
    // Calculate velocity in rpm
    motor_velocity = (1000.0 / delta_ms) * delta_enc * 60.0 / ticks_per_rev;
    // multiply by any gear ratio's being used
    return( motor_velocity * gear_ratio );
}

void PI_Control(MOTOR_PI* motorA){
    float errorK1speed;
    ReadSpeed(motorA, timeSegment);
    //make the calculation for the speed errors
    errorK1speed = (*motorA).errorK0speed;
    (*motorA).errorK0speed = (*motorA).speedSet-(*motorA).speedRead;

    //apply control`s law
    if(abs((*motorA).speedRead - (*motorA).speedSet)<PI_RANGE)
    {
    	if((*motorA).proportional)
    	{
    		(*motorA).controller_output = PI_SETUP;
    		(*motorA).proportional = false;
    	}
			(*motorA).controller_output = A0*(*motorA).controller_output + B0*((*motorA).errorK0speed)+B1*errorK1speed;
		}

		//but, if the controller is to far from the point i want to, I want it to go faster. Fast as hell. Now, I would like to play with a proportional
		else
		{
			(*motorA).controller_output = P_GAIN*((1/P_GAIN+1)*((*motorA).speedSet)-(*motorA).speedRead);
			(*motorA).errorK0speed = 0;
			(*motorA).proportional = true;
		}

		// The motor is having a problema when stopping. The controller output does not goes to 0, so it is supplying the motor with power, eventhough it is
		// not running. This is meant to solve this problem
		if ((*motorA).speedSet == 0) (*motorA).controller_output = 0;


    //apply saturation of the controller
    if ( (*motorA).controller_output > SATURATION_UP ) (*motorA).controller_output = SATURATION_UP;
    else if ( (*motorA).controller_output < SATURATION_DOWN ) (*motorA).controller_output = SATURATION_DOWN;
    else if ( (*motorA).controller_output < MOTOR_DEADZONE && (*motorA).controller_output > -MOTOR_DEADZONE ) (*motorA).controller_output = 0;
		else (*motorA).controller_output = (*motorA).controller_output;


    //set power in the motor
    motor[(*motorA).name1] = (*motorA).controller_output;

    //the controller output can`t be less the saturation dowm
    if ( (*motorA).controller_output < SATURATION_DOWN ) (*motorA).controller_output = SATURATION_DOWN;
}

void motor_Control(MOTOR_PI* motorA){

	if(time1[T1] >= SAMPLE_PERIOD/2){
		ReadSpeed(motorA, time1[T1]);
		time1[T1] = 0;
	}
	if(time1[T2]>= SAMPLE_PERIOD){
		ReadSpeed(motorA, time1[T2]);
		time1[T2] =0;
	}
}

void motorInit (MOTOR_PI* motorA, tMotor title1, tSensors sensor){
		(*motorA).name1 = title1;
		(*motorA).sensorname = sensor;
		SensorValue[(*motorA).sensorname] = 0;
    (*motorA).speedSet = 0;
    (*motorA).errorK0speed = 0;
    (*motorA).errorK0output=0;
    (*motorA).controller_output = 0;
    (*motorA).speedRead = 0.0;
    (*motorA).lastEncoderRead = 0;
}
