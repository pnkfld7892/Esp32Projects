#define FASTLED_INTERNAL
#include <FastLED.h>
extern CRGB g_LEDs[];

 void LedsOnBlue(){
     for (int i = 0; i < NUM_LEDS; i++)
     {
         g_LEDs[i] = CRGB::Blue;
     }
     FastLED.show();
}

 void LedsOnRed(){
     for (int i = 0; i < NUM_LEDS; i++)
     {
         g_LEDs[i] = CRGB::Red;
     }
     FastLED.show();
}

 void LedsOnGreen(){
     for (int i = 0; i < NUM_LEDS; i++)
     {
         g_LEDs[i] = CRGB::Green;
     }
     FastLED.show();
}

void LedsOff(){
 for (int i = 0; i < NUM_LEDS; i++)
     {
         g_LEDs[i] = CRGB::Black;
     }
     FastLED.show();
}

void setBrightness(int b){
    FastLED.setBrightness(b);
    FastLED.show();
}