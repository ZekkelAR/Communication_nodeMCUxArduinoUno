#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial NodeMCU (D2, D1);

#define relay1 D0
#define relay2 D3
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "Your firebase host"
#define FIREBASE_AUTH "Your firebase auth"
#define WIFI_SSID "wifi ssid"
#define WIFI_PASSWORD "password wifi"
int fireStatus = 0;



void setup() {
  Serial.begin(9600);
  NodeMCU.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Connect to Firebase account
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println("Firebase COnnected");
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

}

void loop() {
  while (NodeMCU.available() > 0) {
    float val = NodeMCU.parseFloat();
    if (NodeMCU.read() == '\n') {
      int f = (val);
      if(f>=15){
         
      }else{
        Firebase.setString("/DATA/SENSOR_PH", String(val)); 
        Serial.println(val);
        if(val<7){
        digitalWrite(relay1, LOW);
        digitalWrite(relay2, HIGH);
        }
        else if(val>=9){
          digitalWrite(relay2, LOW);
          digitalWrite(relay1, HIGH);
        }
        else{
          digitalWrite(relay2, HIGH);
          digitalWrite(relay1, HIGH);
        }
      }
      
    }
    else{
      Serial.println(val);      
      //Serial.println("no data");
    }
  }

}
