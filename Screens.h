#pragma once

#include "Enums.h"

void clear_screen()
{
  tft.fillScreen(TFT_BLACK);
}

void init_tft()
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
  Weekday weekday, Month month, uint8_t monthday
) {
  clear_screen();

  // --- Draw time HH:MM ---
  uint8_t time_char_size = 7;
  tft.setTextSize(time_char_size);
  tft.setTextColor(TFT_CYAN);

  // Format the time string
  char timeStr[6];
  sprintf(timeStr, "%02d:%02d", hour, minute);

  // Approximate character width: 6 pixels per character at size 1
  // Multiply by text size to scale
  int16_t timeWidth = 6 * time_char_size * strlen(timeStr);
  int16_t x_time = (tft.width() - timeWidth) / 2;
  int16_t y_time = 70; // vertical position
  tft.setCursor(x_time, y_time);
  tft.print(timeStr);

  // --- Draw date ---
  uint8_t date_char_size = 3;
  tft.setTextSize(date_char_size);
  tft.setTextColor(TFT_YELLOW);

  // Format date string: "Wed, Aug 21"
  char dateStr[20];
  sprintf(dateStr, "%s, %s %d", WeekdayStrings[weekday], MonthStrings[month], monthday);

  int16_t dateWidth = 6 * date_char_size * strlen(dateStr); // 6 pixels per char at size 1
  int16_t x_date = (tft.width() - dateWidth) / 2;
  int16_t y_date = y_time + time_char_size * 8 + 10; // x*8 = approx height of size x font, plus 10 px spacing
  tft.setCursor(x_date, y_date);
  tft.print(dateStr);
}

/**
 * Draw the weather screen which shows weather statistics
 * Note: temp is in celsius, precipitation in mm, humidity in percentage, wind in km/h, and uv index is an integer
 */
void draw_weather_screen(
  uint8_t temp_curr_c, uint8_t temp_max_c,
  uint8_t precipitation_curr_mm, uint8_t precipitation_max_mm,
  uint8_t humidity_curr_pc, uint8_t humidity_max_pc,
  uint8_t wind_curr_kmph, uint8_t wind_max_kmph,
  uint8_t uv_index_curr, uint8_t uv_index_max
)
{

}
