/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Estabelece conexão WiFi com o ESP32. O LED interno pisca indefinidamente caso afirmativo.
  Origem:   https://techtutorialsx.com/2017/04/24/esp32-connecting-to-a-wifi-network/
*********/

// Inclui biblioteca WiFi
#include "WiFi.h"
// Define as constantes de conexão de rede WiFi  
const char* ssid     = "GVT-76F4";
const char* password = "91DB072849";
 
void setup() {
  // Inicializa comunicação serial
  Serial.begin(115200);
  //Habilita o LED onboard como saída
  pinMode(LED_BUILTIN, OUTPUT);
  // Inicializa comunicação WiFi
  WiFi.begin(ssid, password);
  //Verifica estado da conexão WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando à rede WiFi..");
  }
  Serial.println("Conectado à rede WiFi");
}
 
void loop() {
 //Faz o LED piscar (inverte o estado).
 digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
 delay(500);
}
