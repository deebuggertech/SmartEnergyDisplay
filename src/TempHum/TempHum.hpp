#pragma once

#include <HTU21D.h>

#include "../DisplayUtils/DisplayUtils.hpp"
#include "../ErrorHandler/ErrorHandler.hpp"
#include "../Weather/Weather.hpp"
#include "../main.hpp"

namespace TempHum
{
    void display();
    void init();

    void setupSensor();
}