/* www.chrisheydrick.com
     
   June 23 2012
   CanonicalArduinoRead write a byte to an Arduino, and then
   receives a serially transmitted string in response.
   The call/response Arduino sketch is here:
   https://gist.github.com/2980344
   Arduino sketch details at www.chrisheydrick.com
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string>
#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <std_msgs/Int32MultiArray.h>
#include <std_msgs/Int32.h>

#define DEBUG 1
  
struct Euler
{
  float roll, pitch, yaw;
};

Euler e;

void ParseEuler(char * buf, int bufLen)
{
  int index = 0;
  int count = 0;
  char number[10];
  
  for(int i = 0; i < bufLen; i++)
  {
    if(buf[i] != ',' && i != bufLen - 1)
    {
      number[index] = buf[i];
      index++;
    }
    else
    {
      number[index + 1] = '\0';
      switch(count)
      {

      case 0:
	e.roll = atof(number); 
	break;
      case 1:
	e.pitch = atof(number); 
	//printf("Pitch:%f\n",e.pitch);
	break;
      case 2:
	e.yaw = atof(number); 
	//printf("Yaw:%f\n",e.yaw);
	break;
      }

      count++;
      i++;
      index = 0;
    }
  }

}

struct Sensors
{
  int rightEnc;
  int leftEnc;
  int liftPot;
  int clawPot;
};

Sensors s;

void ParseSensors(char * buf, int bufLen)
{
  int index = 0;
  int count = 0;
  char number[10];
  bool messageExists = false;
  int beginBrace = 0;
  int endBrace   = 0;

  bool opened = false;
  for(int i = bufLen - 1; i >= 0; i--)
  {
    if(opened && buf[i] == '{')
    {
      beginBrace = i + 1;
      messageExists = true;
      break;
    }
    if(buf[i] == '}')
    {
      endBrace = i;
      opened = true;
    }
    
  }


  if(messageExists)
  {
    for(int i = beginBrace; i < endBrace; i++)
    {

      if(buf[i] != ',')
      {
	number[index] = buf[i];
	index++;
      }
      if(buf[i] == ',' || i == endBrace - 1)
      {	

	switch(count)
	{
	  
	case 0:
	  s.rightEnc = atoi(number);
	  break;
	case 1:
	  s.leftEnc = atoi(number); 
	  break;
	case 2:
	  s.liftPot = atoi(number); 
	  break;
	case 3:
	  s.clawPot = atoi(number); 
	  break;
	}
	
	count++;
	index = 0;
	memset(number, '\0', 10);
      }
    }
  }


}

enum Motors_s
{
  leftBack,
  leftFront,
  leftTop,
  rightBack,
  rightFront,
  rightTop,
  liftLeftBottom,
  liftRightBottom,
  liftTop,
  claw
};
int motors[10];


char tarCmd [] = {':', '`', '0', '\n'};
char QuatCmd[] = {':', '0','0' ,'\n'};
char EulerCmd[] = {':', '1','0' ,'\n'};

void motorCallback(const std_msgs::Int32MultiArray& motorPowers)
{
    for(int i =0;i<10;i++)
    {
        motors[i] = motorPowers.data[i];
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "Sensors_ros");
    ros::NodeHandle nh;

    ros::Publisher pubEuler = nh.advertise<geometry_msgs::Quaternion>("Robot/RPY",1000);
    ros::Publisher pubRightEnc = nh.advertise<std_msgs::Int32>("Robot/RightEnc",1000);
    ros::Publisher pubLeftEnc = nh.advertise<std_msgs::Int32>("Robot/LeftEnc",1000);
    ros::Publisher pubLift = nh.advertise<std_msgs::Int32>("Robot/LiftPot",1000);
    ros::Publisher pubClaw = nh.advertise<std_msgs::Int32>("Robot/ClawPot",1000);

    ros::Subscriber subMotor = nh.subscribe("Robot/Motors",1000,&motorCallback);

    geometry_msgs::Quaternion gyro;
    std_msgs::Int32 rightEnc;
    std_msgs::Int32 leftEnc;
    std_msgs::Int32 liftPot;
    std_msgs::Int32 clawPot;
    
   

      int fd, n, i;
      const int bufSize = 128;

      char buf[bufSize];
      struct termios toptions;

      /* open serial port */
      fd = open("/dev/serial/by-id/usb-2476_1010-if00", O_RDWR | O_NOCTTY);
      printf("Yost, fd opened as %i\n", fd);

      /* wait for the Arduino to reboot */
      usleep(35000);

      /* get current serial port settings */
      tcgetattr(fd, &toptions);
      /* set 9600 baud both ways */
      cfsetispeed(&toptions, B115200);
      cfsetospeed(&toptions, B115200);
      /* 8 bits, no parity, no stop bits */
      toptions.c_cflag &= ~PARENB;
      toptions.c_cflag &= ~CSTOPB;
      toptions.c_cflag &= ~CSIZE;
      toptions.c_cflag |= CS8;
      /* Canonical mode */
      toptions.c_lflag |= ICANON;
      /* commit the serial port settings */
      tcsetattr(fd, TCSANOW, &toptions);

      //Tare
      write(fd, ":`\n", 3);

    
      
      int fd2;
      /* My Arduino is on /dev/ttyACM0 */
      char buf2[256];
      char sendBuf2[128];   

      /* Open the file descriptor in non-blocking mode */
      fd2 = open("/dev/serial/by-id/usb-Arduino__www.arduino.cc__0042_5563930313535160C081-if00", O_RDWR | O_NOCTTY);
      printf("Arduino, fd opened as %i\n", fd2);
      /* Set up the control structure */
      struct termios toptions2;

      /* Get currently set options for the tty */
      tcgetattr(fd2, &toptions2);

      /* Set custom options */

      /* 9600 baud */
      cfsetispeed(&toptions2, B19200);
      cfsetospeed(&toptions2, B19200);
      /* 8 bits, no parity, no stop bits */
      toptions2.c_cflag &= ~PARENB;
      toptions2.c_cflag &= ~CSTOPB;
      toptions2.c_cflag &= ~CSIZE;
      toptions2.c_cflag |= CS8;
      /* no hardware flow control */
      toptions2.c_cflag &= ~CRTSCTS;
      /* enable receiver, ignore status lines */
      toptions2.c_cflag |= CREAD | CLOCAL;
      /* disable input/output flow control, disable restart chars */
      toptions2.c_iflag &= ~(IXON | IXOFF | IXANY);
      /* disable canonical input, disable echo,
         disable visually erase chars,
         disable terminal-generated signals */
      toptions2.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
      /* disable output processing */
      toptions2.c_oflag &= ~OPOST;

      /* wait for 12 characters to come in before read returns */
      /* WARNING! THIS CAUSES THE read() TO BLOCK UNTIL ALL */
      /* CHARACTERS HAVE COME IN! */
      toptions2.c_cc[VMIN] = 12;
      /* no minimum time to wait before read returns */
      toptions2.c_cc[VTIME] = 0;

      /* commit the options */
      tcsetattr(fd2, TCSANOW, &toptions2);

      /* Wait for the Arduino to reset */
      usleep(100000);
      /* Flush anything already in the serial buffer */
      tcflush(fd2, TCIFLUSH);

      int a = 0;
      while(true)
      {

        memset(buf2, '\0', 256);
        memset(sendBuf2, '\0', 128);
        /* read up to 128 bytes from the fd */
        int n2 = read(fd2, buf2, 128);
        ParseSensors(buf2, 128);	
	//printf("RightEnc:%d \n", s.rightEnc);
        rightEnc.data = s.rightEnc;
        leftEnc.data = s.leftEnc;
        liftPot.data = s.liftPot;
        clawPot.data = s.clawPot;
        pubRightEnc.publish(rightEnc);
        pubLeftEnc.publish(leftEnc);
        pubLift.publish(liftPot);
        pubClaw.publish(clawPot);

	//Sets Motor values
	ros::spinOnce();
	
	//Send Motor Values to the Cortex
        sendBuf2[0] = '{';
        sendBuf2[1] = '\0';
        for(int i = 0; i < 10; i++)
        {
          printf("motor%d:%d \n",i, motors[i]);
          char intStr[5];	
          sprintf(intStr, "%d:%d%c",i, motors[i], '\0');
          strcat(sendBuf2, "(");	
          strcat(sendBuf2, intStr);
          strcat(sendBuf2, ")");

        }
        strcat(sendBuf2, "}");

	if(a % 15 == 0)        
		printf("sendBuf:%s\n",sendBuf2);


        int i = 0;
        while(sendBuf2[i - 1] != '}')
        {
          write(fd2, &sendBuf2[i], 1);
          i++;
        }



        //Get Quaternion
        write(fd, &EulerCmd[0], 1);
        write(fd, &EulerCmd[1], 1);
        //write(fd, &EulerCmd[2], 1);  
        write(fd, &EulerCmd[3], 1);

        //Clear buffer and read incomming bytes
        memset(buf, '\0', bufSize);
        n = read(fd, buf, bufSize);
        //system("clear");
        //insert terminating zero in the string */
        ParseEuler(buf, n);
        buf[n] = 0;
        gyro.w = e.pitch;
        gyro.x = e.roll;
        gyro.y = e.yaw;
        pubEuler.publish(gyro);
        usleep(1000);
      
    }

}
