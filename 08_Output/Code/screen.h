
#ifndef SCREEN_H
#define SCREEN_H

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <Arduino.h>
#include "button.h"

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8
#define BUTTON_PIN     2

class screen {

  public:

    screen(int theInterval);
    void init();


    void update(double cm, double v, double s, double m);
    void testdrawtext(char *text, uint16_t color);
    void testfillrects(uint16_t color1, uint16_t color2);
    void testroundrects();

  private:

    stateButton button = stateButton(BUTTON_PIN, 5);
    Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_DC);
    int interval;
    int currentState = -1;
    unsigned long lastUpdate;
    

    void updateScreen(int state);
    void updateVals(int state, double cm, double v, double s, double m);
    boolean updateTime();



};

#endif
