//servo.c
#include <stdio.h>
#include <stdlib.h>
#include  <wiringPi.h> 

int getDCValue(int angle, int maxPWMRange)
{
   float minDC = 1.75;
   float maxDC = 13.15;
   int requiredDC = (angle*(maxDC-minDC)/180+minDC)/100*maxPWMRange; 
   return requiredDC;
}

int main(int argc, char *argv[])
{
 if (argc==2)
 {
  int maxPWMRange = 2000;
  int rotateAngle = atoi(argv[1]);
  int dutyCycle = getDCValue(rotateAngle,maxPWMRange);
  wiringPiSetup ();
  pinMode (1, PWM_OUTPUT); //переводим вывод BCM18 в режим ШИМ выхода
  pwmSetMode(PWM_MODE_MS);   
  pwmSetClock(192);
  pwmSetRange(maxPWMRange);
  pwmWrite (1, dutyCycle);
  printf ("set PWM  value %d \n", dutyCycle);
 }
 else
 {
  printf ("Vvedite ugol povorota");
 }
}


