#include "Adafruit_TinyUSB.h"

// USB WebUSB object
Adafruit_USBD_WebUSB usb_web;

// Landing Page: scheme (0: http, 1: https), url
WEBUSB_URL_DEF(landingPage, 1 /*https*/, "file:///C:/Users/maxhu/OneDrive/Documents/GitHub/PHYS_S-12/11_AP/webUSB/index.html");

int reading;

void setup() {
  usb_web.setLandingPage(&landingPage);
  usb_web.begin();

  pinMode(A0, OUTPUT);
  pinMode(A4, OUTPUT);

  digitalWrite(A0, LOW);
  digitalWrite(A4, HIGH);


  Serial.begin(115200);

  // wait until device mounted
  while ( !USBDevice.mounted() ) delay(1);

  Serial.println("p5 WebUSB Serial example");
}

void loop() {

  reading = avg();
  Serial.println(reading);
  usb_web.println(reading);
  delay(2);

}

int avg() {

  long total;

  for (int i = 0; i < 100; i++) {

    total += analogRead(A2);

  }

  Serial.println(total); //KEEP IN

  total /= 100;

  return total;

}
