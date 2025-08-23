#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

#include "Enums.h"
#include "Screens.h"
#include "RTC.h"
#include "Data.h"

#define switch_delay 7500

void setup()
{
  Serial.begin(9600);
  init_tft();
  init_rtc(); // Make sure to call this function once per hour

  // get_environment_data(
  //   // Weather data
  //   &weather_overview,
  //   &temperature_curr_c,
  //   &temperature_max_c,
  //   &humidity_curr_pc,
  //   &humidity_max_pc,
  //   &wind_speed_curr_kmh,
  //   &wind_speed_max_kmh,
  //   &uv_index_curr,
  //   &uv_index_max,
  //   &cloudiness_curr_pc,
  //   &cloudiness_max_pc,
  //   &precipitation_chances_curr_pc,
  //   &precipitation_chances_max_pc,
  //   &precipitation_amount_curr_mm,
  //   &precipitation_amount_max_mm,

  //   // Sun data
  //   &sunrise,
  //   &sunset,
  //   &day_length
  // );

  // Serial.print("Temp: ");
  // Serial.println(temperature_curr_c);
}

void loop()
{
  draw_home_screen(15, 5, Tuesday, April, 19);
  delay(switch_delay);
  draw_weather_screen(Rainy, 19, 25, 40, 60, 5, 10, 7, 8, 95, 97, 60, 100, 1.15, 3.25);
  delay(switch_delay);
  draw_daymoon_screen("6:22", "7:45", "13h 41m", 72, WaxingGibbous, 5, 261, 34, false);
  delay(switch_delay);
}
