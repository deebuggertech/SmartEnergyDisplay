#include "./TempHum.hpp"

namespace TempHum
{
    HTU21D sensor;

    int xPos = 43;

    void display()
    {
        if (sensor.measure())
        {
            tft.setTextDatum(TC_DATUM);

            tft.setTextColor(0xFCB2, COLOR_CONTAINER);

            tft.drawString("IN", 40, 77, 4);

            tft.setTextColor(0x94BF, COLOR_CONTAINER);

            tft.drawString("OUT", 40, 152, 4);

            tft.setTextColor(COLOR_TEXT, COLOR_CONTAINER);

            tft.setTextDatum(CC_DATUM);

            tft.setCursor(78, xPos + 19);
            tft.setTextFont(6);
            tft.print(String(sensor.getTemperature(), 1));
            tft.setTextFont(4);
            tft.print("`");
            tft.print("C");

            tft.setTextDatum(CC_DATUM);
            tft.setCursor(78, xPos + 99);
            tft.setTextFont(6);
            tft.print(String(Weather::getOutsideTemperature(), 1));
            tft.setTextFont(4);
            tft.print("`");
            tft.print("C");

            tft.setTextDatum(CC_DATUM);
            tft.setCursor(218, xPos + 19);
            tft.setTextFont(6);
            tft.print(String(sensor.getHumidity(), 0));
            tft.setTextFont(4);
            tft.print("%");

            tft.setTextDatum(CC_DATUM);
            tft.setCursor(218, xPos + 99);
            tft.setTextFont(6);
            tft.print(String(Weather::getOutsideHumidity()));
            tft.setTextFont(4);
            tft.print("%");
        }
        else
        {
            ErrorHandler::displayAlertSymbol();
            sensor.reset();
        }
    }

    void init()
    {
        tft.fillRoundRect(10, xPos, 300, 160, 15, COLOR_CONTAINER);
    }

    void setupSensor()
    {
        sensor.begin();
    }

}