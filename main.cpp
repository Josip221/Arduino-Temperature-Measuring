#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Adafruit_BMP280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

WiFiClientSecure client;
HTTPClient https;

Adafruit_BMP280 bmp;

const char* host = "https://shrouded-badlands-04100.herokuapp.com";
const char* fingerprint = "346a4f3549d78bc1ea74b99ec9a8c91f5e6c2761";

int ledPin = D6;

float temperature;
int pressure;
float altitude;

void initWiFi();
void printMeasurements();
void printGoodbye();
void sendPOST();

void setup(){
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial.println("Waking up from deep sleep.");
  initWiFi();

  bool status = bmp.begin(0x76); 
  if (!status) {
    Serial.println("Could not find a valid bmp280 sensor, check wiring!");
  }
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure() / 100.0F;
  altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
  printMeasurements();
  if(WiFi.status() == WL_CONNECTED){
    sendPOST();
  }
  digitalWrite(ledPin, LOW);
  printGoodbye();
  ESP.deepSleep(600e6);
}
 
void loop(){
}

void initWiFi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void printMeasurements(){
  Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(pressure);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(altitude);
    Serial.println(" m");
}

void sendPOST(){
  client.setFingerprint(fingerprint);
    if(https.begin(client, host)){  
      https.addHeader("Content-Type", "application/json");
      int httpsCode = https.POST("{\"temperature\":\"" + String(temperature) + "\",\"altitude\":\"" + String(altitude) + "\",\"pressure\":\"" + pressure + "\"}");
      if(httpsCode > 0){
        String payload = https.getString();
        Serial.println(payload);
      }

      https.end();
    }else{
      Serial.println("Unable to connect");
    };
}

void printGoodbye(){
    Serial.print("Device was active for: ");
    Serial.print(millis() / 1000);
    Serial.println(" seconds.");
    Serial.println("Going to deep sleep.");
}
