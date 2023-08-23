#include <PubSubClient.h>


//Configurações do MQTT
const char* mqttServer = "broker.hivemq.com";
const int mqttPorta = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
const char* mqttTopic = "RLX";

PubSubClient mqttClient(gsmClient);

void callback(char* topic, byte* payload, unsigned int length) {
  SerialMon.println("Mensagem MQTT recebida:");
  for (int i = 0; i < length; i++) {
    SerialMon.print((char)payload[i]);
  }
  SerialMon.println();
}

void Mqtt_Setup(){
  mqttClient.setServer(mqttServer, mqttPorta);
  mqttClient.setCallback(callback);
}

void Mqtt_Connect(){
  if(!mqttClient.connected()){
    SerialMon.println("Conectando ao broker MQTT...");
    if (mqttClient.connect("ESP32", mqttUser, mqttPassword)){
      SerialMon.println("Conexão MQTT estabelecida");
    } else {
      SerialMon.print("Falha na conexão MQTT, código do erro:");
      SerialMon.println(mqttClient.state());
      delay(5000);
      return;
    }
  }
}