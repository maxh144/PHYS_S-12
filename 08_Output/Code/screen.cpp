#include "screen.h"

screen::screen(int theInterval) {

  interval = theInterval;

}
void screen::init() {

  tft.init(135, 240);           // Init ST7789 240x135
  tft.setRotation(1);

  tft.setTextWrap(false);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(4);


}



void screen::update(double cm, double v, double s, double m) {

  int state = button.getState();

  if (state != currentState) {

    updateScreen(state);

  }

  if (updateTime()) {

    updateVals(state, cm, v, s, m);
    currentState = state;
    
  }

}



void screen::testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.print(text);
}

void screen::testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6) {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color2);
  }
}

void screen::testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for (t = 0 ; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0 ; i <= 16; i += 1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}



void screen::updateScreen(int state) {



  if (state == 0) {

    tft.fillScreen(ST77XX_BLACK);

    tft.fillRect(tft.width() / 2 - 5, 0, 10, tft.height(), ST77XX_RED);
    tft.fillRect(0, tft.height() / 2 - 5, tft.width(), 10, ST77XX_RED);

    tft.setTextSize(2);

    tft.setCursor(tft.width() / 2 - 35, tft.height() / 2 - 25);
    tft.print("cm");

    tft.setCursor(tft.width() - 15, tft.height() / 2 - 25);
    tft.print("V");

    tft.setCursor(tft.width() - 15, tft.height() - 20);
    tft.print("m");

    tft.setCursor(tft.width() / 2 - 45, tft.height() - 20);
    tft.print("m/s");

  }
  else {

    tft.fillScreen(ST77XX_RED);
    tft.fillRect(5, 5, tft.width() - 10, tft.height() - 10, ST77XX_BLACK);

    tft.setCursor(tft.width() - 70, tft.height() - 50);
    tft.setTextSize(4);

    switch (state) {

      case 1:
        tft.setCursor(tft.width() - 70, tft.height() - 50);
        tft.print(" m");
        break;
      case 2:
        tft.setCursor(tft.width() - 40, tft.height() - 50);
        tft.print("V");
        break;
      case 3:
        tft.setCursor(tft.width() - 80, tft.height() - 50);
        tft.print("m/s");
        break;
      case 4:
        tft.setCursor(tft.width() - 40, tft.height() - 50);
        tft.print("m");
        break;
    }

  }

}
void screen::updateVals(int state, double cm, double v, double s, double m) {

  if (state == 0) {

    tft.setTextSize(4);

    tft.setCursor(10, 10);
    tft.print(cm);

    tft.setCursor(tft.width() / 2 + 15, 10);
    tft.print(v);

    tft.setCursor(10, tft.height() / 2 + 15);
    tft.print(s);

    tft.setCursor(tft.width() / 2 + 15, tft.height() / 2 + 15);
    tft.print(m);

  }
  else {

    tft.setTextSize(8);
    tft.setCursor(20, 20);

    switch (state) {
      case 1:
        tft.print(cm);
        break;
      case 2:
        tft.print(v);
        break;
      case 3:
        tft.print(s);
        break;
      case 4:
        tft.print(m);
        break;
    }
  }

  }

  boolean screen::updateTime() {

    unsigned long time = millis();

    if (time - lastUpdate > interval) {

      lastUpdate = time;
      return true;

    }
    else {
      return false;
    }

}
