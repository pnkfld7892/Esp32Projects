#include <Arduino.h>
#include "WiFi.h"

#define FASTLED_INTERNAL
#include <FastLED.h>

#define NUM_LEDS  144      // FastLED definitions
#define LED_PIN    15
#define LED_BUILTIN 2
int original_brightness = 64;
int g_Brightness = 64;
CRGB g_LEDs[NUM_LEDS] = {0};

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
#include "webServer.h"
void setup() {
  // put your setup code here, to run once:
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
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wifi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
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