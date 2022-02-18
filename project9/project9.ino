#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "######";
const char* password = "######";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open

  //IPAddress IP = WiFi.softAPIP();
  //Serial.print("AP IP address: ");
 // Serial.println(IP);
  boolean result = WiFi.softAP(ssid, password);
  if(result){
	  Serial.println("Ready");
	  Serial.println(String("Soft-AP IP address = ") + WiFi.softAPIP().toString());
	  Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
	  }
  else{
	  Serial.println("Failed!");
	  }
  Serial.println("Setup End");
  }

void loop() {
}
