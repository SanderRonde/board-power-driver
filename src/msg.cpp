#include <config.h>
#include <telnet.h>
#include <power.h>
#include <ws.h>

namespace Msg {
	void ws_event(String event, String type, String data);

	int value = 0;
	SemiWebSocket ws = SemiWebSocket(ws_event, 5000, 60 * 1000);

	void on_value(int new_value) {
		int old_value = value;
		if (old_value != new_value) {
			LOGF("Different values %d, %d\n", old_value, new_value);
			Power::set(new_value);
		} else {
			LOGF("Same values %d, %d\n", old_value, new_value);
		}

		value = new_value;
	}


	void handle_msg(String type, String data) {
		if (type == "valChange") {
			on_value(atoi(data.c_str()));
		} else {
			LOGF("Unknown message %s, %s\n", type.c_str(), data.c_str());
		}
	}

	void ws_event(String event, String type, String data) {
		if (event == "closed") {
			LOGF("[WSc] Disconnected!\n");
		} else if (event == "connected") {
			LOGF("[WSc] Connected\n");
			ws.send_message("listen", KEY_NAME);
		} else if (event == "message") {
			LOGF("[WSc] get text: %s %s\n", type.c_str(), data.c_str());
			handle_msg(type, data);
		} else {
			LOGF("[WSc] Unknown msg, %s\n", event.c_str());
		}
	}

	void setup() {
		Power::setup();
		ws.start_server();
		ws.connect();
	}
	
	void loop() {
		ws.loop();
	}
}