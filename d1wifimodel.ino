#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

// #define ARDUINO_INPUT D2

int ARDUINO_INPUT = 4;


ESP8266WiFiMulti WiFiMulti;


const char* ssid = "RESNET-GUEST-DEVICE"; // Replace with your Wi-Fi network SSID
const char* password = "ResnetConnect"; // Replace with your Wi-Fi network password
const char* webhooksURL = "http://maker.ifttt.com/trigger/breathalyzer_activated/with/key/nKLXNaMKdLzjFnjJksXepbWaGnC_Ae-yMQ6rc83vnQV"; // Replace with your Webhooks URL


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ARDUINO_INPUT, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
 
  Serial.println();
  Serial.println();
  Serial.println();


  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }


  WiFi.mode(WIFI_STA);
  // WiFiMulti.addAP(ssid);
  WiFiMulti.addAP(ssid, password);


}


void loop() {
    // watch out for emergency contact


    byte input = digitalRead(ARDUINO_INPUT);
    Serial.print("Arduino input: ");
    Serial.println(input);
    if (input == 1) {
      Serial.println("Contacting emergency contact");
      Serial.println("Making sure connected to wifi");
      if ((WiFiMulti.run() == WL_CONNECTED)) {


        WiFiClient client;


        HTTPClient http;


        Serial.println("[HTTP] begin...\n");


        if (http.begin(client, webhooksURL)) {  // HTTP
          Serial.print("[HTTP] POST...\n");
          // start connection and send HTTP header
          int httpCode = http.POST("");


          // httpCode will be negative on error
          if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] POST... code: %d\n", httpCode);


            // file found at server
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();
            Serial.println(payload);
            }


            while (1) {} // exit
          } else {
            Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }


          http.end();
        } else {
          Serial.println("[HTTP] Unable to connect");
        }
      }
    }
 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}


