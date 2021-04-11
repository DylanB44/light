#include <Adafruit_NeoPixel.h>


#include <WiFi.h>

const char* ssid     = "";
const char* password = "";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);     

    delay(10);

   

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available(); 

  if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";             
    while (client.connected()) {           
      if (client.available()) {            
        char c = client.read();             
        Serial.write(c);                  
        if (c == '\n') {                   
      
          if (currentLine.length() == 0) {
     
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
      
                                            
                                            class Strip
                                            {
                                            public:
                                              uint8_t   effect;
                                              uint8_t   effects;
                                              uint16_t  effStep;
                                              unsigned long effStart;
                                              Adafruit_NeoPixel strip;
                                              Strip(uint16_t leds, uint8_t pin, uint8_t toteffects, uint16_t striptype) : strip(leds, pin, striptype) {
                                                effect = -1;
                                                effects = toteffects;
                                                Reset();
                                              }
                                              void Reset(){
                                                effStep = 0;
                                                effect = (effect + 1) % effects;
                                                effStart = millis();
                                              }
                                            };
                                            
                                            struct Loop
                                            {
                                              uint8_t currentChild;
                                              uint8_t childs;
                                              bool timeBased;
                                              uint16_t cycles;
                                              uint16_t currentTime;
                                              Loop(uint8_t totchilds, bool timebased, uint16_t tottime) {currentTime=0;currentChild=0;childs=totchilds;timeBased=timebased;cycles=tottime;}
                                            };
                                            
                                            Strip strip_0(308, 5, 308, NEO_RGB + NEO_KHZ800);
                                            struct Loop strip0loop0(1, false, 1);
                                            
                                            //[GLOBAL_VARIABLES]
                                            
                                            void setup() {
                                            
                                              //Your setup here:
                                            
                                              strip_0.strip.begin();
                                            }
                                            
                                            void loop() {
                                            
                                              //Your code here:
                                            
                                              strips_loop();
                                            }
                                            
                                            void strips_loop() {
                                              if(strip0_loop0() & 0x01)
                                                strip_0.strip.show();
                                            }
        
                                            
                                            uint8_t strip0_loop0() {
                                                uint8_t ret = 0x00;
                                                switch(strip0loop0.currentChild) {
                                                  case 0: 
                                                         ret = strip0_loop0_eff0();break;
                                                }
                                                if(ret & 0x02) {
                                                  ret &= 0xfd;
                                                  if(strip0loop0.currentChild + 1 >= strip0loop0.childs) {
                                                    strip0loop0.currentChild = 0;
                                                    if(++strip0loop0.currentTime >= strip0loop0.cycles) {strip0loop0.currentTime = 0; ret |= 0x02;}
                                                  }
                                                  else {
                                                    strip0loop0.currentChild++;
                                                  }
                                                };
                                                return ret;
                                            }
                                            
                                            uint8_t strip0_loop0_eff0() {
                                                // Strip ID: 0 - Effect: Rainbow - LEDS: 308
                                                // Steps: 66 - Delay: 20
                                                // Colors: 3 (255.0.0, 0.255.0, 0.0.255)
                                                // Options: rainbowlen=297, toLeft=false, 
                                              if(millis() - strip_0.effStart < 20 * (strip_0.effStep)) return 0x00;
                                              float factor1, factor2;
                                              uint16_t ind;
                                              for(uint16_t j=0;j<308;j++) {
                                                ind = 66 - (uint16_t)(strip_0.effStep - j * 0.2222222222222222) % 66;
                                                switch((int)((ind % 66) / 22)) {
                                                  case 0: factor1 = 1.0 - ((float)(ind % 66 - 0 * 22) / 22);
                                                          factor2 = (float)((int)(ind - 0) % 66) / 22;
                                                          strip_0.strip.setPixelColor(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
                                                          break;
                                                  case 1: factor1 = 1.0 - ((float)(ind % 66 - 1 * 22) / 22);
                                                          factor2 = (float)((int)(ind - 22) % 66) / 22;
                                                          strip_0.strip.setPixelColor(j, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
                                                          break;
                                                  case 2: factor1 = 1.0 - ((float)(ind % 66 - 2 * 22) / 22);
                                                          factor2 = (float)((int)(ind - 44) % 66) / 22;
                                                          strip_0.strip.setPixelColor(j, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
                                                          break;
                                                }
                                              }
                                              if(strip_0.effStep >= 66) {strip_0.Reset(); return 0x03; }
                                              else strip_0.effStep++;
                                              return 0x01;                                         
                                              }
        }

        
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(5, LOW);                
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
