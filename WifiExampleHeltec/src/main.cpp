#include <Arduino.h>
#include "WiFi.h"

#define FASTLED_INTERNAL
#include <FastLED.h>
#include <U8g2lib.h>



#define NUM_LEDS      144      // FastLED definitions
#define LED_PIN       2
#define OLED_CLOCK    15
#define OLED_DATA     4
#define OLED_RESET    16


int original_brightness = 64;
int g_Brightness = 64;
CRGB g_LEDs[NUM_LEDS] = {0};
int g_lineHeight = 0;

U8G2_SSD1306_128X64_NONAME_F_SW_I2C g_OLED(U8G2_R2,OLED_CLOCK,OLED_DATA,OLED_RESET);

const char* ssid= "Narnia_Bogjangles_the_5th";
const char* password = "N@rn!aJynxB00fl@h43920726";



//web server
WiFiServer server(80);

//variable for HTTP messges
String header;
String outputState = "off";
String currentLine = "";
WiFiClient client;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
unsigned long timeoutTime = 2000;

//custom headers
#include "webServer.h"
#include "oled.h"

void setup() {
  // put your setup code here, to run once:

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
  //insure leds are all off on boot
  LedsOff();

  //setup wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  String message = "connecting";
  g_OLED.clear();
  g_OLED.setCursor(0,g_lineHeight);
  g_OLED.print(message);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wifi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP().toString());
  Serial.println("start oled stuff");
  g_OLED.clear();
  g_OLED.setCursor(0,g_lineHeight);
  g_OLED.print("Wifi Connected");
  g_OLED.setCursor(0,g_lineHeight *2 );
  g_OLED.print(WiFi.localIP().toString());
  g_OLED.sendBuffer();

  Serial.println("starting server");
  server.begin();
  
}

void loop() {
  // start up listener
  client = server.available();

  if(client) //when a new client connects
  {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client Connection!");
    currentLine = "";
   //clear header
    handleConnection();
    header = "";
    client.stop();
    Serial.println("Client Disconnected");
    Serial.println("");
  }
}