#pragma once

#include "Enums.h"

void clear_screen()
{
  tft.fillScreen(TFT_BLACK);
}

void init_home_screen()
{
  tft.init();
  tft.setRotation(1); // Landscape
  clear_screen();
}

/**
 * Draw the home screen -- show the time and date
 * @param monthday The day of the month. 18th, 5th, 31st, etc.
 */
void draw_home_screen(
  uint8_t hour, uint8_t minute,
  Weekday weekday, Month month, uint8_t monthday,
  
)