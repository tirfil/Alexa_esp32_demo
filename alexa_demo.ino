#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include <fauxmoESP.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

#define WIFI_SSID "MY-SSID"
#define WIFI_PASS "MY-WIFIPASS"

#define ID_NAME_1 "led"
#define ID_NAME_2 "flash"

#define SERIAL_BAUDRATE 115200
#define PERIOD 1000

fauxmoESP fauxmo;
bool flash;
int flash_info;
unsigned long now = 0;

// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------
 
void wifiSetup() {
 
    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);
 
    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
 
    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();
 
    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setup() {

    Serial.begin(SERIAL_BAUDRATE);

    flash = false;
    flash_info = LOW;

    pinMode(LED_BUILTIN, OUTPUT);

    //... connect to wifi ...
    wifiSetup();

    fauxmo.addDevice(ID_NAME_1);
    fauxmo.addDevice(ID_NAME_2);

    fauxmo.setPort(80); // required for gen3 devices
    fauxmo.enable(true);

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
        if (strcmp(device_name, ID_NAME_1) == 0)
        {
            digitalWrite(LED_BUILTIN, state ? HIGH : LOW);
            flash = false;
        } else if (strcmp(device_name, ID_NAME_2) == 0)
        {
           flash = state;
           flash_info = LOW;
           digitalWrite(LED_BUILTIN,LOW);
        }
    });

}

void loop() {
    fauxmo.handle();
    // flash ?
    if (flash == true) {
      if(millis() > now + PERIOD){
          now = millis();
          flash_info = flash_info ? LOW : HIGH;
          digitalWrite(LED_BUILTIN, flash_info);
      }
    }
}
