#include <Arduino.h>
#include <U8g2lib.h>

#define OLED_CLOCK  15    //pins for OLED ONLY USE FOR OLED
#define OLED_DATA   4
#define OLED_RESET  16

int g_lineHeight = 0;

U8G2_SSD1306_128X64_NONAME_F_SW_I2C g_OLED(U8G2_R2,OLED_CLOCK,OLED_DATA,OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  g_OLED.begin();
  g_OLED.clear();
  g_OLED.setFont(u8g2_font_profont15_tf);

  g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent(); //decent in a negative number so - to add
  g_OLED.setCursor(0,g_lineHeight);                                //Place cursor at 0
  g_OLED.print("Hello world!!");
  g_OLED.setCursor(0,g_lineHeight * 2);
  g_OLED.printf("Line Height %d", g_lineHeight);
  g_OLED.sendBuffer();  //need to send the buffer 
}

void loop() {
  digitalWrite(LED_BUILTIN,0);
  delay(500);
  digitalWrite(LED_BUILTIN,1);
  delay(500);
}