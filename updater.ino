#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define cSERIAL Serial

ESP8266WiFiMulti WiFiMulti;
const char* fingerprint = "YOUR SITE CERT FINGERPRINT";

void setup() {
  cSERIAL.begin(115200);
  for (uint8_t t = 4; t > 0; t--) {
    cSERIAL.printf("[SETUP] WAIT %d...\n", t);
    cSERIAL.flush();
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("YOURSSID", "PASSWORD");
}

void loop() {
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    HTTPClient http;
    cSERIAL.print("[HTTP] begin...\n");
    http.begin("https://yoursite.com/updater", fingerprint);
    http.addHeader("Content-Type", "text/plain");
    cSERIAL.print("[HTTP] POST...\n");
    int httpCode = http.POST("deviceId=NODEMCU");
    http.end();
  }
  cSERIAL.print("[WAIT] Wait a minute...\n");
  delay(1000);
  cSERIAL.print("[WAIT] ... literally!\n");
  delay(59000);
}
