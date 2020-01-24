
void callback(char* topic, byte * payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  String mensagem = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    mensagem += String((char)payload[i]);
  }
  //  Serial.print("\nrecebiido: ");
  //  Serial.println(mensagem);
  if (mensagem == "variable: estado with value: false") {
    digitalWrite(LED, HIGH);
    estado = false;
  }
  if (mensagem == "variable: estado with value: true") {
    digitalWrite(LED, LOW);
    estado = true;
  }
  Serial.println("\n-----------------------");
}

void verificaCliente() {
  if (!client.connected()) {
    Serial.print("Reconectando - se em ");
    Serial.println(mqttServer);
    while (!!!client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.print(".");
      delay(500);
    }
  }
}



void setupCliente() {
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Conectando ao MQTT...");
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("Conectado");
    } else {
      Serial.print("Falha na conexão MQTT: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  client.setCallback(callback);
  client.subscribe(mytopic);
}
