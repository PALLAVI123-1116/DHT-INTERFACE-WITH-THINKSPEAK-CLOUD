
#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

// -------- DHT11 Configuration --------
#define DHTPIN 21
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// -------- Wi-Fi Configuration --------
const char* ssid = "ma0019";
const char* password = "Froza@2007";

// -------- ThingSpeak Configuration --------
unsigned long channelID =3530447 ;
const char* writeAPIKey = "VAFVFADV5ERBOSUU";

WiFiClient client;

// Upload interval: 20 seconds
const unsigned long uploadInterval = 20000;
unsigned long lastUpload = 0;

void connectWiFi() {
  Serial.print("Connecting to Wi-Fi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nESP32 DHT11 ThingSpeak Logger");

  dht.begin();
  connectWiFi();

  ThingSpeak.begin(client);
}

void loop() {
  // Wait until the next 20-second upload
  if (lastUpload != 0 &&
      millis() - lastUpload < uploadInterval) {
    delay(100);
    return;
  }

  lastUpload = millis();

  // Reconnect Wi-Fi if disconnected
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected. Reconnecting...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);

    unsigned long startTime = millis();

    while (WiFi.status() != WL_CONNECTED &&
           millis() - startTime < 10000) {
      delay(500);
      Serial.print(".");
    }

    Serial.println();

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Wi-Fi reconnection failed.");
      return;
    }

    Serial.println("Wi-Fi reconnected!");
  }

  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check sensor readings
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT11 reading failed. Check wiring.");
    return;
  }

  // Display sensor readings
  Serial.println("\n--- DHT11 Sensor Data ---");
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  // Send readings to ThingSpeak
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);

  int responseCode = ThingSpeak.writeFields(
    channelID, writeAPIKey
  );

  if (responseCode == 200) {
    Serial.println("Upload successful!");
  } else {
    Serial.print("Upload failed. Response code: ");
    Serial.println(responseCode);
  }

  Serial.println("-------------------------");
}
