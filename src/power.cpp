#include <config.h>
#include <telnet.h>
#include <msg.h>

#define POLL_DELAY_S 10

namespace Power
{
	void set(int value)
	{
		LOGF("Setting to %d\n", value);
		if (digitalRead(MODE_PIN) == 1)
		{
			value = !value;
		}
		digitalWrite(POWER_PIN, value ? HIGH : LOW);
	}

	void set_effective(int value)
	{
		LOGF("Setting to effective %d\n", value);
		digitalWrite(POWER_PIN, value ? HIGH : LOW);
	}

	void setup()
	{
		pinMode(POWER_PIN, OUTPUT);
		pinMode(MODE_PIN, INPUT);

		set_effective(0);
	}

	unsigned long last_poll = millis();
	void loop()
	{
		if (millis() > last_poll + (POLL_DELAY_S * 1000))
		{
			last_poll = millis();

			set(Msg::value);
		}
	}
} // namespace Power