#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_I2CDevice.h>
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library
#include "EspMQTTClient.h"

#define TFT_MOSI 14  // SDA Pin on ESP32
#define TFT_SCLK 25  // SCL Pin on ESP32
#define TFT_CS   26  // Chip select control pin
#define TFT_DC   33  // Data Command control pin
#define TFT_RST  27 // Reset pin (could connect to RST pin)

String message="Start";
String old_message="Start";
String Cat_Message="";
int message_count=0;


EspMQTTClient client(
  "JasonHotspot",
  "jason12345",
  "test.mosquitto.org",  // MQTT Broker server ip
  "",   // Can be omitted if not needed
  "",   // Can be omitted if not needed
  "ESP32-Headset-Demo-Immersive",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
//Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD); 
/****************************** Feeds ***************************************/ 
// Code for LCD code
 
float p = 3.1415926;
 
//void MQTT_connect(); 
void setup(void) {

  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
  Serial.begin(115200);
  pinMode(21, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  digitalWrite(21, HIGH);
  digitalWrite(19, HIGH);
  digitalWrite(18, LOW);
  tft.setTextSize(1);
  tft.setTextWrap(true);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_RED);
  tft.setCursor(0, 30);
  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 240x240 pixel
  tft.setRotation(2);
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  client.subscribe("immersive_headset_demo", [](const String & topic, const String & payload) {
    Serial.println(payload);  // Print the message to the Serial monitor
    Serial.println("message set to payload");
    message = payload;
    Serial.println(message);
  });
}

void tftrefresh(void){
  tft.setTextWrap(true);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_RED);
  tft.setCursor(0, 30);
  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 240x240 pixel
  tft.setRotation(2);
}


void loop() {
  if (message == old_message){
    client.loop();  
  }
  else{
    message_count++;
    Cat_Message= Cat_Message + message;
    if(message_count==3){
      old_message = message;
      tftrefresh();
      Serial.println(Cat_Message);
      tft.print(Cat_Message);
      message_count=0;
      Cat_Message="";
    }
  } 
}
