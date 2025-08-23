#pragma once

#include "Enums.h"

// Approximate character size: 5x8 pixels per character at size 1
#define charsize_w 6
#define charsize_h 8

#define PRIMARY TFT_YELLOW
#define SECONDARY TFT_CYAN

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
  tft.setTextColor(PRIMARY);

  // Format the time string
  char timeStr[6];
  sprintf(timeStr, "%02d:%02d", hour, minute);

  // Multiply by text size to scale
  int16_t timeWidth = charsize_w * time_char_size * strlen(timeStr);
  int16_t x_time = (tft.width() - timeWidth) / 2;
  int16_t y_time = 70; // vertical position
  tft.setCursor(x_time, y_time);
  tft.print(timeStr);

  // --- Draw date ---
  uint8_t date_char_size = 3;
  tft.setTextSize(date_char_size);
  tft.setTextColor(SECONDARY);

  // Format date string: "Wed, Aug 21"
  char dateStr[20];
  sprintf(dateStr, "%s, %s %d", WeekdayStrings[weekday], MonthStrings[month], monthday);

  int16_t dateWidth = charsize_w * date_char_size * strlen(dateStr);
  int16_t x_date = (tft.width() - dateWidth) / 2;
  int16_t y_date = y_time + time_char_size * charsize_h + 10; // x*8 = approx height of size x font, plus 10 px spacing
  tft.setCursor(x_date, y_date);
  tft.print(dateStr);
}

/**
 * Draw the weather screen which shows weather statistics
 * Note: temp is in celsius, humidity in percentage, wind in km/h, and uv index is an integer 0-15, precipitation in mm and percentage
 */
