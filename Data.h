#ifndef DATA_H
#define DATA_H

#include "API.h"
#include "RTC.h"
#include "TimeFuncs.h"
#include "CalendarFuncs.h"

// Time data
String curr_time;
Date curr_date;
Weekday curr_weekday;

// Weather data
WeatherOverview weather_overview;
int8_t temperature_curr_c;
int8_t temperature_max_c;
uint8_t humidity_curr_pc;
uint8_t humidity_max_pc;
uint8_t wind_speed_curr_kmh;
uint8_t wind_speed_max_kmh;
float uv_index_curr;
float uv_index_max;
uint8_t cloudiness_curr_pc;
uint8_t cloudiness_max_pc;
uint8_t precipitation_chances_curr_pc;
uint8_t precipitation_chances_max_pc;
float precipitation_amount_curr_mm;
float precipitation_amount_max_mm;

// Sun/moon data
String sunrise;
String sunset;
String day_length;
uint8_t next_solstice;
MoonPhase moon_phase;
uint8_t days_to_next_full_moon;
uint16_t current_day;
uint8_t current_week;

void update_data()
{
  curr_time = get_current_time();
  curr_date = get_current_date();

  // If it's hour 0 (midnight), it's a new day so the highs will be different
  // Otherwise, the highs should be preserved because the API only does predictions and can sometimes
  // give lower values than it previously gave for the highs that day
  uint8_t current_hour = curr_time.substring(0, 2).toInt();
  bool new_day = current_hour == 0;

  get_environment_data(
    replace_highs,
    // Weather data
    &weather_overview,
    &temperature_curr_c,
    &temperature_max_c,
    &humidity_curr_pc,
    &humidity_max_pc,
    &wind_speed_curr_kmh,
    &wind_speed_max_kmh,
    &uv_index_curr,
    &uv_index_max,
    &cloudiness_curr_pc,
    &cloudiness_max_pc,
    &precipitation_chances_curr_pc,
    &precipitation_chances_max_pc,
    &precipitation_amount_curr_mm,
    &precipitation_amount_max_mm,

    // Sun / moon data
    &sunrise,
    &sunset,
    &day_length,
    &moon_phase,
    &days_to_next_full_moon
  );

  next_solstice = daysUntilNextSolstice(curr_date.year, (int)curr_date.month, curr_date.day);
  current_day = calculateDayOfYear(curr_date.year, (int)curr_date.month, curr_date.day);
  current_week = calculateWeekOfYear(curr_date.year, (int)curr_date.month, curr_date.day);
}

void update_date_and_time()
{
  curr_time = get_current_time();
  curr_date = get_current_date();
}

#endif