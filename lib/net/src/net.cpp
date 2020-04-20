#include <string.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <net_secrets.h>
#include <net.h>

using namespace std;

ESP8266WiFiMulti WiFiMulti;

namespace Net {
	String req(const char* host, int port, const char* path) {
		// wait for WiFi connection
		await_wifi();

		String result = "?";

		HTTPClient http;
		http.setTimeout(2000);
		http.begin(host, port, path);
		http.addHeader("Content-Type", "text/plain");

		String body = "";
		int httpCode = http.POST(body);
		if(httpCode > 0) {
			if(httpCode != 200) {
				Serial.printf("Got err code %d and msg %s\n", httpCode, http.getString().c_str());
			} else {
				result = http.getString();
			}
		} else {
			Serial.printf("Got sending error %s\n", http.errorToString(httpCode).c_str());
		}
		http.end();

		return result;
	}

	bool _setup = false;
	void setup() {
		if (_setup) return;

		for (uint8_t t = 4; t > 0; t--) {
			Serial.printf("[SETUP] WAIT %d...\n", t);
			Serial.flush();
			delay(1000);
		}

		WiFi.mode(WIFI_STA);
		WiFiMulti.addAP(WIFI_SSID, WIFI_PW);

		_setup = true;
	}

	void await_wifi() {
		while (WiFiMulti.run() != WL_CONNECTED) {
			delay(1000);
		}
	}
}