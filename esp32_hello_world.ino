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