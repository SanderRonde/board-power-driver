#pragma once

#include <string.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

using namespace std;

namespace Net {
	String req(const char* host, int port, const char* path);

	void setup();

	void await_wifi();
}