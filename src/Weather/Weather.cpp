
#include "./Weather.hpp"

namespace Weather
{
    HTTPClient httpClient;
    DeserializationError error;
    JsonDocument doc;

    int xPos = 43;

    double outsideTemperature = 0;
    int outsideHumidity = 0;

    bool previousAPICallSuccess = false;
    void updateData()
    { // refactored to avoid unnecessary API calls
        httpClient.setTimeout(500);
        httpClient.begin(wifiClient, "WEATHER API"); // see openweathermap.org
        if (httpClient.GET() == 200)
        {
            error = deserializeJson(doc, httpClient.getString());
            if (error)
            {
                previousAPICallSuccess = false;
                ErrorHandler::displayAlertSymbol();
            }
            else
            {
                previousAPICallSuccess = true;
            }
        }
        else
        {
            previousAPICallSuccess = false;
            ErrorHandler::displayAlertSymbol();
        }
        httpClient.end();
    }

    Scheduler apiCallScheduler(60000, updateData);


    void display()
    {
        apiCallScheduler.handle();
        if (previousAPICallSuccess)
        {
            outsideTemperature = doc["now"]["temp"];
            outsideHumidity = doc["now"]["humidity"];

            tft.setTextColor(COLOR_TEXT, COLOR_CONTAINER);
            tft.setTextDatum(TL_DATUM);
            tft.drawString((String)doc["forecast"][0]["time"], 20, xPos + 12, 4);
            DisplayUtils::displayImageByName(String(doc["forecast"][0]["icon"]).c_str(), xPos + 8, 90, COLOR_CONTAINER);
            tft.setTextDatum(CC_DATUM);
            tft.setCursor(160, xPos + 9);
            tft.setTextFont(6);
            tft.print((double)doc["forecast"][0]["temp"], 1);
            tft.setTextFont(4);
            tft.print("`");
            tft.print("C    ");
            tft.setTextDatum(CL_DATUM);
            tft.drawString(String((double)doc["forecast"][0]["pop"]*100.0, 0) + "%", 245, xPos + 58, 4);

            tft.setTextDatum(TL_DATUM);
            tft.drawString((String)doc["forecast"][1]["time"], 20, xPos + 94, 4);
            DisplayUtils::displayImageByName(String(doc["forecast"][1]["icon"]).c_str(), xPos + 89, 90, COLOR_CONTAINER);
            tft.setTextDatum(CC_DATUM);
            tft.setCursor(160, xPos + 89);
            tft.setTextFont(6);
            tft.print((double)doc["forecast"][1]["temp"], 1);
            tft.setTextFont(4);
            tft.print("`");
            tft.print("C    ");
            tft.setTextDatum(CL_DATUM);
            tft.drawString(String((double)doc["forecast"][1]["pop"]*100.0, 0) + "%", 245, xPos + 143, 4);
        }
    }

    bool initialGFXinit = true;
    void init()
    {
        tft.fillRoundRect(10, xPos, 300, 160, 15, COLOR_CONTAINER);
        if(initialGFXinit){
            updateData();
            initialGFXinit = false;
        }
        
    }

    double getOutsideTemperature()
    {
        return outsideTemperature;
    }

    int getOutsideHumidity()
    {
        return outsideHumidity;
    }
}