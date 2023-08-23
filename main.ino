#include "GSM.h"
#include "MQTT.h"

void setup(){
  SerialMon.begin(115200);
  GSM_Setup();
  Mqtt_Setup();
  delay(1000);
  Mqtt_Connect();
}

void loop(){
  mqttClient.loop();
}
