# DHT-INTERFACE-WITH-THINKSPEAK-CLOUD
# ESP32 DHT11 ThingSpeak IoT Data Logger

An IoT temperature and humidity monitoring project using an **ESP32**, **DHT11 sensor module**, and **ThingSpeak**. The ESP32 reads temperature and relative humidity, prints the measurements to the Arduino Serial Monitor, and uploads them to a ThingSpeak channel over Wi-Fi.

## Features

- Reads temperature in degrees Celsius from the DHT11.
- Reads relative humidity in percent.
- Prints measurements and upload status to the Serial Monitor.
- Uploads temperature and humidity to ThingSpeak:
  - **Field 1:** Temperature (°C)
  - **Field 2:** Humidity (%)
- Uses **GPIO 21** as the DHT11 data pin.
- Uploads at a 20-second interval.

## Hardware Requirements

- ESP32 development board (for example, ESP32 DevKit V1)
- DHT11 sensor module
- Breadboard and jumper wires
- USB data cable
- Wi-Fi network with Internet access (2.4 GHz recommended)

## Wiring

| DHT11 module pin | ESP32 connection | Purpose |
|---|---|---|
| VCC | 3.3V | Sensor power |
| DATA / OUT | GPIO 21 | Digital data |
| GND | GND | Common ground |

> **Note:** Check the labels on your specific DHT11 module. If you are using a bare four-pin DHT11 sensor rather than a module, confirm its pin order from the datasheet and use a suitable pull-up resistor between DATA and 3.3V if required.

### Wiring diagram

Add the generated wiring image to this repository as `docs/esp32-dht11-gpio21-wiring.png`, then the diagram will render here:

![ESP32 and DHT11 wiring diagram](docs/esp32-dht11-gpio21-wiring.png)

## Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP32 board support package by Espressif Systems
- Arduino libraries:
  - **ThingSpeak** by MathWorks
  - **DHT sensor library** by Adafruit
  - **Adafruit Unified Sensor**

## ThingSpeak Setup

1. Sign in or create an account at [ThingSpeak](https://thingspeak.mathworks.com/).
2. Create a new channel named `ESP32 DHT11 Monitoring`.
3. Enable **Field 1** and name it `Temperature`.
4. Enable **Field 2** and name it `Humidity`.
5. Save the channel.
6. Open the channel's **API Keys** tab.
7. Copy the **Channel ID** and **Write API Key**. Keep the Write API Key private.

## Arduino IDE Setup

1. Install Arduino IDE.
2. Add the ESP32 board package URL in **File → Preferences → Additional Boards Manager URLs**, if needed:

   ```text
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```

3. Open **Tools → Board → Boards Manager**, search for `esp32`, and install **esp32 by Espressif Systems**.
4. Open **Sketch → Include Library → Manage Libraries**.
5. Install `ThingSpeak`, `DHT sensor library`, and `Adafruit Unified Sensor`.
6. Open the Arduino sketch (`esp32_dht11_thingspeak.ino`) and update the Wi-Fi and ThingSpeak settings.

## Configuration

Replace the example values in the sketch with your own credentials:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

unsigned long channelID = 1234567;
const char* writeAPIKey = "YOUR_WRITE_API_KEY";
```

- `ssid`: your Wi-Fi network name
- `password`: your Wi-Fi password
- `channelID`: your ThingSpeak channel ID
- `writeAPIKey`: the channel's Write API Key

**Security:** Do not commit real Wi-Fi credentials or ThingSpeak API keys to a public repository. For a public Git repository, consider moving credentials into a separate untracked configuration file or entering them locally before compiling.

## Upload and Run

1. Connect the DHT11 module to the ESP32 as shown in the wiring table.
2. Connect the ESP32 to your computer using a USB data cable.
3. In Arduino IDE, select your ESP32 board (for example, **ESP32 Dev Module**) and the correct COM port.
4. Replace the placeholder credentials.
5. Click **Verify**, then **Upload**.
6. Open **Tools → Serial Monitor** and set the baud rate to **115200**.
7. Open your ThingSpeak channel's **Private View** and confirm that the data appears in Field 1 and Field 2.

## Example Serial Monitor Output

The values below are illustrative; actual measurements depend on the environment.

```text
ESP32 DHT11 ThingSpeak Logger
Connecting to Wi-Fi....
Wi-Fi connected!
IP Address: 192.168.1.105

--- DHT11 Sensor Data ---
Temperature: 29.0 *C
Humidity: 65.0 %
Upload successful!
-------------------------
```

## Data Flow

1. DHT11 measures temperature and humidity.
2. ESP32 reads the sensor values through GPIO 21.
3. ESP32 displays the values on the Serial Monitor.
4. ESP32 sends the values over Wi-Fi to ThingSpeak.
5. ThingSpeak stores the readings and displays time-series charts.

## Troubleshooting

| Issue | Things to check |
|---|---|
| `DHT11 reading failed` | Confirm DATA is connected to GPIO 21, check VCC/GND, and ensure `DHTTYPE` is `DHT11`. |
| Wi-Fi does not connect | Verify the SSID/password and use a compatible 2.4 GHz Wi-Fi network. |
| ThingSpeak upload fails | Check Internet access, Channel ID, Write API Key, and channel fields. |
| No chart data appears | Open the correct channel's Private View and confirm Fields 1 and 2 are enabled. |
| Repeated upload errors | Check the HTTP response code in Serial Monitor and confirm the channel update rate is permitted. |

## Repository Structure

A suggested repository layout:

```text
esp32-dht11-thingspeak/
├── README.md
├── esp32_dht11_thingspeak.ino
└── docs/
    ├── esp32-dht11-gpio21-wiring.png
    ├── block-diagram.png
    └── flowchart.png
```

## Notes

- The example sketch uploads one ThingSpeak update every 20 seconds.
- Keep the upload interval within your ThingSpeak plan's rate limits.
- The ESP32 must have Internet access for cloud logging.
- This project is intended for learning and prototyping.

## License

Choose a license before publishing this repository. If you want others to reuse and modify the code, consider an open-source license such as the MIT License.
