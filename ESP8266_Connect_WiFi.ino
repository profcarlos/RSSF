#include<ESP8266WiFi> 
/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Estabelece conexão WiFi com o ESP8266. O LED interno pisca indefinidamente caso afirmativo.
  Origem:   https://www.instructables.com/Getting-Started-With-ESP8266LiLon-NodeMCU-V3Flashi/
*********/

// Inclui biblioteca WiFi
const char* ssid = "Tenda"; //your WiFi Name
const char* password = "12345678";  //Your Wifi Password
int ledPin = 03; 
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  delay(10); 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 
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
  Serial.println("WiFi connected"); 
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  } 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush(); 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("");
  client.println("");
  client.print("Led is : "); 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }  client.println("");  
client.println(" On ");
   client.println(" Off ");  
  client.println(" ");
     delay(1);
   Serial.println("Client disonnected");
  Serial.println("");   }
