#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 
Adafruit_BME280 bme;

const char* ssid = "####";
const char* password = "####";

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
}

void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe("esp32/message");
      }      
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    } 
    Serial.println("");
     Serial.println("Connected to Wi-Fi");

  if (!bme.begin(0x76)) {
    Serial.println("Check BME280 connections!");
  }
  setupMQTT();
}

void loop() {
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
  long now = millis();
  long previous_time = 0;
  
  if (now - previous_time > 1000) {
    previous_time = now;
    
    float temperature = bme.readTemperature();
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    mqttClient.publish("esp32/temperature", tempString);
 
    float humidity = bme.readHumidity();
    char humString[8];
    dtostrf(humidity, 1, 2, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);
    mqttClient.publish("esp32/humidity", humString);

    float pressure = bme.readPressure() / 100;
    char pressString[8];
    dtostrf(pressure, 1, 2, pressString);
    Serial.print("Pressure: ");
    Serial.println(pressString);
    mqttClient.publish("esp32/pressure", pressString);
    
  }
}
  void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }
}
