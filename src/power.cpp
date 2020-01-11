#include <config.h>
#include <telnet.h>

namespace Power {
	void set(int value) {
		LOGF("Setting to %d\n", value);
		if (SWITCH_LED) {
			digitalWrite(LED_BUILTIN, value ? LOW : HIGH);
		}
		if (INVERT) {
			value = !value;
		}
		digitalWrite(POWER_PIN, value ? HIGH : LOW);
	}

	void setup() {
		if (SWITCH_LED) {
			pinMode(LED_BUILTIN, OUTPUT);
		}
		pinMode(POWER_PIN, OUTPUT);

		set(INVERT ? !DEFAULT_VALUE : DEFAULT_VALUE);
	}
}