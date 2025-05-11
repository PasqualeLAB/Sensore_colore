#ifndef SYSTEM_H
#define SYSTEM_H

#include <MD_TCS230.h>
#include <FreqCount.h>

#define RED_PWM_PIN              3
#define GREEN_PWM_PIN            9
#define BLUE_PWM_PIN             6

#define S0_PIN              12
#define S1_PIN              11
#define S2_PIN              8
#define S3_PIN              7
#define OE_PIN              10
#define COLOR_PIN           5

#define CAL_SWITCH_PIN      2
#define WAIT_CAL_SWITCH     2000

#define BLACK_CAL           1
#define WHITE_CAL           2

void init_system(void);
void init_color_sensor(MD_TCS230 *CS);
void start_led_animation(void);
void StartSensorCalibration(MD_TCS230 *CS);
void RawToRGB(sensorData *sens_data,unsigned char* rgb_data);
#endif //SYSTEM_H