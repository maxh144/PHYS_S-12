#include "esp_camera.h"
#include <WiFi.h>
#include <NMEAGPS.h>
#include <Wire.h>

#define  gpsPort Serial



static NMEAGPS gps; // GPS
gps_fix fix;

double baseLong;
double baseLat;;
double baseAlt;
double baseSpeed;


const char* ssid = "ESP32-CAM Access Point"; //CAM
const char* password = "123456789";

void startCameraServer();
void setupFunc(); //Cleans up Code

void setup() {

  gpsPort.begin(9600);
  getBaseline();


  pinMode(4, OUTPUT); //LED BUILTIN
  //digitalWrite(4, HIGH);

  setupFunc();
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  startCameraServer();

  Wire.begin(13, 12);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10000);
}



void getBaseline() {

  while (fix.satellites < 0) {
    while (!gps.available(gpsPort)) {
      yield();
    }
    fix = gps.read();
  }

  baseLat = fix.latitude();
  baseLong = fix.longitude();
  baseSpeed = fix.speed_kph();
  baseAlt = fix.altitude();

}

double getDist() {

  double longi;
  double lati;

  longi = (fix.longitude() - baseLong) * 111139;
  lati = (fix.latitude() - baseLat) * 111139 ;

  return (sqrt(longi * longi + lati * lati));


}

double getSpeed() {

  return abs(fix.speed_kph() - baseSpeed);

}

double getAlt() {

  return abs(fix.altitude() - baseAlt);

}

int numSat() {

  return fix.satellites;

}

boolean updateVals() {

  if (gps.available(gpsPort)) {

    fix = gps.read();

    return true;
  }

  return false;
}

void wireVals(unsigned int values[]) {

  unsigned int c, d;

  Wire.requestFrom(8, 4);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    
    c = Wire.read(); // receive a byte as character
    d = Wire.read(); // receive a byte as character
    values[0] = c << 8 | d;
    
    c = Wire.read(); // receive a byte as character
    d = Wire.read(); // receive a byte as character
    values[1] = c << 8 | d;

  }

}
