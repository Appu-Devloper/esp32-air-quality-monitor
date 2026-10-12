#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// WiFi details
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingSpeak details
unsigned long channelID = YOUR_CHANNEL_ID;
const char* writeAPIKey = "YOUR_WRITE_API_KEY";

WiFiClient client;

// Pin configuration
#define MQ135_PIN 34
#define DHT_PIN 4
#define DHT_TYPE DHT22

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Alert threshold
int airQualityThreshold = 2000;

void setup() {
  Serial.begin(115200);

  dht.begin();

  Wire.begin(21, 22);   // SDA = GPIO21, SCL = GPIO22

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED display not found");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("IoT Air Monitor");
  display.println("Connecting WiFi...");
  display.display();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");

  ThingSpeak.begin(client);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi Connected");
  display.println(WiFi.localIP());
  display.display();

  delay(2000);
}

void loop() {
  int mq135Value = analogRead(MQ135_PIN);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT22 sensor error");
    displayError("DHT22 Error");
    delay(2000);
    return;
  }

  String airStatus;

  if (mq135Value < 1000) {
    airStatus = "Good";
  } else if (mq135Value < 2000) {
    airStatus = "Moderate";
  } else {
    airStatus = "Poor";
  }

  Serial.println("----- Sensor Readings -----");
  Serial.print("MQ135 Value: ");
  Serial.println(mq135Value);
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Air Status: ");
  Serial.println(airStatus);

  displayData(mq135Value, temperature, humidity, airStatus);

  ThingSpeak.setField(1, mq135Value);
  ThingSpeak.setField(2, temperature);
  ThingSpeak.setField(3, humidity);

  int response = ThingSpeak.writeFields(channelID, writeAPIKey);

  if (response == 200) {
    Serial.println("Data uploaded to cloud");
  } else {
    Serial.print("Cloud upload failed. Error: ");
    Serial.println(response);
  }

  delay(15000); // ThingSpeak needs minimum 15 seconds delay
}

void displayData(int airValue, float temp, float hum, String status) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Air Quality Monitor");

  display.setCursor(0, 15);
  display.print("Air: ");
  display.print(airValue);

  display.setCursor(0, 27);
  display.print("Status: ");
  display.print(status);

  display.setCursor(0, 39);
  display.print("Temp: ");
  display.print(temp);
  display.print(" C");

  display.setCursor(0, 51);
  display.print("Humidity: ");
  display.print(hum);
  display.print(" %");

  display.display();
}

void displayError(String message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Sensor Error");
  display.println(message);
  display.display();
}
