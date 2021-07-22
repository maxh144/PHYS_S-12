#include "esp_camera.h"
#include <WiFi.h>

//
// WARNING!!! Make sure that you have either selected ESP32 Wrover Module,
//            or another board which has PSRAM enabled
//

const char* ssid = "ESP32-CAM Access Point";
const char* password = "123456789";

void startCameraServer();
void setupFunc(); //Cleans up Code

void setup() {
  Serial.begin(115200);
  Serial.println();

  setupFunc();

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  startCameraServer();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10000);
}

int test() { // function used for JSON

  return random(100);

}
