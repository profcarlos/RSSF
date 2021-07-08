/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Programa de testes do ESP8622. Semáforo de três lâmpadas.
  Origem: ?
  URL adicional para Gerenciador de Placas: http://arduino.esp8266.com/stable/package_esp8266com_index.json
*********/
// Tabela de definições de pinos digitais
// Disponível em: https://github.com/esp8266/Arduino/issues/584

static const uint8_t TRUE   = 1;
static const uint8_t FALSE  = 0;

#define LED_VERDE    D0
#define LED_AMARELO  D1
#define LED_VERMELHO D3
#define BOTAO        D7

void setup() {
 Serial.begin(115200);
 // Habilita o LED onboard como saída
 pinMode(LED_BUILTIN, OUTPUT);
 digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
 delay(500);
 // Define LEDS do semáforo como saída
 pinMode(LED_VERDE, OUTPUT);
 pinMode(LED_AMARELO, OUTPUT);
 pinMode(LED_VERMELHO, OUTPUT);
 // Confirma todos LEDS apagados
 digitalWrite(LED_VERDE, HIGH);
 digitalWrite(LED_AMARELO, HIGH);
 digitalWrite(LED_VERMELHO, HIGH);
 // Configura BOTAO como saída
 pinMode(BOTAO, OUTPUT);
 
}

void loop() {
 // Simula o Semáforo
 if(digitalRead(BOTAO) == TRUE){
  delay(1000);
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_AMARELO, LOW);
  delay(2000);
  digitalWrite(LED_AMARELO, HIGH);
  digitalWrite(LED_VERMELHO, LOW);
    delay(4000);
  digitalWrite(LED_VERMELHO, HIGH);
  digitalWrite(LED_VERDE, LOW);
  delay(3000);
 }
}
