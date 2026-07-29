#include <Arduino.h>
#include <WIFI.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <secrets.h>

const char *topic = "beta/team";
WiFiClientSecure vuka;
PubSubClient mqttclient(vuka);

void connectClient(){
  vuka.setInsecure();
  mqttclient.setServer(mqtturl, port);
  while (!mqttclient.connected()) {
    String clientId = "esp32-" + String((uint32_t)ESP.getEfuseMac(), HEX);
    Serial.printf("MQTT: connecting as %s ", clientId.c_str());

    if (mqttclient.connect(clientId.c_str(), user, password1)) {
      Serial.println("-> connected.");
    } else {
      Serial.printf("-> failed (rc=%d). Retrying in 2s\n", mqttclient.state());
      delay(2000);
    } 
  }
}


void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  connectClient();
}

void loop()
{
mqttclient.loop();
mqttclient.publish(topic, "Hello from team Beta.You're a great team.");
delay(2000);
}




