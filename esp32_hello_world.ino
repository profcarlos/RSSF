/**********
  IFG Campus Goiânia
  Autor:    Carlos Silveira
  Objetivo: Programa de testes do ESP32. O LED interno pisca indefinidamente e escreve mensagem padrão.
  Origem:   https://techtutorialsx.com/2017/04/24/esp32-hello-world/
  URLs adicionais para Gerenciadores de Placas: https://dl.espressif.com/dl/package_esp32_index.json 
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
