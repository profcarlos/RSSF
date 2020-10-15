/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Estabelece um WebServer com o ESP32 para apresentar dados do sensor DHT11. 
  Origem:   https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
            
  Imagem na página: https://circuits4you.com/2018/01/31/upload-image-png-jpeg-to-esp8266-web-page/
  Fórum sobre imagem: https://forum.arduino.cc/index.php?topic=599971.0
*********/
// Tabela de definições de pinos digitais
// Disponível em: https://github.com/esp8266/Arduino/issues/584
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;

// Inclui biblioteca WiFi
#include<ESP8266WiFi.h>
// Inclui bibliotecas do DHT
#include "Adafruit_Sensor.h"
#include "DHT.h"
// #include "DHT_U.h"

// Define as constantes de conexão de rede WiFi  
// Insere o nome da Rede WiFi
const char* ssid = "Campos Oi Fibra 2G";
// Insere a senha da Rede WiFi
const char* password = "fdpcssm123";

// configura a porta do servidor para número 80
WiFiServer server(80);

// Configurações DHT
#define DHTTYPE DHT11     // Define o modelo DHT 11, DHT21, DHT22
#define DHTPIN D1          // Define o pino de conexão do sensor
DHT dht(DHTPIN, DHTTYPE); // DHT (pino,tipo)
// Define variáveis tipo char
char temp[6];
char umid[6];

void setup() {
  // Inicializa a comunicação Serial
  Serial.begin(115200);
  // Inicializa comunicação DHT
  dht.begin();                 
  // Inicializa as variáveis de saída
  pinMode(LED_BUILTIN, OUTPUT);

  // Conecta à rede WiFi com o SSID e password
  Serial.print("Conectando à Rede WiFi ");
  Serial.println('.');
  // Apaga LED da placa 
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  // Verifica o estado até estabelecar a conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Quando conecta acende o LED da placa
  digitalWrite(LED_BUILTIN, LOW);
  // Apresenta o endereço de IP local e inicializa o WebServer
  Serial.println("");
  Serial.println("Conectado à Rede WiFi.");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Escuta os Clientes recebidos

  if (client) {                             // Se um novo cliente conectou,
    Serial.println("Novo Cliente.");        // imprime uma mensagem pela porta Serial
    String currentLine = "";                // String para armazenar dados recebidos do cliente
    // Cabeçalhos HTTP sempre começam com um código de resposta (e.g. HTTP/1.1 200 OK)
    client.println("HTTP/1.1 200 OK");
    // e um tipo de conteúdo para que o cliente saiba o que está por vir e, 
    client.println("Content-type:text/html");
    client.println("Conexão Fechada");
    // em seguida, uma linha em branco
    client.println();
                            
    // Apresenta a página HTML ao Cliente
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
  
    // Apresenta o cabeçalho da página de Web
    client.println("<body><h1>ESP8266 Web Server</h1>");
    client.println("<img src=\"https://img.elo7.com.br/product/zoom/1050AA0/totem-display-minions-90-cm-festa-minions.jpg\" alt=\"Minion\" height=\"120\" width=\"60\">");
    while (client.connected()) {            // Mantenha um laço enquanto o Cliente está conectado      
      // Realiza a leitura da temperatura e umidade
      float umid =  dht.readHumidity();    
      float temp =  dht.readTemperature(); 
      Serial.print(umid);
      Serial.print(" : ");
      Serial.println(temp);
      // Apresenta o valor atual da temperatura e umidade
      client.println("<p>Temperatura: " + String(temp) + "    Umidade: " + String(umid) + "</p>");
      // A resposta HTTP termina com outra linha em branco
      delay(1000);      
    }
    client.stop();
    Serial.println("Cliente desconectado.");
    Serial.println("");
  }
}
