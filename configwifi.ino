

void setupWifi() {
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("TP-LINK_355E", "campobauer");
  wifiMulti.addAP("Multilaser_2.4G_39C8D0", "12345678");
  wifiMulti.addAP("VIVO-1CD0", "V3XFWa9qXe");
  wifiMulti.addAP("Ariel", "arielariel");
  wifiMulti.addAP("NSI", "wickedbotz");
  Serial.println("\nConnecting Wifi...");
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando ao WiFi...");
  }
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(2000);
  }
}




void verificaWifi() {
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("REFAZENDO CONEXAO");
    setupWifi();
  } 
}
