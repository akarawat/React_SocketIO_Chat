/*
   Recieve Data from SocketIO GCP server
   Target for control I/O
   Akarawat.Pa
   9-24-19  Initial
*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SocketIoClient.h>
#define USE_SERIAL Serial

#include <Servo.h>
Servo myservo;

ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

void event(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);

  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, payload, length);
  if (error) {
    USE_SERIAL.println(error.c_str());
    return;
  }
  JsonObject obj = doc.as<JsonObject>();
  String _pulse = obj["pulse"];
  USE_SERIAL.println(_pulse);
  int pos;
  int degre = _pulse.toInt();
  
  if (degre == 0) {
    USE_SERIAL.println("Servo Stop");
    myservo.attach(2);
    int lstpos = myservo.read();
    if (lstpos > 0) {
      for (pos = lstpos; pos >= 0; pos -= 1) {
        myservo.write(pos);
        USE_SERIAL.println(pos);
        delay(15);
      }
    }
    myservo.detach();
  } else if (degre > 0 and degre <= 180) {
    USE_SERIAL.println("Servo Start");
    myservo.attach(2);
    for (pos = 0; pos <= degre; pos += 1) {
      myservo.write(pos);
      USE_SERIAL.println(pos);
      delay(15);
    }
    myservo.detach();
  }
  
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

  webSocket.on("pulse", event);
  webSocket.begin("34.87.86.224", 3002);

}

void loop() {
  webSocket.loop();
}
