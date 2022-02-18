#include <WiFi.h>
const char* ssid     = "########";
const char* password = "#########";
const char *ssid_Router = "####"; 
const char *password_Router = "#####"; 

void setup() {
  Serial.begin(115200);
  Serial.print("Setting AP (Access Point)…");
  boolean result = WiFi.softAP(ssid, password);
  if(result){
	  Serial.println("Ready");
	  Serial.println(String("Soft-AP IP address = ") + WiFi.softAPIP().toString());
	  Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
	  }
  else{
	  Serial.println("Failed!");
	  }
  Serial.println(" Access mode Setup End");
  Serial.println(" Station mode Setup start");
  WiFi.begin(ssid_Router, password_Router);
  Serial.println(String("Connecting to ")+ssid_Router);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected to:");
  Serial.println(WiFi.SSID());
  Serial.print("\IP Address:");
  Serial.println(WiFi.localIP());
  Serial.println(" Station Setup End");
}

void loop() {
}
