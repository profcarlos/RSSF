/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Estabelece um WebServer com o ESP32. Realiza o acionamento de dois LEDs via rede WiFi.
  Origem:   https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
*********/

// Inclui biblioteca WiFi
#include "WiFi.h"
// Define as constantes de conexão de rede WiFi  
const char* ssid     = "GVT-76F4";
const char* password = "91DB072849";

// configura a porta do servidor para número 80
WiFiServer server(80);

// Variável para armazenar a requisição HTTP
String header;

// Variáveis auxiliares para armazenar o estado atual das saídas
String LED1State = "OFF";
String LED2State = "OFF";

// Configura os pinos utilizados para os LEDs
const int LED1 = 4;
const int LED2 = 2;

void setup() {
  // Inicializa a comunicação Serial
  Serial.begin(115200);
  // Inicializa as variáveis de saída
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  // Configura as saídas como desligadas
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  // Conecta à rede WiFi com o SSID e password
  Serial.print("Conectando à Rede WiFi ");
  Serial.println('.');
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  // Verifica o estado até estabelecar a conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
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
    while (client.connected()) {            // Mantenha um laço enquanto o Cliente está conectado
      if (client.available()) {             // Se existe byte para ler do cliente,
        char c = client.read();             // leia o byte
        Serial.write(c);                    // Apresente o byte lido
        header += c;
        if (c == '\n') {                    // Se o byte é um caractere de nova linha
          // Se a linha atual estiver em branco, você terá dois caracteres de nova linha seguidos.
          // Como é o fim da solicitação HTTP do cliente, envie uma resposta.
          if (currentLine.length() == 0) {
            // Cabeçalhos HTTP sempre começam com um código de resposta (e.g. HTTP/1.1 200 OK)
            client.println("HTTP/1.1 200 OK");
            // e um tipo de conteúdo para que o cliente saiba o que está por vir e, 
            client.println("Content-type:text/html");
            client.println("Conexão Fechada");
            // em seguida, uma linha em branco
            client.println();
            
            // Atualiza o estado dos LEDs
            if (header.indexOf("GET /LED1/ON") >= 0) {
              Serial.println("LED1 ON");
              LED1State = "ON";
              digitalWrite(LED1, HIGH);
            } else if (header.indexOf("GET /LED1/OFF") >= 0) {
              Serial.println("LED1 OFF");
              LED1State = "OFF";
              digitalWrite(LED1, LOW);
            } else if (header.indexOf("GET /LED2/ON") >= 0) {
              Serial.println("LED2 ON");
              LED2State = "ON";
              digitalWrite(LED2, HIGH);
            } else if (header.indexOf("GET /LED2/OFF") >= 0) {
              Serial.println("LED2 OFF");
              LED2State = "OFF";
              digitalWrite(LED2, LOW);
            }
            
            // Apresenta a página HTML ao Cliente
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // Utiliza CSS para configuração do estilo dos botões 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Apresenta o cabeçalho da página de Web
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Apresenta o estado atual do LED1 e botão 
            client.println("<p>LED1 - State " + LED1State + "</p>");
            // Se o LED1State está em OFF, apresenta o Botão ON       
            if (LED1State=="OFF") {
              client.println("<p><a href=\"/LED1/ON\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/LED1/OFF\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Apresenta o estado atual do LED2 e botão   
            client.println("<p>LED2 - State " + LED2State + "</p>");
            // Se o LED2State está em OFF, apresenta o Botão ON         
            if (LED2State=="OFF") {
              client.println("<p><a href=\"/LED2/ON\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/LED2/OFF\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // A resposta HTTP termina com outra linha em branco
            client.println();
            // Se respondeu ao Cliente, sai do laço while (client.connected())
            break;
          } else { // Se você que uma nova linha, então limpe a variável currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // se você tiver mais alguma coisa além de um caractere 
          currentLine += c;      // de retorno de carro, adicione à variável currentLine
        }
      }
    }
    // Limpa a variável do cabeçalho
    header = "";
    // Fecha a conexão com o Cliente
    client.stop();
    Serial.println("Cliente desconectado.");
    Serial.println("");
  }
}
