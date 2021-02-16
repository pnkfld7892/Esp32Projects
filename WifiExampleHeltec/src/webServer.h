#include "WiFi.h"
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "onOff.h"

extern String currentLine;
extern WiFiClient client;
extern unsigned long currentTime;
extern unsigned long previousTime;
extern unsigned long timeoutTime;
extern String header;
extern String outputState;
extern int original_brightness;
extern int g_Brightness;

void handleConnection() {
   while(client.connected() && currentTime - previousTime <= timeoutTime){
      currentTime = millis();
      if(client.available()){
        char c = client.read(); //read buyte
        Serial.write(c);
        header += c;
        if (c == '\n'){
          if(currentLine.length() == 0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type:text/html");
            client.println("Connection: close");
            client.println();

            if(header.indexOf("GET /on/blue") >= 0)
            {
              Serial.println("LEDs Blue");
              LedsOnBlue();
              outputState = "onB";
              FastLED.show();
            }
            else if(header.indexOf("GET /on/red") >= 0)
            {
              Serial.println("LEDs Red");
              LedsOnRed();
              outputState = "onR";
              FastLED.show();
            }
            else if(header.indexOf("GET /on/green") >= 0)
            {
              Serial.println("LEDs Green");
              LedsOnGreen();
              outputState = "onG";
              FastLED.show();
            }
            else if(header.indexOf("GET /off") >= 0){
              Serial.println("LEDs off");
              LedsOff();
              outputState = "off";
              FastLED.show();
            }
            else if(header.indexOf("GET /brightness/up") >=0 ){
              Serial.println("brightness before "+ g_Brightness);
              g_Brightness += 5;
              if(g_Brightness > 255)
                g_Brightness = 255;
              Serial.println("brightness after "+ g_Brightness);

              setBrightness(g_Brightness);
            }
            else if(header.indexOf("GET /brightness/down") >= 0){
              g_Brightness -= 5;
              if(g_Brightness <=5)
                g_Brightness = 5;
              setBrightness(g_Brightness);
            }
            else if(header.indexOf("GET /brightness/reset") >= 0){
              g_Brightness = original_brightness;
              setBrightness(g_Brightness);
            }
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button-red { background-color: #cf0000; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button-green { background-color: #009c06; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button-blue { background-color: #4c5baf; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button-off { background: #111111; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            
            client.println("</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.println("<p>LEDs State " + outputState + "</p>");
            if(outputState == "off"){
              client.println("<p><a href=\"/off\"><button class=\"button-off\">Off</button></a></p>");
              client.println("<p><a href=\"/on/red\"><button class=\"button-red\">ON Red</button></a></p>");
              client.println("<p><a href=\"/on/green\"><button class=\"button-green\">ON Green</button></a></p>");
              client.println("<p><a href=\"/on/blue\"><button class=\"button-blue\">ON Blue</button></a></p>");
            }
            else if (outputState == "onB"){
              client.println("<p><a href=\"/off\"><button class=\"button-off\">Off</button></a></p>");
              client.println("<p><a href=\"/on/red\"><button class=\"button-red\">ON Red</button></a></p>");
              client.println("<p><a href=\"/on/green\"><button class=\"button-green\">ON Green</button></a></p>");
              client.println("<p><a href=\"/on/blue\"><button class=\"button-blue\" disabled>ON Blue</button></a></p>");
            }
            else if (outputState == "onR"){
              client.println("<p><a href=\"/off\"><button class=\"button-off\">Off</button></a></p>");
              client.println("<p><a href=\"/on/red\"><button class=\"button-red\" disabled>ON Red</button></a></p>");
              client.println("<p><a href=\"/on/green\"><button class=\"button-green\">ON Green</button></a></p>");
              client.println("<p><a href=\"/on/blue\"><button class=\"button-blue\">ON Blue</button></a></p>");
            }
            else if (outputState == "onG"){
              client.println("<p><a href=\"/off\"><button class=\"button-off\">Off</button></a></p>");
              client.println("<p><a href=\"/on/red\"><button class=\"button-red\">ON Red</button></a></p>");
              client.println("<p><a href=\"/on/green\"><button class=\"button-green\" disabled>ON Green</button></a></p>");
              client.println("<p><a href=\"/on/blue\"><button class=\"button-blue\">ON Blue</button></a></p>");
            }
            client.println("</body></html>");

            client.println();
            break;
          }else{
            currentLine = "";
          }
        } else if(c != '\r'){
          currentLine += c;
        }
      }
    }
    
}