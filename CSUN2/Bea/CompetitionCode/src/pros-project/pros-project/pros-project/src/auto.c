void autonomous() {
int x = 0;
while ( x < 5 ) {
printf("setting motor6 to 1\n");
motorSet(6,1);
delay(500);
printf("setting motor6 to 0\n");
motorSet(6,0);
delay(1500);
x++;
}
}
