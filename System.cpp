#include <Arduino.h>
#include "System.h"
#include "Display.h"

sensorData sdBlack = { 7770, 6720, 8840 };  //default values for black (minimum)
sensorData sdWhite = { 54390, 51740, 69490 }; //default value for white (maximum)

void Calibrate(MD_TCS230 *CS,uint8_t cal_type,sensorData *cal_data);

void init_system(void)
{
  display_init();
  pinMode(RED_PWM_PIN, OUTPUT);
  pinMode(GREEN_PWM_PIN, OUTPUT);
  pinMode(BLUE_PWM_PIN, OUTPUT);

  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);
  pinMode(OE_PIN, OUTPUT);
  pinMode(COLOR_PIN, INPUT);

  pinMode(CAL_SWITCH_PIN, INPUT);

  analogWrite(RED_PWM_PIN, 255);
  analogWrite(GREEN_PWM_PIN, 255);
  analogWrite(BLUE_PWM_PIN, 255);
}

void init_color_sensor(MD_TCS230 *CS)
{
  CS->begin();
  delay(500);
  CS->setSampling(TCS230_FREQ_MID); ///< 20% prescaler
}

void start_led_animation(void)
{
  analogWrite(RED_PWM_PIN, 0);
  analogWrite(GREEN_PWM_PIN, 255);
  analogWrite(BLUE_PWM_PIN, 255);
  delay(1000);
  analogWrite(RED_PWM_PIN, 255);
  analogWrite(GREEN_PWM_PIN, 0);
  analogWrite(BLUE_PWM_PIN, 255);
  delay(1000);
  analogWrite(RED_PWM_PIN, 255);
  analogWrite(GREEN_PWM_PIN, 255);
  analogWrite(BLUE_PWM_PIN, 0);
  delay(1000);
  analogWrite(RED_PWM_PIN, 255);
  analogWrite(GREEN_PWM_PIN, 255);
  analogWrite(BLUE_PWM_PIN, 255);
}

void StartSensorCalibration(MD_TCS230 *CS)
{
  Serial.println("Black calibration: please point sensor on a black sample");
  delay(1000);
  Serial.println("Press button to calibrate");
  while(digitalRead(CAL_SWITCH_PIN) == 1);
  Calibrate(CS,BLACK_CAL,&sdBlack);
  delay(500);
  Serial.println("White calibration: please point sensor on a white sample");
  while(digitalRead(CAL_SWITCH_PIN) == 1);
  Calibrate(CS,BLACK_CAL,&sdWhite);
  delay(500);
  Serial.println("DONE");
  for(int i = 0; i < 3; i++)
  {
    Serial.print(sdBlack.value[i]);
    Serial.print("      ");
    Serial.println(sdWhite.value[i]);
  }
}

void Calibrate(MD_TCS230 *CS,uint8_t cal_type,sensorData *cal_data)
{
  

  CS->read();
  while(!(CS->available()));
  CS->getRaw(cal_data);
  
/*for(int i = 0; i < 3; i++)
  {
    Serial.println(cal_data->value[i]);
    
  }*/

  if(cal_type == BLACK_CAL)
  {
    CS->setDarkCal(cal_data);
  }
  else if(cal_type == WHITE_CAL)
  {
    CS->setWhiteCal(cal_data);	
  }
  else;
}

void RawToRGB(sensorData *sens_data,unsigned char* rgb_data)
{
  rgb_data[0] = map(sens_data->value[0],sdBlack.value[0],sdWhite.value[0],0,255);
  rgb_data[1] = map(sens_data->value[1],sdBlack.value[1],sdWhite.value[1],0,255);
  rgb_data[2] = map(sens_data->value[2],sdBlack.value[2],sdWhite.value[2],0,255);

  

}


