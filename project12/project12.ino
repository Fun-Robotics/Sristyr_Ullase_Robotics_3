#include <WiFi.h>
#include "driver/adc.h"
#define STA_SSID "####"
#define STA_PASS "####"
 unsigned long startLoop = millis();
 bool started = false;
 
void disableWiFi(){
    adc_power_off();
    WiFi.disconnect(true);  // Disconnect from the network
    WiFi.mode(WIFI_OFF);    // Switch WiFi off
    Serial.println("");
    Serial.println("WiFi disconnected!");
}

void setModemSleep() {
    disableWiFi();
    setCpuFrequencyMhz(40);
}
 
void enableWiFi(){
    adc_power_on();
    delay(200);
    WiFi.disconnect(false);  // Reconnect the network
    WiFi.mode(WIFI_STA);    // Switch WiFi off
    delay(200);
    Serial.println("START WIFI");
    WiFi.begin(STA_SSID, STA_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
     }
 
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}
 
void wakeModemSleep() {
    setCpuFrequencyMhz(240);
    enableWiFi();
}
 
void setup() {
    Serial.begin(115200); 
    Serial.println("START WIFI");
    WiFi.begin(STA_SSID, STA_PASS);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    setModemSleep();
    Serial.println("MODEM SLEEP ENABLED FOR 5secs");
}
 
void loop() {
    if (!started && startLoop+5000<millis()){
        wakeModemSleep();
        Serial.println("MODEM SLEEP DISABLED");
        started = true;
    }
}
