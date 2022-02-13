#include <OneWire.h>
#include <DallasTemperature.h>
#include <CayenneMQTTESP32.h>
char ssid[] = "####";
char wifiPassword[] = "####";

char username[] = "######";
char password[] = "######";
char clientID[] = "######";

#define SENSOR_PIN 4 
#define VIRTUAL_CHANNEL 1

OneWire oneWire(SENSOR_PIN);
DallasTemperature sensors(&oneWire);

void setup()
{
	Serial.begin(9600);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
	sensors.begin();
}

void loop()
{
	Cayenne.loop();
}

// This function is called at intervals to send sensor data to Cayenne.
CAYENNE_OUT(VIRTUAL_CHANNEL)
{
	// Send the command to get temperatures.
	sensors.requestTemperatures();
// This command writes the temperature in Celsius to the Virtual Channel.
	Cayenne.celsiusWrite(VIRTUAL_CHANNEL, sensors.getTempCByIndex(0));
	}
