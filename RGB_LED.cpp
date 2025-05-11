#include "RGB_LED.h"
#include "System.h"

void Show_RGB_LED(unsigned char * rgb)
{
  analogWrite(RED_PWM_PIN,(255 - rgb[0]));
  analogWrite(GREEN_PWM_PIN,(255 - rgb[1]));
  analogWrite(BLUE_PWM_PIN,(rgb[2]));
}