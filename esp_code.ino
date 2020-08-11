#include <HTTPClient.h>
#include <WiFi.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define DHTTYPE DHT22

const char* ssid = "8XkLM";
const char* password = "verbal83her76two";

uint8_t sensor = 16;
DHT dht(sensor, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected!");
}

void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://192.168.10.5:8090/");
    http.addHeader("Content-Type", "text/plain");

    const int cap = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<cap> doc;

    doc["temperature"] = dht.readTemperature();
    doc["humidity"] = dht.readHumidity();

    char output[256];
    serializeJsonPretty(doc, output);
    Serial.println(output);
    
    //Code will give back error after trying to POST
    int httpCode = http.POST(output);
    if(httpCode > 0) {
      Serial.println(httpCode);
    } else Serial.println("Error in Connection");
    http.end();
  }
  delay(10000);
}
