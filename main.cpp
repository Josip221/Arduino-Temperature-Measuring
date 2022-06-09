#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#include <time.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
//#include "Adafruit_BME680.h"
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

//fix this later
#define WIFI_SSID "WemosD1"
#define WIFI_PASSWORD "123456789"
#define API_KEY "AIzaSyD-d6NBZprdkXabaFzRbMXyyoLaDK263Kg"
#define DATABASE_URL "https://wemos-firebase-demo-default-rtdb.europe-west1.firebasedatabase.app/" 

// #define BME_SCK 13
// #define BME_MISO 12
// #define BME_MOSI 11
// #define BME_CS 10

//Adafruit_BME680 bme;
Adafruit_BME280 bme;

//Adafruit_BME280 bme(BME_CS); // hardware SPI
// Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

bool signupOK = false;
bool measureStatus = 0;

bool readMeasureStatus();
void initWiFi();
void sendData(String path, float value);


void setup(){
  Serial.begin(115200);
  initWiFi();
  //initBME();

  bme.begin(0x76);
}

void loop(){
  if(readMeasureStatus()){
    time_t timeStamp = time(0);
    json.add("temperature", bme.readTemperature());
    json.add("humidity", bme.readHumidity());
    json.add("pressure", bme.readPressure());
    json.add("timeStamp", timeStamp);
    Serial.print(timeStamp);
    delay(50);
    if(Firebase.ready() && signupOK){
      Firebase.RTDB.pushJSON(&fbdo, "measure", &json);
      Firebase.RTDB.setInt(&fbdo, "measureStatus", 0);
    }
  }
  delay(1000);
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

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

bool readMeasureStatus() {
  Firebase.RTDB.getInt(&fbdo, "measureStatus");
  if(fbdo.to<int>() == 1){
    return 1;
  }
  return 0;
}
  
// int initBME(){
//   bme.setTemperatureOversampling(BME680_OS_8X);
//   bme.setHumidityOversampling(BME680_OS_2X);
//   bme.setPressureOversampling(BME680_OS_4X);
//   // bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
//   // bme.setGasHeater(320, 150); // 320*C for 150 ms
//   return 0;
// }

