#include <config.h>
#include <telnet.h>
#include <power.h>
#include <ws.h>

#define PING_INTERVAL_MS (1000 * 60 * 60)

namespace Msg
{
	void ws_event(String event, String type, String data);

	int value = 0;
	SemiWebSocket ws = SemiWebSocket(ws_event, 5000, 60 * 1000);

	void on_value(int new_value)
	{
		int old_value = value;
		if (old_value != new_value)
		{
			LOGF("Different values %d, %d\n", old_value, new_value);
			Power::set(new_value);
		}
		else
		{
			LOGF("Same values %d, %d\n", old_value, new_value);
		}

		value = new_value;
	}

	void handle_msg(String type, String data)
	{
		if (type == "valChange")
		{
			on_value(atoi(data.c_str()));
		}
		else
		{
			LOGF("Unknown message %s, %s\n", type.c_str(), data.c_str());
		}
	}

	unsigned long last_ping = 0;
	void ws_event(String event, String type, String data)
	{
		if (event == "closed")
		{
			LOGF("[WSc] Disconnected!\n");
			last_ping = 0;
		}
		else if (event == "connected")
		{
			LOGF("[WSc] Connected\n");
			ws.send_message("listen", KEY_NAME);
			last_ping = millis();
		}
		else if (event == "message")
		{
			LOGF("[WSc] get text: %s %s\n", type.c_str(), data.c_str());
			handle_msg(type, data);
		}
		else
		{
			LOGF("[WSc] Unknown msg, %s\n", event.c_str());
		}
	}

	void setup()
	{
		Power::setup();
		ws.start_server();
		ws.connect();
	}

	void ping() {
		last_ping = millis();
		ws.send_message("ping", "");
	}

	void loop()
	{
		ws.loop();
		if (millis() > last_ping + PING_INTERVAL_MS) {
			ping();	
		}
	}
} // namespace Msg