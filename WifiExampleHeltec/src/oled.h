#pragma once
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C g_OLED;
extern int g_lineHeight;
void oledClearAndPrint(char* message){
    g_OLED.clear();
    g_OLED.setCursor(0,g_lineHeight);
    g_OLED.print(message);
    g_OLED.sendBuffer();
}
