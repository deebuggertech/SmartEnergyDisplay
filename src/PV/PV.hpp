#pragma once

#include <ESP8266HTTPClient.h>
#include "ArduinoJson.h"

#include "../DisplayUtils/DisplayUtils.hpp"
#include "../ErrorHandler/ErrorHandler.hpp"
#include "../main.hpp"

namespace PV
{
    void display();
    void init();
}