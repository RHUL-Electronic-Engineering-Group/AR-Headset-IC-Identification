# **ARIC** - An Augmented Reality Solution for IC Identification

  Headset model view           |  Headset wiring
:-------------------------:|:-------------------------:
![](https://raw.githubusercontent.com/RHUL-Electronic-Engineering-Group/AR-Headset-IC-Identification/main/Images/Demo1.jpg)  |  ![](https://raw.githubusercontent.com/RHUL-Electronic-Engineering-Group/AR-Headset-IC-Identification/main/Images/Demo.jpg)

## Hardware 

* AR heads up display made for Phones (custom or off the shelf)  
* ESP32-s  
* Raspberry Pi Zero W
* 2x SPI IPS display 240x240 ST7789  
* Rechargeable LiPo battery (3000mAh+) or battery pack
* Custom PCB for 2 displays
* ESP and battery housing  
* Raspberry Pi IC isolation chamber
## Dependancies 

### ESP32

* Adafruit_ST7789
* Adafruit_I2CDevice
* Adafruit_GFX
* SPI
* EspMQTTClient

**We use the open MQTT server "test.mosquitto.org".** 

**Install custom board package: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json**  
File > Preferences > Additional Board Manager URLs  

**Install board files:**  
Tools > Board > Boards Manager > ESP32 by Espressif Systems  

**Select ESP32 AI thinker:**  
Tools > Board > ESP32-WROOM

_SOMETIMES THE BOARD WILL HANG ON DONE UPLOADING: When you see the “Done uploading” message press the RST button_

### Raspberry Pi

* CSV
* Paho MQTT
* GCLOUD/Google AI access



