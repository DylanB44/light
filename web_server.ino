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

            client.print("Click <a href=\"/H\">here</a> for rainbow on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn off .<br>");

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
      
                                            
                                           //where the code for the light strip needs to be so when the web server has /H it will execute that code.
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