void draw_weather_screen(
  WeatherOverview weather_overview,
  int8_t temp_curr_c, int8_t temp_max_c,
  uint8_t humidity_curr_pc, uint8_t humidity_max_pc,
  uint8_t wind_curr_kmph, uint8_t wind_max_kmph,
  uint8_t uv_index_curr, uint8_t uv_index_max,
  uint8_t cloudiness_curr_pc, uint8_t cloudiness_max_pc,
  uint8_t precipitation_curr_pc, uint8_t precipitation_max_pc,
  float precipitation_curr_mm, float precipitation_max_mm
)
{
  clear_screen();
  uint8_t text_size = 2;
  tft.setTextSize(text_size);
  tft.setTextColor(SECONDARY);

  // Format strings
  char temp_str[50];
  sprintf(temp_str, "%dC / %dC", temp_curr_c, temp_max_c);
  char humidity_str[50];
  sprintf(humidity_str, "   %d%% / %d%%", humidity_curr_pc, humidity_max_pc);
  char wind_str[50];
  sprintf(wind_str, "       %dkmh / %dkmh", wind_curr_kmph, wind_max_kmph);
  char uv_index_str[50];
  sprintf(uv_index_str, "   %d / %d", uv_index_curr, uv_index_max);
  char cloudiness_str[50];
  sprintf(cloudiness_str, " %d%% / %d%%", cloudiness_curr_pc, cloudiness_max_pc);
  char precipitation_pc_str[50];
  sprintf(precipitation_pc_str, "    %d%% / %d%%", precipitation_curr_pc, precipitation_max_pc);
  char precipitation_mm_str[50];
  sprintf(precipitation_mm_str, "    %.2fmm / %.2fmm", precipitation_curr_mm, precipitation_max_mm);

  // Positioning
  uint8_t left_margin = 10;
  uint8_t top_margin = 10;
  auto newline = [left_margin, &top_margin, text_size]() -> void { top_margin += text_size * charsize_h + 10; tft.setCursor(left_margin, top_margin); }; // move to next line
  tft.setCursor(left_margin, top_margin);

  // Position the values
  tft.setTextColor(SECONDARY);
  tft.setTextSize(3); // weather overview is a little bit larger
  tft.print("Currently ");
  tft.setTextColor(PRIMARY);
  tft.print(WeatherStrings[weather_overview]);
  top_margin += 3 * charsize_h + 10;
  tft.setCursor(left_margin, top_margin);

  tft.setTextSize(text_size); // back to 2
  // top_margin += 16;
  // tft.setCursor(left_margin, top_margin);
  tft.setTextColor(SECONDARY);
  tft.print("Temperature: ");
  tft.setTextColor(PRIMARY);
  tft.print(temp_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Humidity: ");
  tft.setTextColor(PRIMARY);
  tft.print(humidity_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Wind: ");
  tft.setTextColor(PRIMARY);
  tft.print(wind_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("UV index: ");
  tft.setTextColor(PRIMARY);
  tft.print(uv_index_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Cloudiness: ");
  tft.setTextColor(PRIMARY);
  tft.print(cloudiness_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Precipitation:");
  newline();
  tft.setTextColor(PRIMARY);
  tft.print(precipitation_pc_str);
  newline();
  tft.print(precipitation_mm_str);
}

void draw_daymoon_screen(
  String sunrise_time_str,
  String sunset_time_str,
  String day_length_str,
  uint8_t days_until_solstice,
  MoonPhase current_moon_phase,
  uint8_t days_to_next_full_moon,
  uint16_t day_of_the_year,
  uint8_t week_of_the_year,
  bool is_leap_year
)
{
  clear_screen();
  uint8_t text_size = 2;
  tft.setTextSize(text_size);
  tft.setTextColor(SECONDARY);

  // Generate display strings
  char days_until_solstice_str[50];
  sprintf(days_until_solstice_str, "%d days", days_until_solstice);
  char days_to_full_moon_str[50];
  sprintf(days_to_full_moon_str, "%d days", days_to_next_full_moon);
  char day_of_the_year_str[50];
  if (is_leap_year)
    sprintf(day_of_the_year_str, "%d / 366", day_of_the_year);
  else
    sprintf(day_of_the_year_str, "%d / 365", day_of_the_year);
  char week_of_the_year_str[50];
  sprintf(week_of_the_year_str, "%d / 52", week_of_the_year);

  // Positioning
  uint8_t left_margin = 10;
  uint8_t top_margin = 10;
  auto newline = [left_margin, &top_margin, text_size]() -> void { top_margin += text_size * charsize_h + 10; tft.setCursor(left_margin, top_margin); }; // move to next line
  tft.setCursor(left_margin, top_margin);

  // Write values
  tft.setTextColor(SECONDARY);
  tft.print("Sunrise: ");
  tft.setTextColor(PRIMARY);
  tft.print(sunrise_time_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Sunset: ");
  tft.setTextColor(PRIMARY);
  tft.print(sunset_time_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Day length: ");
  tft.setTextColor(PRIMARY);
  tft.print(day_length_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Next solstice: ");
  tft.setTextColor(PRIMARY);
  tft.print(days_until_solstice_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Moon: ");
  tft.setTextColor(PRIMARY);
  tft.print(MoonPhaseStrings[current_moon_phase]);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Next full moon: ");
  tft.setTextColor(PRIMARY);
  tft.print(days_to_full_moon_str);
  newline();
  
  tft.setTextColor(SECONDARY);
  tft.print("Current day: ");
  tft.setTextColor(PRIMARY);
  tft.print(day_of_the_year_str);
  newline();

  tft.setTextColor(SECONDARY);
  tft.print("Current week: ");
  tft.setTextColor(PRIMARY);
  tft.print(week_of_the_year_str);
  newline();
}

void ShowWifiFailureScreen()
{
  clear_screen();
  uint8_t text_size = 2;
  tft.setTextSize(text_size);
  tft.setTextColor(PRIMARY);
  tft.print("Failed to conenct to wifi");
  delay(90000000); // permanently blocking
}

void ShowGetFailureScreen(int code)
{
  clear_screen();
  uint8_t text_size = 2;
  tft.setTextSize(text_size);
  tft.setTextColor(PRIMARY);
  tft.print("GET req failure: ");
  tft.print(code);
  delay(90000000); // permanently blocking
}