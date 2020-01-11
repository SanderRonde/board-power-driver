#pragma once

#include <WiFiClient.h>

#define LOG Telnet::client.print
#define LOGN Telnet::client.println
#define LOGLN LOGN
#define LOGF Telnet::client.printf

namespace Telnet {
	extern WiFiClient client;

	void setup(const char* name);

	void loop();
}