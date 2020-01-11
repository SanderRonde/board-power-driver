#include <net.h>
#include <WiFiClient.h>
#include <string.h>
#include <telnet.h>

#define TELNET_IP "192.168.1.3"
#define TELNET_PORT 1500

namespace Telnet {
	WiFiClient client;

	void setup(const char* name) {
		Net::setup();
		Net::await_wifi();

		client.connect(TELNET_IP, TELNET_PORT);
		client.write("set-name:");
		client.write(name);
		client.write("\n");
		client.write("Hi\n");
	}
}