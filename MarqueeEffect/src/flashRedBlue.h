#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

extern CRGB g_LEDs[];
extern int g_Brightness;

void flashRedAndBlue()
{
    FastLED.setBrightness(g_Brightness);
    for(int i = 0; i < NUM_LEDS; i++){
      g_LEDs[i] = CRGB::Red;
    }
    FastLED.show();
    delay(500);
    for(int i = 0; i < NUM_LEDS; i++){
      g_LEDs[i] = CRGB::Blue;
    }
    FastLED.show();
    delay(500);
}

void redPulse()
{
    FastLED.setBrightness(g_Brightness);
    for(int i = 0; i < NUM_LEDS; i++){
      g_LEDs[i] = CRGB::Red;
    }
    FastLED.show();
    delay(100);

    FastLED.setBrightness(g_Brightness/2);
    FastLED.show();
    delay(50);
    FastLED.setBrightness(g_Brightness);
    FastLED.show();
    delay(100);
}

void flashGreenAndPurple(){
     FastLED.setBrightness(g_Brightness);
    for(int i = 0; i < NUM_LEDS; i++){
      g_LEDs[i] = CRGB::Green;
    }
    FastLED.show();
    delay(500);
    for(int i = 0; i < NUM_LEDS; i++){
      g_LEDs[i] = CRGB::Purple;
    }
    FastLED.show();
    delay(250);
    for(int i = 0; i < NUM_LEDS; i++){
      g_LEDs[i] = CRGB::Blue;
    }
    FastLED.show();
    delay(500);
}