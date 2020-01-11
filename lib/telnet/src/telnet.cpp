#include <WiFiClient.h>
#include <Arduino.h>
#include <string.h>
#include <telnet.h>
#include <net.h>

#define TELNET_IP "192.168.1.3"
#define TELNET_PORT 1500

#define RETRY_TIME 30

namespace Telnet {
	WiFiClient client;

	char* _name = (char*) malloc(sizeof(char) * 50);
	void connect() {
		client.connect(TELNET_IP, TELNET_PORT);
		client.write("set-name:");
		client.write(_name);
		client.write("\n");
		client.write("Hi\n");
	}

	void setup(const char* name) {
		strcpy(_name, name);

		Net::setup();
		Net::await_wifi();

		connect();
	}

	unsigned long last_connect = millis();
	void loop() {
		if (millis() - last_connect > RETRY_TIME * 1000) {
			client.keepAlive();
			if (!client.connected()) {
				connect();
			}
		}
	}
}