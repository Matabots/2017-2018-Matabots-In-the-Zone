int joystickGetAnalog ( unsigned char joystick, unsigned char axis);

void motorSet ( unsigned char channel, int speed);

void operatorControl() {
  int power;
  int turn;
    while (1) {
        power = joystickGetAnalog(1, 2); // vertical axis on left joystick
        turn  = joystickGetAnalog(1, 1); // horizontal axis on left joystick
        motorSet(2, power + turn); // set left wheels
        motorSet(3, power - turn); // set right wheels
        delay(20);
    }
}
void operatorControl() {
  printf("going into auto mode\n");
  autonomous();
  printf("going done auto mode\n");
}
