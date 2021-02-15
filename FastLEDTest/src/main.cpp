#include <Arduino.h>
//#include <U8g2lib.h>
#define FASTLED_INTERNAL
#include <FastLED.h>


#define NUM_LEDS  25       // FastLED definitions
#define LED_PIN    15
#define LED_BUILTIN 2

CRGB g_LEDs[NUM_LEDS] = {0};

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);

  while(!Serial){}
  Serial.println("ESP32 Startup");

  FastLED.addLeds<WS2812B, LED_PIN,GRB>(g_LEDs,NUM_LEDS);
  FastLED.setBrightness(10);
}

void loop() {
  bool bLED = 0;
  uint8_t initialHue = 0;
  const uint8_t deltaHue = 16;
  const uint8_t hueDensity = 4;

  for(;;){
    bLED = !bLED;
    //digitalWrite(LED_BUILTIN,bLED);
    fill_rainbow(g_LEDs,NUM_LEDS,initialHue += hueDensity, deltaHue);
    delay(20);
    FastLED.show();
  }
}