#include "Display.h"
#include <stdio.h>


U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); //this instruction defines wich interface is used to drive OLED display

unsigned char Red_val[4];
unsigned char Green_val[4];
unsigned char Blue_val[4];

void display_init(void)
{
  u8g2.begin(); 
  u8g2.setFont(u8g2_font_ncenB10_tr);
}


void start_screen(void)
{
  u8g2.firstPage();
  do {
    u8g2.drawHLine(0,0,128);
    u8g2.drawStr(5,20,"Pasquale's LAB");
    u8g2.drawHLine(0,30,128);
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(4,60,"Color to RGB");
    u8g2.setFont(u8g2_font_ncenB10_tr);
  } while ( u8g2.nextPage() );
  delay(2000);
  u8g2.clear();
}

void Show_RGB_display(unsigned char * rgb_data)
{
  
  //dtostrf(V_out, 4, 2, sensor_val);
  sprintf(Red_val,"%d",rgb_data[0]);
  sprintf(Green_val,"%d",rgb_data[1]);
  sprintf(Blue_val,"%d",rgb_data[2]);
  u8g2.firstPage();
  do {
    u8g2.drawHLine(0,0,128);
    u8g2.drawHLine(0,63,128);
    u8g2.drawStr(0,20,"R: ");
    u8g2.drawStr(50,20,Red_val);
    u8g2.drawStr(0,40,"G:");
    u8g2.drawStr(50,40,Green_val);
    u8g2.drawStr(0,60,"B:");
    u8g2.drawStr(50,60,Blue_val);
    
  } while ( u8g2.nextPage() );
  
}

