#include "./ErrorHandler.hpp"

namespace ErrorHandler
{

  void update()
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      DisplayUtils::displayImage(DisplayUtils::img_wifi, 5, 149, DisplayUtils::img_wifi_width, DisplayUtils::img_wifi_height, COLOR_CONTAINER);
    }
    else
    {
      tft.fillScreen(TFT_WHITE);
      DisplayUtils::displayImage(DisplayUtils::img_warning_large, 140, 110, DisplayUtils::img_warning_large_width, DisplayUtils::img_warning_large_height, TFT_WHITE);
      tft.setTextFont(1);
      tft.setTextSize(2);
      tft.setTextDatum(TC_DATUM);
      tft.setTextColor(TFT_BLACK);
      tft.drawString("WIFI Connection Lost!", tft.width() / 2, 265);
      delay(10.000);
      DisplayUtils::fadeOut();
      ESP.restart();
    }
  }

  void displayAlertSymbol()
  {
    DisplayUtils::displayImage(DisplayUtils::img_warning, 5, 149, DisplayUtils::img_warning_width, DisplayUtils::img_warning_height, COLOR_CONTAINER);
  }

}