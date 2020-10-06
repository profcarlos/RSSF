/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Programa de testes do ESP8622. O LED interno pisca indefinidamente e escreve mensagem padrão.
  Origem:   https://www.instructables.com/NodeMCU-Basic-Project-Hello-World/
  URL adicional para Gerenciador de Placas: http://arduino.esp8266.com/stable/package_esp8266com_index.json
*********/
void setup() {
 Serial.begin(115200);
 // Habilita o LED onboard como saída
 pinMode(LED_BUILTIN, OUTPUT);
}
 
void loop() {
 // Escreve mensagem padrão de programação 
 Serial.println("Hello World");
 delay(500);
 // Faz o LED piscar (inverte o estado).
 digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
 // Espera para inverter o estado do LED.
 delay(500);
}
