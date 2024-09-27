#include "./Time.hpp"

namespace Time
{
  time_t currentTime;
  struct tm timeInfo;

  int posY = 0;

  String formatTwoDigits(int value)
  {
    return value < 10 ? "0" + String(value) : String(value);
  }

  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  void display()
  {
    time(&currentTime);
    localtime_r(&currentTime, &timeInfo);
    tft.setTextColor(COLOR_TEXT, COLOR_CONTAINER);
    tft.setTextDatum(TL_DATUM);
    tft.drawString(formatTwoDigits(timeInfo.tm_mday) + "." + months[timeInfo.tm_mon], 20, posY + 5, 4);
    tft.setTextDatum(TR_DATUM);
    tft.drawString("   " + formatTwoDigits(timeInfo.tm_hour) + ":" + formatTwoDigits(timeInfo.tm_min), 300, posY + 5, 4);
  }

  void init()
  {
    tft.fillRoundRect(10, posY - 10, 300, 42, 15, COLOR_CONTAINER);
  }

  int getHour(){
    time(&currentTime);
    localtime_r(&currentTime, &timeInfo);
    return timeInfo.tm_hour;
  }
}
