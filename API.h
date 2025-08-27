#ifndef API_H
#define API_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "Wifi.h"
#include "Secrets.h"
#include "CalendarFuncs.h"
#include "TimeFuncs.h"

void turn_wifi_on()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) delay(500);
  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("WIFI failed");
    ShowWifiFailureScreen();
    return;
  } else {
    Serial.println("WIFI on");
  }
}

void turn_wifi_off()
{
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  btStop();
  delay(100); // short pause to let it shut down
  Serial.println("WIFI off");
}

WeatherOverview strToWeatherOverview(String s)
{
  if (s == "Clear") return Clear;
  else if (s == "Clouds") return Cloudy;
  else if (s == "Rain") return Rainy;
  else if (s == "Drizzle") return Rainy;
  else if (s == "Snow") return Snowy;
  else if (s == "Mist") return Misty;
  else if (s == "Smoke") return Smokey;
  else if (s == "Haze") return Hazy;
  else if (s == "Sand") return Sandy;
  else if (s == "Dust") return Dusty;
  else if (s == "Fog") return Foggy;
  else if (s == "Thunderstorm") return Stormy;
  else
  {
    Serial.println(s);
    Serial.println("Failed to convert weather overview");
    delay(9000000);
    return Clear;
  }
}

MoonPhase calculateMoonPhase(float index) {
  // normalize index to 0..1
  if (index < 0) index = 0;
  if (index > 1) index = fmod(index, 1.0);

  // handle exact round values
  if (fabs(index - 0.0) < 0.01 || fabs(index - 1.0) < 0.01) return NewMoon;
  if (fabs(index - 0.25) < 0.01) return FirstQuarter;
  if (fabs(index - 0.50) < 0.01) return FullMoon;
  if (fabs(index - 0.75) < 0.01) return LastQuarter;

  // otherwise assign based on ranges
  if (index > 0.0  && index < 0.25) return WaxingCrescent;
  if (index > 0.25 && index < 0.50) return WaxingGibbous;
  if (index > 0.50 && index < 0.75) return WaningGibbous;
  if (index > 0.75 && index < 1.0)  return WaningCrescent;

  // Error
  Serial.println(index);
  Serial.println("Failed to calculate moon phase");
  delay(9000000);
  return NewMoon;
}

uint8_t calculateDaysToFullMoon(float moonPhaseIndex)
{
  const float lunarCycle = 29.53; // average length of lunar cycle in days
  float phaseUntilFull = 0.5 - moonPhaseIndex;

  // wrap around if we're past the full moon
  if (phaseUntilFull < 0) phaseUntilFull += 1.0;

  // convert fraction of lunar cycle to days
  uint8_t days = (uint8_t)round(phaseUntilFull * lunarCycle);
  return days;
}

/**
 * Takes in a bunch of variables as pointers, queries the API,
 * and then populates the variables with the accurate data
 */
void get_environment_data(
  // Weather data
  WeatherOverview* _weather_overview,
  int8_t* _temperature_curr_c,
  int8_t* _temperature_max_c,
  uint8_t* _humidity_curr_pc,
  uint8_t* _humidity_max_pc,
  uint8_t* _wind_speed_curr_kmh,
  uint8_t* _wind_speed_max_kmh,
  float* _uv_index_curr,
  float* _uv_index_max,
  uint8_t* _cloudiness_curr_pc,
  uint8_t* _cloudiness_max_pc,
  uint8_t* _precipitation_chances_curr_pc,
  uint8_t* _precipitation_chances_max_pc,
  float* _precipitation_amount_curr_mm,
  float* _precipitation_amount_max_mm,

  // Sun / moon data
  String* _sunrise,
  String* _sunset,
  String* _day_length,
  MoonPhase* _moon_phase,
  uint8_t* _days_to_next_full_moon
)
{
  turn_wifi_on();

  if (WiFi.status() != WL_CONNECTED)
  {
    ShowWifiFailureScreen();
    return;
  }

  // Perform get request
  HTTPClient http;
  http.begin(WEATHER_API_ROUTE);
  int code = http.GET();
  if (code != 200)
  {
    ShowGetFailureScreen(code);
    return;
  }

  // Parse JSON
  String body = http.getString();
  DynamicJsonDocument doc(30000); // 30KB
  DeserializationError error = deserializeJson(doc, body);
  if (error) 
  {
    Serial.print("JSON parse failed: ");
    Serial.println(error.c_str());
    ShowGetFailureScreen(-666);
    return;
  }

  // Get values
  *_weather_overview = strToWeatherOverview(doc["current"]["weather"][0]["main"]);
  *_temperature_curr_c = doc["current"]["temp"];
  *_temperature_max_c = doc["daily"][0]["temp"]["max"];
  *_humidity_curr_pc = doc["current"]["humidity"];
  *_humidity_max_pc = doc["daily"][0]["humidity"];
  *_wind_speed_curr_kmh = doc["current"]["wind"];
  *_wind_speed_max_kmh = doc["daily"][0]["wind_speed"];
  *_uv_index_curr = doc["current"]["uvi"];
  *_uv_index_max = doc["daily"][0]["uvi"];
  *_cloudiness_curr_pc = doc["current"]["clouds"];
  *_cloudiness_curr_pc = doc["daily"][0]["clouds"];
  *_precipitation_chances_curr_pc = doc["hourly"]["pop"];
  *_precipitation_chances_max_pc = doc["daily"][0]["pop"];
  if (doc["hourly"][0].containsKey("rain") && doc["hourly"][0]["rain"].containsKey("1h"))
  {
    *_precipitation_amount_curr_mm = doc["hourly"][0]["rain"]["1h"].as<float>();
  }
  else if (doc["current"].containsKey("snow") && doc["current"]["snow"].containsKey("1h"))
  {
    *_precipitation_amount_curr_mm = doc["current"]["snow"]["1h"].as<float>();
  }
  else
  {
    *_precipitation_amount_curr_mm = 0.00;
  }

  if (doc["daily"][0].containsKey("rain"))
  {
    *_precipitation_amount_max_mm = doc["daily"][0]["rain"].as<float>();
  }
  else if (doc["daily"][0].containsKey("snow"))
  {
    *_precipitation_amount_max_mm = doc["daily"][0]["snow"].as<float>();
  }
  else
  {
    *_precipitation_amount_max_mm = 0.00;
  }

  *_sunrise = unix_tsToHHMM(doc["daily"][0]["sunrise"]);
  *_sunset = unix_tsToHHMM(doc["daily"][0]["sunset"]);;
  *_day_length = calculate_day_length(doc["daily"][0]["sunrise"], doc["daily"][0]["sunset"]);
  *_moon_phase = calculateMoonPhase(doc["daily"][0]["moon_phase"]);
  *_days_to_next_full_moon = calculateDaysToFullMoon(doc["daily"][0]["moon_phase"]);

  // Cleanup
  http.end();
  turn_wifi_off();
}

#endif