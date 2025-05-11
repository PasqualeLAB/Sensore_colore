
#include "Display.h"
#include "System.h"
#include "RGB_LED.h"

MD_TCS230 ColorSensor(S2_PIN, S3_PIN , S0_PIN, S1_PIN);
sensorData sens_data;
unsigned char rgb_data[3];

void setup() 
{
  unsigned long time_cal_switch = 0;
  
  Serial.begin(9600);
  init_system();
  digitalWrite(OE_PIN,LOW); //enable color sensor
  
  init_color_sensor(&ColorSensor);
  
  start_screen();
  start_led_animation();
  
  time_cal_switch = millis();
  while((digitalRead(CAL_SWITCH_PIN) == 0) && ((millis() - time_cal_switch) < WAIT_CAL_SWITCH));
  if((digitalRead(CAL_SWITCH_PIN) == 0) && ((millis() - time_cal_switch) >= WAIT_CAL_SWITCH))
  {
    StartSensorCalibration(&ColorSensor);
  }
  else
  {
    Serial.println("Sensor not calibrated, using default values");
  }
  
  
}

void loop() 
{
  while((digitalRead(CAL_SWITCH_PIN) == 1)); //wait switch trigger
  delay(200);
  ColorSensor.read();
  while(!ColorSensor.available());

  ColorSensor.getRaw(&sens_data);
  RawToRGB(&sens_data,rgb_data);
  Show_RGB_display(rgb_data);
  Show_RGB_LED(rgb_data);



}
