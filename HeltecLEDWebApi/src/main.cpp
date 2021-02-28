#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>

#define LED_PIN     2
#define NUM_LEDS    144
#define OLED_CLOCK  15
#define OLED_DATA   4
#define OLED_RESET  16

int g_Original_Brightness = 64;
int g_Brightness = g_Original_Brightness;
CRGB g_LEDs[NUM_LEDS] = {0};
int g_lineHeight = 0;

U8G2_SSD1306_128X64_NONAME_F_SW_I2C g_OLED(U8G2_R2,OLED_CLOCK,OLED_DATA,OLED_RESET);

//wifi vars
const char* ssid= "Narnia_Bogjangles_the_5th";
const char* password = "N@rn!aJynxB00fl@h43920726";

//web server on port 80
WebServer server(80);
char buffer[255];

StaticJsonDocument<255> jsonDocument;

void connectToWifi(){
  Serial.print("connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Wifi Connected");
  Serial.println(WiFi.localIP());

  g_OLED.clear();
  g_OLED.setCursor(0,g_lineHeight);
  g_OLED.print("Wifi Connected");
  g_OLED.setCursor(0,g_lineHeight *2 );
  g_OLED.print(WiFi.localIP().toString());
  g_OLED.sendBuffer();

}



void setRed(){
  Serial.println("setting leds to red");
  for (int i = 0; i < NUM_LEDS; i++)
     {
         g_LEDs[i] = CRGB::Red;
     }
     FastLED.show();
  server.send(200);
}

void setGreen(){
  Serial.println("setting leds to green");
  for (int i = 0; i < NUM_LEDS; i++)
     {
         g_LEDs[i] = CRGB::Green;
     }
     FastLED.show();
  server.send(200);
}


void setBlue(){
  Serial.println("setting leds to blue");
  for (int i = 0; i < NUM_LEDS; i++)
     {
         g_LEDs[i] = CRGB::Blue;
     }
     FastLED.show();
  server.send(200);
}

void setOff(){
  Serial.println("setting leds to off");
  for (int i = 0; i < NUM_LEDS; i++)
     {
         g_LEDs[i] = CRGB::Black;
     }
     FastLED.show();
  server.send(200);
}

void setupRouting(){
  server.on("/red", setRed);
  server.on("/green", setGreen);
  server.on("/blue", setBlue);
  server.on("/off", setOff);

  server.begin();
}

void setup() {
  g_OLED.begin();
  g_OLED.clear();
  g_OLED.setFont(u8g2_font_profont15_tf);

  g_lineHeight = g_OLED.getFontAscent() - g_OLED.getFontDescent();
  
  Serial.begin(115200);
  while(!Serial){}
  pinMode(LED_PIN,OUTPUT);
  //add leds
  FastLED.addLeds<WS2812B, LED_PIN,EOrder::GRB>(g_LEDs,NUM_LEDS);
  FastLED.setBrightness(g_Brightness);

 //insure that LEDs are set to off
  for (int i = 0; i < NUM_LEDS; i++)
  {
    g_LEDs[i] = CRGB::Black;
  }
  FastLED.show();
  
  connectToWifi();
  setupRouting();
     
}

void loop() {
  server.handleClient();
}