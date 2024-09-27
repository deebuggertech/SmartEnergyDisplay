#pragma once

#include <Arduino.h>
#include "TFT_eSPI.h"
#include "../main.hpp"

extern TFT_eSPI tft;

namespace DisplayUtils
{

    extern const int BACKLIGHT_PIN;
    extern const int DISPLAY_BRIGHTNESS;

    void setupScreen();

    void fadeIn();

    void fadeOut();

    void displayImage(const uint32_t *image, int x, int y, int width, int height, uint32_t color_image_background);

    void displayImageByName(const char *name, int x, int y, uint32_t color_image_background);

    void printHorizontallyCenteredAndRemoveAfterDelay(String msg, int y, const uint32_t color_text, const uint32_t color_background, int delayTime = 150);

    extern const int img_icon_width;
    extern const int img_icon_height;
    extern const uint32_t img_icon[];

    extern const int img_wifi_width;
    extern const int img_wifi_height;
    extern const uint32_t img_wifi[];
    extern const uint32_t img_no_wifi[];

    extern const int img_warning_width;
    extern const int img_warning_height;
    extern const uint32_t img_warning[];
    extern const int img_warning_large_width;
    extern const int img_warning_large_height;
    extern const uint32_t img_warning_large[];

    extern const int img_battery_width;
    extern const int img_battery_height;
    extern const uint32_t img_battery_0[] PROGMEM;
    extern const uint32_t img_battery_1[] PROGMEM;
    extern const uint32_t img_battery_2[] PROGMEM;
    extern const uint32_t img_battery_3[] PROGMEM;

    extern const int img_house_width;
    extern const int img_house_height;
    extern const uint32_t img_house[] PROGMEM;

    extern const int img_solar_width;
    extern const int img_solar_height;
    extern const uint32_t img_solar[] PROGMEM;

    extern const int img_weather_width;
    extern const int img_weather_height;
    extern const uint32_t img_weather_01d[] PROGMEM;
    extern const uint32_t img_weather_01n[] PROGMEM;
    extern const uint32_t img_weather_02d[] PROGMEM;
    extern const uint32_t img_weather_02n[] PROGMEM;
    extern const uint32_t img_weather_03d[] PROGMEM;
    extern const uint32_t img_weather_03n[] PROGMEM;
    extern const uint32_t img_weather_04d[] PROGMEM;
    extern const uint32_t img_weather_04n[] PROGMEM;
    extern const uint32_t img_weather_09d[] PROGMEM;
    extern const uint32_t img_weather_10d[] PROGMEM;
    extern const uint32_t img_weather_10n[] PROGMEM;
    extern const uint32_t img_weather_11d[] PROGMEM;
    extern const uint32_t img_weather_11n[] PROGMEM;
    extern const uint32_t img_weather_13d[] PROGMEM;
    extern const uint32_t img_weather_13n[] PROGMEM;
    extern const uint32_t img_weather_50d[] PROGMEM;
    extern const uint32_t img_weather_50n[] PROGMEM;

}