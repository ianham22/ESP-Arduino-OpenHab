#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "BTHub5-ZG53";
const char* password = "59d49ee597";


void setup() {
 Serial.begin(9600);
 Serial.println("Booting");
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password);
 while (WiFi.waitForConnectResult() != WL_CONNECTED) {
 Serial.println("Connection Failed! Rebooting...");
 delay(5000);
 ESP.restart();
 }

// Port defaults to 8266
 // ArduinoOTA.setPort(8266);

// Hostname defaults to esp8266-[ChipID]
 // ArduinoOTA.setHostname("myesp8266");

// No authentication by default
 // ArduinoOTA.setPassword((const char *)"123");

ArduinoOTA.onStart([]() {
 Serial.println("Start");
 });
 ArduinoOTA.onEnd([]() {
 Serial.println("\nEnd");
 });
 ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
 Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
 });
 ArduinoOTA.onError([](ota_error_t error) {
 Serial.printf("Error[%u]: ", error);
 if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
 else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
 else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
 else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
 else if (error == OTA_END_ERROR) Serial.println("End Failed");
 });
 ArduinoOTA.begin();
 Serial.println("Ready");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());

 pinMode(2, OUTPUT);
}

void loop() {
 ArduinoOTA.handle();
 digitalWrite(2, HIGH); // turn the LED on (HIGH is the voltage level)
 delay(250); // wait for 2 second
 digitalWrite(2, LOW); // turn the LED off by making the voltage LOW
 delay(250);
}
