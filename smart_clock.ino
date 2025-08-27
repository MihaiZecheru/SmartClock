#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

#include "Enums.h"
#include "Screens.h"
#include "RTC.h"
#include "Data.h"

#define SWITCH_DELAY_MS 7500
#define TIME_UPDATE_DELAY_MS 5000 // Update date/time every 5 seconds
#define RTC_UPDATE_DELAY_MS 27600000 // 45 minutes in ms
void setup()
{
  Serial.begin(9600);
  Serial.println("\n\n-------------------\n");
  init_tft();
  init_rtc(); // TODO: Make sure to call this function once per hour
  update_data();
}

uint32_t last_time_update = millis();
uint32_t last_rtc_update = millis();
bool recently_updated_data = true;

void loop()
{
  uint32_t curr_ms = millis();

  // UPDATE THE TIME EVERY 5 SECONDS
  if (curr_ms - last_time_update > TIME_UPDATE_DELAY_MS)
  {
    update_date_and_time();
    last_time_update = curr_ms;
  }

  // SYNC RTC EVERY 45m
  if (curr_ms - last_rtc_update > RTC_UPDATE_DELAY_MS)
  {
    init_rtc();
    last_rtc_update = curr_ms;
  }

  // UPDATE DATA HOURLY
  uint8_t current_minute = curr_time.substring(curr_time.length() - 2).toInt();
  if (current_minute <= 2 && !recently_updated_data)
  {
    update_data();
    recently_updated_data = true;
  }
  else if (current_minute > 2 && recently_updated_data)
  {
    recently_updated_data = false;
  }

  draw_home_screen(curr_time, curr_date.weekday, curr_date.month, curr_date.day);
  delay(SWITCH_DELAY_MS);
  draw_weather_screen(weather_overview, temperature_curr_c, temperature_max_c, humidity_curr_pc, humidity_max_pc, wind_speed_curr_kmh, wind_speed_max_kmh, uv_index_curr, uv_index_max, cloudiness_curr_pc, cloudiness_max_pc, precipitation_chances_curr_pc, precipitation_chances_max_pc, precipitation_amount_curr_mm, precipitation_amount_max_mm);
  delay(SWITCH_DELAY_MS);
  draw_daymoon_screen(sunrise, sunset, day_length, next_solstice, moon_phase, days_to_next_full_moon, current_day, current_week, isLeapYear(curr_date.year));
  delay(SWITCH_DELAY_MS);
}
