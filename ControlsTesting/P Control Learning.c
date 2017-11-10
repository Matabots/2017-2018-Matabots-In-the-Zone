
task main()
{
	//drive forward for 500 degrees using P control
	SensorValue[dgtl1] = 0;

	float error = 500 - SensorValue[dgtl1];	//error is the difference between the goal and current distance

	float tolerance = 1;	//how accurate do I want the robot to be

	float Kp = 1;		//Kp is a multiplier to calibrate the power


	while(abs(error) < tolerance)
	{
		error = 500 - SensorValue[dgtl1];
		motor[port1] = error *Kp;	//constantly updates as I get closer to target
		//motor power limits itself to 127 if too large.
		//check to make sure the robot is not stalling before it reaches the target point
			//Note: stalling is either from Kp being too low and doesn't have enough power to push last bit of distance
			//Note: You can eliminate stalling with a minimum speed limit i.e: if(error*kp < MIN){ motor[port[1]] = MIN};



		//*****STEPS TO CALIBRATE Kp*****
		//1. keep increasing Kp until the robot starts to oscillate about the target point physically
		//2. once Kp oscillates, decrease Kp a little so it is stable
	}

	//Things to know about P Controllers
	//

}
