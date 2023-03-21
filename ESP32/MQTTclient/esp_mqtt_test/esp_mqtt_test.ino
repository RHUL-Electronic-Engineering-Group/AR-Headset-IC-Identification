#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "JasonHotspot";
const char* password =  "jason12345";
const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
int tempcount = 0;
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("immersive_headset_demo");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
//  while (!client.connected()) {
//    Serial.println("Connecting to MQTT...");
// 
//    if (client.connect("ESP32Client")) {
// 
//      client.subscribe("immersive_headset_demo");
//      
//      Serial.println("subscried to topic");  
//      Serial.println("connected");  
// 
//    } else {
// 
//      Serial.print("failed with state ");
//      Serial.print(client.state());
//      delay(2000);
// 
//    }
//  }
 
 
}
 
void loop() {
  if (!client.connected()) {
    Serial.println("reconnecting");
    reconnect();
  }
  //client.loop();


  if(tempcount<10){
    client.publish("immersive_headset_demo", "testing from esp board");
    tempcount++;
  }
}
