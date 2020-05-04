#include "WiFi.h"
 
const char* ssid     = "GVT-76F4";
const char* password = "91DB072849";
 
void setup() {
 
  Serial.begin(115200);
  //Habilita o LED onboard como saída
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}
 
void loop() {
  //Faz o LED piscar (inverte o estado).
 digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
 //espera 250mS para inverter o estado do LED.
 delay(500);
}
