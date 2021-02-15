#include <Arduino.h>

#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS  144      // FastLED definitions
#define LED_PIN    15
#define LED_BUILTIN 2
int g_Brightness = 64;
CRGB g_LEDs[NUM_LEDS] = {0};

#include "marquee.h"
#include "twinkle.h"
#include "comet.h"
#include "flashRedBlue.h"
void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);

  while(!Serial){}
  Serial.println("ESP32 Startup marquee");

  FastLED.addLeds<WS2812B, LED_PIN,EOrder::GRB>(g_LEDs,NUM_LEDS);
  
}
void loop() {
  bool bLED = 0;
  // uint8_t initialHue = 0;
  // const uint8_t deltaHue = 16;
  // const uint8_t hueDensity = 4;

  for(;;){
    bLED = !bLED;
    //digitalWrite(LED_BUILTIN,bLED);
    //fill_rainbow(g_LEDs,NUM_LEDS,initialHue += hueDensity, deltaHue);
    //DrawComet(); 
    
    // g_LEDs[0] = CRGB::Blue;
   redPulse();
    // FastLED.show();
    // delay(1000);
    // g_LEDs[0] = CRGB::Black;
    // FastLED.show();
   }
}