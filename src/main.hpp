#pragma once

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>

extern const uint32_t COLOR_BACKGROUND;
extern const uint32_t COLOR_TEXT;
extern const uint32_t COLOR_CONTAINER;

extern const char *WIFI_SSID;
extern const char *WIFI_PASS;
extern const char *FW_VERSION;

extern const int STANDBY_START;
extern const int STANDBY_END;
extern const bool RUN_CONTINUOUS;

extern WiFiClient wifiClient;

void setup();
void loop();