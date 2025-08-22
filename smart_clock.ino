#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

#include "Enums.h"
#include "Screens.h"

#define switch_delay 7500

void setup()
{
  init_tft();
}

void loop()
{
  draw_home_screen(15, 5, Tuesday, April, 19);
  delay(switch_delay);
  draw_weather_screen(Rainy, 19, 25, 40, 60, 5, 10, 7, 8, 60, 100, 1.15, 3.25);
  delay(switch_delay);
  draw_daymoon_screen(5, 34, 7, 15, 13, 41, 72, WaxingGibbous, 5, 261, 34);
  delay(switch_delay);
}
