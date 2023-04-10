#include <SoftwareSerial.h>
#include <FirebaseESP8266.h>
#include <DHT.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "https://iot-dt3-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "TpDdtrH4cX2UADvMvaqwoCEwbwEblix9yO7OYOxz"

#define WIFI_SSID "ssid" 
#define WIFI_PASSWORD "pass" 
 

FirebaseData fbdo;
SoftwareSerial loraSerial(3, 1); // RX, TX

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  delay(1000);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Dang ket noi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
   Serial.println ("");
  Serial.println ("Da ket noi WiFi!");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  if (loraSerial.available()) {
    String data = loraSerial.readStringUntil('\n');
    float t = data.substring(0, data.indexOf(',')).toFloat();
    float h = data.substring(data.indexOf(',') + 1).toFloat();
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println(" %");
    
    Firebase.setFloat( fbdo,"Nhiet do", t);
    Firebase.setFloat ( fbdo,"Do am", h);
    delay(200);

  }
}
