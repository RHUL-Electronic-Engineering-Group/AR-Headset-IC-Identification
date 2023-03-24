# **ARIC** - Augmented Reality for IC Identification

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

# Build environment

**ESP32** > ESP-Headset > ESP-Headset.ino -> Upload to ESP 

```C++
EspMQTTClient client(
  "****",                             // Network SSID
  "****",                             // Network Password
  "test.mosquitto.org",               // MQTT Broker server ip (we use public)
  "username",                         // Can be omitted if not needed
  "password",                         // Can be omitted if not needed
  "ESP32-Headset-Demo-Immersive",     // Client name that uniquely identify your device
  1883                                // The MQTT port, default to 1883. this line can be omitted
);
```

We modified the Adafruit_GFX library to mirror text by default for our headset. In the ADAFRUIT_ST77XX:

```C++

#define ST77XX_MADCTL_MY 0x80
#define ST77XX_MADCTL_MX 0x40
#define ST77XX_MADCTL_MV 0x20
#define ST77XX_MADCTL_ML 0x10
#define ST77XX_MADCTL_RGB 0x4B // modifed code

```

**Raspberry Pi** > Python > OcrTextSearch.py OR OcrTextSearchButton.py

```python
sudo python3 OcrTextSearch.py
```
_If you have certain ICs that are not in the IC_Library.csv - add them and include their datasheet in the same format._

