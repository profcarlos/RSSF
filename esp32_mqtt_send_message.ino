/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Estabelece comunicação via WiFi utilizando o protocolo MQTT. 
            Pisca o LED interno a cada mensagem enviada.
  Origem:   https://www.arduinoecia.com.br/enviando-mensagens-mqtt-modulo-esp32-wifi/
  Sugestão de alteração do mqttServer: https://cursos.alura.com.br/forum/topico-erro-ao-conectar-com-o-mqtt-broker-82795
*********/

#include <WiFi.h>
#include <PubSubClient.h>
const char* ssid     = "GVT-76F4";
const char* password = "91DB072849";
const char* mqttServer = "broker.mqtt-dashboard.com";
const int mqttPort = 1883;
const char* mqttUser = "profcarlos";
const char* mqttPassword = "password";
WiFiClient espClient;
PubSubClient client(espClient);
int contador = 1;
char mensagem[30];
void setup()
{
  Serial.begin(115200);
  //Habilita o LED onboard como saída
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Iniciando conexao com a rede WiFi..");
  }
  Serial.println("Conectado na rede WiFi!");
}
void loop()
{
  //Faz a conexao com o broker MQTT
  reconectabroker();
  sprintf(mensagem, "MQTT ESP32 - Mensagem no. %d", contador);
  Serial.print("Mensagem enviada: ");
  Serial.println(mensagem);
  //Envia a mensagem ao broker
  client.publish("ArduinoeCia", mensagem);
  Serial.println("Mensagem enviada com sucesso...");
   delay(500);
  //Faz o LED piscar (inverte o estado).
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  //espera 500mS para inverter o estado do LED.
  delay(500);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  //Incrementa o contador
  contador++;
  
  //Aguarda 10 segundos para enviar uma nova mensagem
  delay(10000);
}
void reconectabroker()
{
  //Conexao ao broker MQTT
  client.setServer(mqttServer, mqttPort);
  while (!client.connected())
  {
    Serial.println("Conectando ao broker MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword ))
    {
      Serial.println("Conectado ao broker!");
    }
    else
    {
      Serial.print("Falha na conexao ao broker - Estado: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
