#include <TFT_eSPI.h>
#include <SPI.h>

// TODO: make the draw_x_screen functions not take arguments. They can just use the global variables from Data.h directly
TFT_eSPI tft = TFT_eSPI();

#include "Enums.h"
#include "Screens.h"
#include "RTC.h"
#include "Data.h"
#include "PushBtn.h"
#include "UnitSystem.h"

#define TIME_UPDATE_DELAY_MS 5000 // Update date/time every 5 seconds
#define RTC_UPDATE_DELAY_MS 27600000 // 45 minutes in ms
#define LONG_BTN_PRESS_DURATION_MS 5000
#define TIME_BEFORE_HOME_SCREEN_IS_SHOWN_AGAIN_MS 30000 // The other screens can only be shown for a max of 30 seconds before switching back to the home screen

void setup()
{
  Serial.begin(9600);
  Serial.println("\n\n-------------------\n");
  init_tft();
  init_rtc(); // Make sure to call this function once per hour
  init_pushbtn();
  update_data();
  draw_home_screen(curr_time, curr_date.weekday, curr_date.month, curr_date.day);
}

int32_t time_home_screen_was_last_seen = -1; // -1 for when the home screen is currently being shown

Screen active_screen = HomeScreen;
void CycleDisplayScreen()
{
  // 
  if (active_screen == HomeScreen)
  {
    active_screen = WeatherScreen;
    draw_weather_screen(weather_overview, temperature_curr_c, temperature_max_c, humidity_curr_pc, humidity_max_pc, wind_speed_curr_kmh, wind_speed_max_kmh, uv_index_curr, uv_index_max, cloudiness_curr_pc, cloudiness_max_pc, precipitation_chances_curr_pc, precipitation_chances_max_pc, precipitation_amount_curr_mm, precipitation_amount_max_mm);
    time_home_screen_was_last_seen = millis();
  }
  else if (active_screen == WeatherScreen)
  {
    active_screen = DayMoonScreen;
    draw_daymoon_screen(sunrise, sunset, day_length, next_solstice, moon_phase, days_to_next_full_moon, current_day, current_week, isLeapYear(curr_date.year));    
    // Start a timer so that the clock will automatically move back to the home screen if the user doesn't press the btn to go back
    // Home screen is the default so it should always be shown when the user is not actively looking at the other two screens
    time_home_screen_was_last_seen = millis();
  }
  else if (active_screen == DayMoonScreen)
  {
    active_screen = HomeScreen;
    draw_home_screen(curr_time, curr_date.weekday, curr_date.month, curr_date.day);
    // Start a timer so that the clock will automatically move back to the home screen if the user doesn't press the btn to go back
    // Home screen is the default so it should always be shown when the user is not actively looking at the other two screens
    time_home_screen_was_last_seen = -1;
  }
}

uint32_t last_time_update = millis();
uint32_t last_rtc_update = millis();
bool recently_updated_data = true;

void loop()
{
  // --------------------
  // HANDLE SCREEN TOGGLE
  // --------------------
  if (btn_is_pressed())
  {
    // Wait for press to finish
    // Time the button press -- if the press is short, then toggle the screen.
    // if it is long, then toggle the display units metric/imperial
    uint32_t btn_press_start = millis();
    while (btn_is_pressed() && millis() - btn_press_start < LONG_BTN_PRESS_DURATION_MS);
    
    // Long press
    if (millis() - btn_press_start >= LONG_BTN_PRESS_DURATION_MS)
    {
      // Toggle the units then go to home screen
      ToggleUnits();

      // Notify user that the units changed
      draw_units_changed_screen();
      delay(5000);

      // Reset to the home screen
      active_screen = HomeScreen;
      draw_home_screen(curr_time, curr_date.weekday, curr_date.month, curr_date.day);
    }
    // Short press
    else
    {
      CycleDisplayScreen();
    }
  }

  // Move back to home screen after 30 seconds
  if (active_screen != HomeScreen && millis() - time_home_screen_was_last_seen >= TIME_BEFORE_HOME_SCREEN_IS_SHOWN_AGAIN_MS)
  {
    active_screen = HomeScreen;
    time_home_screen_was_last_seen = -1;
    draw_home_screen(curr_time, curr_date.weekday, curr_date.month, curr_date.day);
  }

  // -----------------------------
  // HANDLE DATA / DISPLAY UPDATES
  // -----------------------------

  uint32_t curr_ms = millis();

  // UPDATE THE TIME EVERY 5 SECONDS
  if (curr_ms - last_time_update > TIME_UPDATE_DELAY_MS)
  {
    uint8_t minute_before_update = curr_time.substring(curr_time.length() - 2).toInt();  
    update_date_and_time();
    uint8_t minute_after_update = curr_time.substring(curr_time.length() - 2).toInt();  
    last_time_update = curr_ms;

    // Refresh the home screen if necessary
    if (active_screen == HomeScreen && minute_before_update != minute_after_update)
    {
      draw_home_screen(curr_time, curr_date.weekday, curr_date.month, curr_date.day);
    }
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
}
