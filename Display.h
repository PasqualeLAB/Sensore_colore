#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

extern unsigned char UV_index;

void display_init(void);
void start_screen(void);
void display_update(unsigned int sens_read);
void Show_RGB_display(unsigned char * rgb_data);


#endif //DISPLAY_H