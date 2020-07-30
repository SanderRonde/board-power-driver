#include <ArduinoOTA.h>
#include <config.h>
#include <Arduino.h>
#include <telnet.h>
#include <power.h>
#include <msg.h>
#include <ota.h>
#include <net.h>

void setup()
{
	Serial.begin(115200);
	Serial.println("Booting");

	// Setup telnet
	Telnet::setup((String("power-board-") + KEY_NAME).c_str());

	// Setup OTA and wait
	OTA::setup();
	LOGN("Booted. Waiting for possible OTAs");
	OTA::wait_for_otas();
	LOGN("Stopped waiting");

	// Setup the rest
	Net::setup();
	Msg::setup();

	// Done
	LOGN("Booted");
}

void loop()
{
	OTA::loop();
	Msg::loop();
	Telnet::loop();
}
