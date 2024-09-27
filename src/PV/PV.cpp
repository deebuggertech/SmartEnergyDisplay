
#include "./PV.hpp"

namespace PV
{
    HTTPClient httpClient;
    DeserializationError error;
    JsonDocument doc;

    const int xPos = 214;

    int productionPeak = 0;
    double previousBatteryLevel = -1;

    String formatLargeNumber(int number)
    {
        String numStr = String(abs(number));
        String result;
        int len = numStr.length();

        for (int i = 0; i < len; i++)
        {
            if (i > 0 && (len - i) % 3 == 0)
            {
                result += '.';
            }
            result += numStr[i];
        }

        return (number < 0 ? "-" : "") + result;
    }

    void display()
    {
        httpClient.setTimeout(500);
        httpClient.begin(wifiClient, "INVERTER API"); /** http://  INVERTER IP ADDRESS  /solar_api/v1/GetPowerFlowRealtimeData.fcgi for Symo24 **/
        if (httpClient.GET() == 200)
        {
            error = deserializeJson(doc, httpClient.getString());
            if (error)
            {
                ErrorHandler::displayAlertSymbol();
            }
            else
            {
                if (doc["Body"]["Data"]["Site"]["P_PV"] > productionPeak)
                {
                    productionPeak = doc["Body"]["Data"]["Site"]["P_PV"];
                }

                tft.setTextColor(COLOR_TEXT, COLOR_CONTAINER);
                tft.setTextDatum(TL_DATUM);

                tft.setTextFont(6);
                tft.setCursor(100, xPos + 10);
                tft.print(formatLargeNumber((int)doc["Body"]["Data"]["Site"]["P_PV"]) + "      ");
                tft.setCursor(100, xPos + 10);
                tft.print(formatLargeNumber((int)doc["Body"]["Data"]["Site"]["P_PV"]));
                tft.setTextFont(4);
                tft.print("W");

                tft.drawString("Peak: " + formatLargeNumber(productionPeak) + "W    ", 100, xPos + 55, 4);

                tft.setTextFont(6);
                tft.setCursor(100, xPos + 105);
                tft.print(formatLargeNumber(-1 * ((int)doc["Body"]["Data"]["Site"]["P_Load"])) + "      ");
                tft.setCursor(100, xPos + 105);
                tft.print(formatLargeNumber(-1 * ((int)doc["Body"]["Data"]["Site"]["P_Load"])));
                tft.setTextFont(4);
                tft.print("W");

                double batteryLevel = doc["Body"]["Data"]["Inverters"]["1"]["SOC"];
                tft.setTextFont(6);
                tft.setCursor(100, xPos + 180);
                tft.print(String(batteryLevel, 1) + "    ");
                tft.setCursor(100, xPos + 180);
                tft.print(String(batteryLevel, 1));
                tft.setTextFont(4);
                tft.print("%");

                if (((int)doc["Body"]["Data"]["Site"]["P_Akku"]) > 0)
                {
                    tft.setTextColor(0xFCB2, COLOR_CONTAINER);
                }
                else
                {
                    tft.setTextColor(0x97F2, COLOR_CONTAINER);
                }
                tft.drawString(formatLargeNumber(-1 * ((int)doc["Body"]["Data"]["Site"]["P_Akku"])) + "W      ", 100, xPos + 225, 4);

                if (batteryLevel >= 66.0)
                {
                    if (previousBatteryLevel < 66)
                    {
                        DisplayUtils::displayImage(DisplayUtils::img_battery_3, xPos + 180, 20, DisplayUtils::img_battery_width, DisplayUtils::img_battery_height, COLOR_CONTAINER);
                    }
                }
                else if (batteryLevel >= 33.0)
                {
                    if (previousBatteryLevel < 33 || previousBatteryLevel >= 66.0)
                    {
                        DisplayUtils::displayImage(DisplayUtils::img_battery_2, xPos + 180, 20, DisplayUtils::img_battery_width, DisplayUtils::img_battery_height, COLOR_CONTAINER);
                    }
                }
                else if (batteryLevel >= 8.0)
                {
                    if (previousBatteryLevel < 8 || previousBatteryLevel >= 33.0)
                    {
                        DisplayUtils::displayImage(DisplayUtils::img_battery_1, xPos + 180, 20, DisplayUtils::img_battery_width, DisplayUtils::img_battery_height, COLOR_CONTAINER);
                    }
                }
                else
                {
                    if (previousBatteryLevel < 0 || previousBatteryLevel >= 8.0)
                    {
                        DisplayUtils::displayImage(DisplayUtils::img_battery_0, xPos + 180, 20, DisplayUtils::img_battery_width, DisplayUtils::img_battery_height, COLOR_CONTAINER);
                    }
                }

                previousBatteryLevel = batteryLevel;
            }
        }
        else
        {
            ErrorHandler::displayAlertSymbol();
        }
        httpClient.end();
    }

    void init()
    {
        tft.fillRoundRect(10, xPos, 300, 255, 15, COLOR_CONTAINER);
        DisplayUtils::displayImage(DisplayUtils::img_solar, xPos + 5, 20, DisplayUtils::img_solar_width, DisplayUtils::img_solar_height, COLOR_CONTAINER);
        DisplayUtils::displayImage(DisplayUtils::img_house, xPos + 87, 20, DisplayUtils::img_house_width, DisplayUtils::img_house_height, COLOR_CONTAINER);
        DisplayUtils::displayImage(DisplayUtils::img_battery_0, xPos + 180, 20, DisplayUtils::img_battery_width, DisplayUtils::img_battery_height, COLOR_CONTAINER);
    }

}