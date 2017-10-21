struct Vector
{
	float x;
	float y;
	float z;
};

struct Chassis
{
	float wheelDiameter;	//center of rotation
	Vector COR;	//center of rotation

};

struct Lift
{
	//define combination of bars
	float armLength;
	float height;
};
