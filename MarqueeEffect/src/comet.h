// draws a moving comet with fading tail


#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

extern CRGB g_LEDs[];

void DrawComet()
{
    //FastLED.clear(false);
    const byte fadeAmt = 64;    //fraciton of 256y to fade a pixel
    const int cometSize = 5;    //size of comet block
    const int deltaHue = 4;     //how far to step the color wheel
    const double cometSpeed = 0.5;

    static byte hue = HUE_RED;
    static int iDirection = 1;
    static double iPos = 0.0;


    hue += deltaHue;
    iPos += iDirection * cometSpeed;

    if(iPos == (NUM_LEDS - cometSize) || iPos == 0)
        iDirection *= -1;
    
    for(int i = 0; i<cometSize; i++){
        g_LEDs[(int)iPos + i ].setHue(hue);
    }
    //fade the leds
    for (int j = 0; j < NUM_LEDS; j++)
        if(random(2) == 1)
            g_LEDs[j] = g_LEDs[j].fadeToBlackBy(fadeAmt);
    delay(15);
}