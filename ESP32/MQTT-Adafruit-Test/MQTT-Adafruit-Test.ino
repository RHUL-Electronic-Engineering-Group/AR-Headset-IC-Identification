/***************************************************
  Adafruit MQTT Library Retain Flag Example

  This example demonstrates use of the retain flag when publishing messages.
  If retain is set, the MQTT broker will store the message. When a new
  client subscribes to the topic, the retained message will be republished
  to that client. This is useful for configuration messages and 'last known
  good' values.

  Written by Ben Willmore.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <WiFi.h> // use <WiFi.h> for ESP32
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_I2CDevice.h>
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "AdamHotspot"
#define WLAN_PASS       "adam12345"

/************************* Adafruit.io Setup *********************************/

#define MQTT_SERVER "test.mosquitto.org"
#define MQTT_SERVERPORT 1883 // use 8883 for SSL
#define MQTT_USERNAME ""
#define MQTT_KEY ""
#define DEVICE_ID "ESP32-Immersive-Headset"


#define TFT_MOSI 14  // SDA Pin on ESP32
#define TFT_SCLK 25  // SCL Pin on ESP32
#define TFT_CS   26  // Chip select control pin
#define TFT_DC   33  // Data Command control pin
#define TFT_RST  27 // Reset pin (could connect to RST pin)

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

float p = 3.1415926;

/************ Global State (you don't need to change this!) ******************/

// Create a WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiClientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);

/****************************** Feeds ***************************************/

// Set up for publishing and subscribing to the same feed, for demonstration only
Adafruit_MQTT_Publish publish_feed = Adafruit_MQTT_Publish(&mqtt, DEVICE_ID "immersive_headset_demo/testpublish");
Adafruit_MQTT_Subscribe subscribe_feed = Adafruit_MQTT_Subscribe(&mqtt, DEVICE_ID "immersive_headset_demo");

/*************************** Sketch Code ************************************/

void setup() {
  Serial.begin(115200);
  delay(10);

  tft.setTextWrap(true);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  
  Serial.begin(115200);
  pinMode(21, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  digitalWrite(21, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(18, LOW);
  tft.setRotation(2);
  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 240x240 pixel
  tft.fillScreen(ST77XX_BLACK);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT broker, then publish a retained message and a
  // non-retained message.
  Serial.print("\nConnecting to MQTT broker...");
  MQTT_connect();
  Serial.println("connected");

  Serial.println("Publishing messages while not subscribed");
  publish_feed.publish("This message should be retained", true);
  publish_feed.publish("This message should not be retained");

  Serial.println("Disconnecting from MQTT broker\n");
  mqtt.disconnect();

  subscribe_feed.setCallback(subscribe_callback);
  mqtt.subscribe(&subscribe_feed);
}

void subscribe_callback(char *data, uint16_t len) {
  Serial.print("--> Message received: \"");
  Serial.print(data);
  tft.println(data);
  Serial.println("\"\n");
}

void loop() {

  // Connect to MQTT broker. We should receive the retained message only.
  Serial.println("Connecting to broker. Expect to receive retained message:");
  MQTT_connect();

  mqtt.processPackets(1000);

  Serial.println("Publishing non-retained message. Expect to receive it immediately:");
  publish_feed.publish("This message should be received immediately but not retained");

  mqtt.processPackets(1000);

  Serial.println("Publishing retained message. Expect to receive it immediately and on re-subscribing:");
  publish_feed.publish("This message should be received immediately AND retained", true);

  mqtt.processPackets(10000);

  Serial.println("Disconnecting from broker\n");
  mqtt.disconnect();

  delay(15000);
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
}
