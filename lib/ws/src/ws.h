#pragma once

#include <string.h>
#include <Arduino.h>

class SemiWebSocket {
	private:
		String _ws_id;
		bool _connected;
		int _refresh_interval;
		int _ping_interval;
		unsigned long _last_refresh;
		unsigned long _last_ping;
	public:
		char* get_type(char* payload);

		char* get_data(char* payload);

		void create_server();

		void close();

		void ping();

		void connect();

		void start_server();

		SemiWebSocket(void(*handler)(String event, String type, String data), 
					  int refresh_interval, int ping_interval);

		void send_message(String type, String data);

		void loop();
};