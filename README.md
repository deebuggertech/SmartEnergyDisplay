# Smart Energy Display

![Smart Energy Display](https://github.com/user-attachments/assets/faa0a9b6-2562-4863-b81f-c6f07d383fd3)

The Smart Energy Display project utilizes an ESP8266 microcontroller and an ILI9488 display to provide real-time energy monitoring for a photovoltaic system. It displays battery levels, consumption information, data from a weather forecast service, and readings from an internal temperature sensor (HTU21D).

## Features

- Real-time monitoring of PV system energy output
- Battery level and consumption information display
- Weather forecast integration using an external API
- Internal temperature and humidity monitoring via HTU21D sensor

## Getting Started

### Prerequisites


- ESP8266 microcontroller
- ILI9488 display
- HTU21D temperature/humidity sensor
- Female headers and wires or a connector PCB
- PV system inverter with an API for accessing real-time information (e.g., Fronius Symo24)
- Weather forecast API credentials (e.g., OpenWeatherMap)
- Soldering equipment (for hardware setup)
- A computer with VSCode and PlatformIO installed (for software development)

### Setup

1. **Connect all hardware components:**
    - Follow the provided schematic or use the project PCB design:
      ![Schematic](https://github.com/user-attachments/assets/9f393ba8-d408-4580-9a5c-d769d9b3bdb2)

2. **Clone the repository:**
    - Visit the repository on GitHub and download the project files.

3. **Modify the code:**
    - Open the `main.cpp` file in the Arduino IDE.
    - Locate the section for Wi-Fi credentials and input your details:
      ```cpp
      const char *WIFI_SSID = "SSID"; // Replace with your Wi-Fi SSID
      const char *WIFI_PASS = "PASS";  // Replace with your Wi-Fi Password
      ```

    - Open `weather.cpp` and `pv.cpp`, and manually input the necessary API endpoints or additional configuration settings as needed. For example, locate sections similar to:
      ```cpp
      const char* weatherApiEndpoint = "YOUR_WEATHER_API_ENDPOINT"; // Replace with your Weather API endpoint
      const char* pvApiEndpoint = "YOUR_PV_API_ENDPOINT"; // Replace with your PV API endpoint
      ```

4. **Upload the code to your ESP8266 - Done!**

    - Once the device is powered on, the display will show real-time energy monitoring data, including battery levels, energy consumption, and weather information.

### Contributing

Contributions are welcome! If you have suggestions for improvements or features, please create a pull request or open an issue.

### License

This project is licensed under the MIT License.
