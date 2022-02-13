#include <WiFi.h>
#include "driver/adc.h"
#include <esp_sleep.h>
#define STA_SSID "####"
#define STA_PASS "####"

void disableWiFi(){
    adc_power_off();
    WiFi.disconnect(true);  // Disconnect from the network
    WiFi.mode(WIFI_OFF);    // Switch WiFi off
    Serial.println("");
    Serial.println("WiFi disconnected!");
}
void enableWiFi(){
    adc_power_on();
    WiFi.disconnect(false);  // Reconnect the network
    WiFi.mode(WIFI_STA);    // Switch WiFi off
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
    delay(1000);
    Serial.println("LIGHT SLEEP ENABLED FOR 5secs");
    delay(100);
    esp_sleep_enable_timer_wakeup(5 * 1000 * 1000);
    esp_light_sleep_start();
    Serial.println("LIGHT SLEEP WAKE UP");
}

void loop() {
}