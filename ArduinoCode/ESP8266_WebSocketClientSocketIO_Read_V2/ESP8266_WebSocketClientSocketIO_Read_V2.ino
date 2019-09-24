/*
 * Recieve Data from SocketIO GCP server
 * Target for control I/O
 * Akarawat.Pa
 * 9-24-19  Initial   
*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SocketIoClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

void event(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
  
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, payload, length);
  if (error){
    USE_SERIAL.println(error.c_str());
    return;
  }
  JsonObject obj = doc.as<JsonObject>();
  String cnter = obj["count"];
  USE_SERIAL.println(cnter);
  
}

void setup() {
  USE_SERIAL.begin(115200);

  USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  WiFiMulti.addAP("Linxens_AY4", "!Linxens4");
  
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  webSocket.on("count", event);
  webSocket.begin("34.87.86.224", 3001);
  
}

void loop() {
  webSocket.loop();
}
