#pragma once

#include <string.h>
#include <Arduino.h>

#define POWER_PIN D1
#define KEY_NAME String("room.speakers.desk")
#define SWITCH_LED 0
#define INVERT 0

// Default value. Ignores invert in the
// sense that it sets the state to what was
// passed to it and doesn't invert it afterwards
#define DEFAULT_VALUE 0