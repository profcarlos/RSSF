/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Apresenta características da rede WiFi. O LED interno pisca indefinidamente caso afirmativo.
  Origem:   https://techtutorialsx.com/2017/06/29/esp32-arduino-getting-started-with-wifi/
*********/

// Inclui biblioteca WiFi
#include "WiFi.h"
// Define as constantes de conexão de rede WiFi  
const char* ssid     = "GVT-76F4";
const char* password = "91DB072849";

// Retorna String correspondente às características da conexão estabelecida
String translateEncryptionType(wifi_auth_mode_t encryptionType) {
 
  switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
      return "Open";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}

// Apresenta as redes encontradas e suas características 
void scanNetworks() {
 
  int numberOfNetworks = WiFi.scanNetworks();
 
  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);
 
  for (int i = 0; i < numberOfNetworks; i++) {
 
    Serial.print("Nome da Rede: ");
    Serial.println(WiFi.SSID(i));
 
    Serial.print("Nível de Sinal: ");
    Serial.println(WiFi.RSSI(i));
 
    Serial.print("Endereço MAC: ");
    Serial.println(WiFi.BSSIDstr(i));
 
    Serial.print("Tipo de Criptografia: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
 
  }
}
// Estabelece a conexão WiFi 
void connectToNetwork() {
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Estabelecendo conexão ao WiFi..");
  }
 
  Serial.println("Conectado à Rede WiFi");
 
}
 
void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  // Configura o pino do LED interno como saída
  pinMode(LED_BUILTIN, OUTPUT);
  scanNetworks();
  connectToNetwork();
  // Escreve as características da conexão estabelecida
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
  // Desconecta o ESP32 da rede WiFi
  WiFi.disconnect(true);
  Serial.println(WiFi.localIP());
 
}
 
void loop() {
 //Faz o LED piscar (inverte o estado).
 digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
 //espera para inverter o estado do LED.
 delay(500);
}
