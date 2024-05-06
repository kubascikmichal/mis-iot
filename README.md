# Management information systems - IoT board for data measurement and sending to cloud
Measurements of temperature, humidity and lighting.

## Configuration
Configuration of device is by html page. Device is in AP_STA mode.

Need to configure:
+ STA SSID - SSID of network to connect
+ STA PASSWORD - Password of network to connect
+ Delay - Timeout of data sending
+ API key - API_KEY of thingspeak

Configuration file is saved in NVS of device. 

## Thingspeak setting

+ Field1 - temperature
+ Field2 - humidity
+ Field3 - lightning