# Alexa_esp32_demo
Alexa demo using Wemos D1 R32 board.

Based on fauxmoesp and AsyncTCP libraries.  
https://bitbucket.org/xoseperez/fauxmoesp  
https://github.com/me-no-dev/AsyncTCP

1) Install arduino environement for ESP32 boards:  
(Retrieve esp32 using Board manager, choice ESP32 Dev module)  
https://dl.espressif.com/dl/package_esp32_index.json

2) Download ZIP libraries for async tcp and fauxmoesp.  
3) Load this .INO source file into Arduino environement.  
4) Modify WIFI_SSID and WIFI_PASS to connect to your personnal wifi router.  
5) Include ZIP libraries.  
Sketch->Include ZIP library  
6) Open Serial monitor to have debug information.  
7) Compile and Upload to Wemos D1 R32 or ESPduino32 board : Board should connect to your wifi router.  
8) First time: Ask Alexa : "Find connected devices"  
9) Test:  Ask Alexa : "Turn on led", "Turn off led", "Turn on flash", "Turn off flash" : Built-in led should change ...



