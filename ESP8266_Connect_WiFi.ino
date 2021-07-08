/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Estabelece conexão WiFi com o ESP8266. O LED interno pisca indefinidamente caso afirmativo.
  Origem:   https://www.instructables.com/Getting-Started-With-ESP8266LiLon-NodeMCU-V3Flashi/
*********/

// Inclui biblioteca WiFi
#include<ESP8266WiFi.h>

// Insere o nome da Rede WiFi
const char* ssid = "network";
// Insere a senha da Rede WiFi
const char* password = "password";  
// Define a porta de comunicação HTTP
WiFiServer server(80);

// Rotina de Configuração
void setup() {
  // Configura Comunicação Serial
  Serial.begin(115200);
  // Tempo para habilitar comunicação
  delay(10); 
  // Define o LED como saída
  pinMode(LED_BUILTIN, OUTPUT);
  // Desliga o LED
  digitalWrite(LED_BUILTIN, LOW);
  // Pula duas linhas
  Serial.println();
  Serial.println();
  // Sinaliza que está conectando na rede
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
  // Enquanto NÃO conecta na rede escreve um ponto
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Pula uma linha
  Serial.println("");
  // Sinaliza que está conectado
  Serial.println("WiFi connected");
  // Inicializa o Servidor HTTP
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  // O endereço do Servidor é o IP do Controlador
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}

void loop() {
  // Verifica se há alguma solicitação de Cliente
  WiFiClient client = server.available();
  // Se não houve, retorna
  if (!client) {
    return;
  }
  // Sinaliza comunicação com Cliente
  Serial.println("new client");
  // Enquanto Cliente não está pronto fica aguardando
  while(!client.available()){
    delay(1);
  } 
  // Faz a leitura da mensagem do Cliente e exclui a quebra de linha
  String request = client.readStringUntil('\r');
  // Imprime a mensage do Cliente
  Serial.println(request);
  // Descarta os bytes já lidos do Cliente
  client.flush(); 
  // Variável value recebe LOW
  int value = LOW;
  // Se a mensagem tem o texto LED=ON acende o LED
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(LED_BUILTIN, LOW);
    value = LOW;
  }
  // Se a mensagem tem o texto LED=OFF apaga o LED
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(LED_BUILTIN, HIGH);
    value = HIGH;
  }
  // Imprime mensage do estado do Servidor para o Cliente
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("");
  client.println("");
  // Informa o estado do LED (DARK apagado e BLUE acesso)
  client.print("LED IS: "); 
  if(value == HIGH) {
    client.print("DARK");
  } 
  else {
    client.print("BLUE");
  }
  // Apresenta informações para acesso ao LED  
  client.println("<br>");  
  client.println("<br>[Options: /LED=ON or /LED=OFF]<br>");
  client.println("<br>[LED TURN OFF in HIGH!]<br>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");   
  }
