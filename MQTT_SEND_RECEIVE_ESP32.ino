#include <WiFi.h>
#include <WiFiMulti.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);
WiFiMulti wifiMulti;



const char* mqttServer = "mqtt.tago.io";// Servidor MQTT
const int mqttPort = 1883;// porta MQTT // pode ser passado qualquer valor como user
const char* mqttUser = "Default"; // Token do device no Tago.io
const char* mqttPassword = "df6b8d67-7e11-459e-9411-ab0d19a24f9c";
char topic[] = "tago/data/post";// Tópico MQTT a ser enviado para o Tago.io
char mytopic[] = "tago/my_topic";// Tópico MQTT a ser enviado para o Tago.io


float umidade;
float temperatura;
int luminosidade;
String str_sta = "estado";
String str_umi = "umidade";
String str_temp = "temperatura";
String str_lum = "luminosidade";
#define LED 2
//#define relay_pin 2 // pin 12 can also be used


long previewMillis;
#define tempoMQTT  10000
bool estado = false;



void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  setupWifi();
  setupCliente();
}



void loop() {
  client.loop();
  long currentMillis =  millis();
  if (currentMillis - previewMillis > tempoMQTT) {
    previewMillis = currentMillis;
    verificaWifi();
    verificaCliente();
    umidade++;
    temperatura++;
    luminosidade++;
    enviaDado(str_lum, luminosidade);
  }
}



void enviaDado(String variable, float dado) {
  String dadoString = String(dado);
  String dadoXXX = "[{\"variable\":\"" + variable + "\",\"value\":" + dadoString + "}]";
  Serial.print("Enviando payload: ");
  Serial.println(dadoXXX);
  if (client.publish(topic, (char*) dadoXXX.c_str())) {
    Serial.println(String("Publish  " + dadoXXX + " "));
  } else {
    Serial.println(String("Publish " + dadoXXX + " failed"));
  }
}
