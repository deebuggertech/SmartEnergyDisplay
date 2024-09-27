#pragma once

#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"

#include "../DisplayUtils/DisplayUtils.hpp"
#include "../ErrorHandler/ErrorHandler.hpp"
#include "../Scheduler/Scheduler.hpp"
#include "../main.hpp"

namespace Weather
{
    void display();
    void init();

    double getOutsideTemperature();
    int getOutsideHumidity();
}