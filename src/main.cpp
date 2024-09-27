#include "./main.hpp"
#include "DisplayUtils/DisplayUtils.hpp"

#include "Time/Time.hpp"
#include "Weather/Weather.hpp"
#include "TempHum/TempHum.hpp"
#include "PV/PV.hpp"

#include "ErrorHandler/ErrorHandler.hpp"
#include "Scheduler/Scheduler.hpp"

const uint32_t COLOR_BACKGROUND = 0x0;
const uint32_t COLOR_TEXT = 0xFFFF;
const uint32_t COLOR_CONTAINER = 0x3186;

const char *WIFI_SSID = "SSID";
const char *WIFI_PASS = "PASS";

const char *FW_VERSION = "2.8.4 (28.07.2024)";

const int STANDBY_START = 23;
const int STANDBY_END = 6;
const bool RUN_CONTINUOUS = false;

WiFiClient wifiClient;

Scheduler *timeUpdateScheduler;
Scheduler *weatherAndTempHumUpdateScheduler;
Scheduler *pvUpdateScheduler;

Scheduler *errorHandlerScheduler;

Scheduler *standbyCheckScheduler;

void boot()
{
  DisplayUtils::setupScreen();
  DisplayUtils::displayImage(DisplayUtils::img_icon, 130, 85, DisplayUtils::img_icon_width, DisplayUtils::img_icon_height, COLOR_BACKGROUND);
  DisplayUtils::fadeIn();
  delay(750);
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Firmware version: " + String(FW_VERSION), 450, COLOR_TEXT, COLOR_BACKGROUND, 1000);
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Processor frequency: " + String(ESP.getCpuFreqMHz()) + "MHz", 450, COLOR_TEXT, COLOR_BACKGROUND);
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Reset reason: " + String(ESP.getResetReason()), 450, COLOR_TEXT, COLOR_BACKGROUND);
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Initializing sensors...", 450, COLOR_TEXT, COLOR_BACKGROUND);
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Connecting to WIFI...", 450, COLOR_TEXT, COLOR_BACKGROUND, 500);
  WiFi.mode(WIFI_STA);
  WiFi.hostname("SmartEnergyDisplay");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int wifi_connect_attempts = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Connecting to WIFI - Attempt " + String(wifi_connect_attempts++), 450, COLOR_TEXT, COLOR_BACKGROUND, 2000);
  }
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Connected!", 450, COLOR_TEXT, COLOR_BACKGROUND, 500);
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("IP Address: " + WiFi.localIP().toString(), 450, COLOR_TEXT, COLOR_BACKGROUND, 2000);
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Hostname: " + WiFi.hostname(), 450, COLOR_TEXT, COLOR_BACKGROUND, 2000);
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Setting up NTP...", 450, COLOR_TEXT, COLOR_BACKGROUND);
  configTime("CET-1CEST,M3.5.0,M10.5.0/3", "europe.pool.ntp.org");
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Setting up Sensors...", 450, COLOR_TEXT, COLOR_BACKGROUND);
  TempHum::setupSensor();
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Setting up OTA...", 450, COLOR_TEXT, COLOR_BACKGROUND);
  ArduinoOTA.setHostname("SmartEnergyDisplay");
  ArduinoOTA.setPassword("nutella");
  ArduinoOTA.begin();
  DisplayUtils::printHorizontallyCenteredAndRemoveAfterDelay("Setup finished!", 450, COLOR_TEXT, COLOR_BACKGROUND, 500);
  delay(500);
  DisplayUtils::fadeOut();
  tft.fillScreen(COLOR_BACKGROUND);
}

bool standby = false;
void runStandbyCheck()
{
  if (!RUN_CONTINUOUS)
  {
    if ((Time::getHour() >= STANDBY_START && STANDBY_START > STANDBY_END) || (Time::getHour() >= STANDBY_START && Time::getHour() < STANDBY_END && STANDBY_START < STANDBY_END))
    {
      if (!standby)
      {
        tft.fillScreen(TFT_WHITE);
        DisplayUtils::displayImage(DisplayUtils::img_warning_large, 140, 110, DisplayUtils::img_warning_large_width, DisplayUtils::img_warning_large_height, TFT_WHITE);
        tft.setTextFont(1);
        tft.setTextSize(2);
        tft.setTextDatum(TC_DATUM);
        tft.setTextColor(TFT_BLACK);
        tft.drawString("Activating Standby", tft.width() / 2, 265);
        delay(10000);
        DisplayUtils::fadeOut();
        standby = true;
      }
    }
    else
    {
      if (standby)
      {
        ESP.restart();
      }
    }
  }
}

bool weatherActive = true;
void weatherAndTempHumUpdate(){
  if(weatherActive){
    TempHum::init();
    TempHum::display();
    weatherActive = false;
  } else {
    Weather::init();
    Weather::display();
    weatherActive = true;
  }
}

void setup()
{
  boot();

  Time::init();
  Weather::init();
  PV::init();

  Time::display();
  Weather::display();
  PV::display();
  
  if (WiFi.status() == WL_CONNECTED) ErrorHandler::update();

  timeUpdateScheduler = new Scheduler(10000, Time::display);

  weatherAndTempHumUpdateScheduler = new Scheduler(6500, weatherAndTempHumUpdate);

  pvUpdateScheduler = new Scheduler(5000, PV::display);

  errorHandlerScheduler = new Scheduler(60000, ErrorHandler::update);

  standbyCheckScheduler = new Scheduler(10000, runStandbyCheck);

  DisplayUtils::fadeIn();
}

int last = 0;
void loop()
{
  ArduinoOTA.handle();

  standbyCheckScheduler->handle();

  if (!standby)
  {
    timeUpdateScheduler->handle();
    weatherAndTempHumUpdateScheduler->handle();
    pvUpdateScheduler->handle();
    errorHandlerScheduler->handle();
  }

}
