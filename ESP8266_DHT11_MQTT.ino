/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Estabelece comunicação via MQTT Broker e envia tópicos  dos sensores
            de temperatura e umidade do sensor DHT11 a cada cinco segundos            
  Origem:  https://randomnerdtutorials.com/esp8266-nodemcu-mqtt-publish-dht11-dht22-arduino/
     
*********/

// Inclui biblioteca WiFi
#include "ESP8266WiFi.h"
// Inclui bibliotecas do DHT
#include "Adafruit_Sensor.h"
#include "DHT.h"
// Inclui biblitecas de comunicação
#include "AsyncMqttClient.h"
#include "Ticker.h"

// Define as constantes de conexão de rede WiFi  
// Insere o nome da Rede WiFi
const char* WIFI_SSID = "Campos Oi Fibra 2G";
// Insere a senha da Rede WiFi
const char* WIFI_PASSWORD = "fdpcssm123";

// configura a porta do servidor para número 80
WiFiServer server(80);

// Configurações DHT
#define DHTTYPE DHT11     // Define o modelo DHT 11, DHT21, DHT22
#define DHTPIN D1         // Define o pino de conexão do sensor no ESP32
DHT dht(DHTPIN, DHTTYPE); // DHT (pino,tipo)

// Para uma nuvem MQTT broker, insere o domínio e porta
#define MQTT_HOST  "broker.mqtt-dashboard.com"
#define MQTT_PORT 1883

// Define os nomes variáveis do sensor DHT para o MQQT broker
#define MQTT_PUB_TEMP "esp8266/dht/temperature"
#define MQTT_PUB_HUM  "esp8266/dht/humidity"

// Define as variáveis para temperatura e umidade
float temp;
float hum;

// Cria um cliente MQTT
AsyncMqttClient mqttClient;
// 
Ticker mqttReconnectTimer;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

// Variáveis para registrar o intervalo de repetição de leitura
unsigned long previousMillis = 0;   
const long interval = 5000;        

// Rotina que faz a conexão com o Wi-Fi
void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

// Rotina que faz a conexão com o MQTT Broker
void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  Serial.println("Connected to Wi-Fi.");
  connectToMqtt();
}

// Rotina que faz a desconexão com o Wi-Fi
void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println("Disconnected from Wi-Fi.");
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.once(2, connectToWifi);
}

// Rotina de conexão do cliente com o MQTT
void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}
// Rotina que sinaliza estabelecimento de seção MQTT
void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
}
// Rotina que sinaliza a desconexão com o MQTT
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

/*void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}*/

// Rotina que sinaliza o endereço do pacote MQTT
void onMqttPublish(uint16_t packetId) {
  Serial.print("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

// Poxa, agora que vai executar o setup??
void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);
  Serial.println();
  // Inicializa o sensor DHT
  dht.begin();
  
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  //mqttClient.onSubscribe(onMqttSubscribe);
  //mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  // If your broker requires authentication (username and password), set them below
  //mqttClient.setCredentials("REPlACE_WITH_YOUR_USER", "REPLACE_WITH_YOUR_PASSWORD");
  
  connectToWifi();
}

void loop() {
  unsigned long currentMillis = millis();
  // A cada intervalo de tempo realiza a leitura do DHT
  if (currentMillis - previousMillis >= interval) {
    // Atualiza o valor de milisegundos anterior 
    previousMillis = currentMillis;
    // Realiza uma nova leitura do sensor de umidade
    hum = dht.readHumidity();
    // Realiza uma nova leitura do sensor de temperatura, em Celsius
    temp = dht.readTemperature();
    // Realiza uma nova leitura do sensor de temperatura, em Fahrenheit (isFahrenheit = true)
    //temp = dht.readTemperature(true);
    
    // Publica no MQTT mensagem do tópico esp8266/dht/temperature
    uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_TEMP, 1, true, String(temp).c_str());                            
    Serial.printf("Publishing on topic %s at QoS 1, packetId: %i ", MQTT_PUB_TEMP, packetIdPub1);
    Serial.printf("Message: %.2f \n", temp);

    // Publica no MQTT mensagem do tópico esp8266/dht/humidity
    uint16_t packetIdPub2 = mqttClient.publish(MQTT_PUB_HUM, 1, true, String(hum).c_str());                            
    Serial.printf("Publishing on topic %s at QoS 1, packetId %i: ", MQTT_PUB_HUM, packetIdPub2);
    Serial.printf("Message: %.2f \n", hum);
  }
}
