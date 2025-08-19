#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

#include "Enums.h"
#include "Screens.h"

void setup()
{
  init_tft();
  draw_home_screen(15, 5, Tuesday, April, 19);
}

void loop()
{

}
