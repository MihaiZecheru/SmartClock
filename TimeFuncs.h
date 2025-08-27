#ifndef TIME_FUNCS_H
#define TIME_FUNCS_H

/**
 * Convert a unix timestamp into "hh:mm" format
 */
String unix_tsToHHMM(uint64_t unix_ts)
{
  time_t t = (unix_ts > 1000000000000ULL) ? (time_t)(unix_ts / 1000ULL) : (time_t)unix_ts; // ms? -> s
  struct tm tmLocal;
  if (!localtime_r(&t, &tmLocal)) return "Time not set";
  char buf[6];
  strftime(buf, sizeof(buf), "%H:%M", &tmLocal);
  return String(buf);
}

/**
 * Given the sunrise and sunset times in unix format,
 * will return the day length in "xxh xxm" format (e.g. 13h 15m)
 */
String calculate_day_length(uint64_t unix_sunrise_ts, uint64_t unix_sunset_ts)
{
  uint64_t diff = unix_sunset_ts - unix_sunrise_ts;
  uint8_t hours = diff / 3600;
  uint8_t minutes = diff % 3600 / 60;
  char buf[8];
  sprintf(buf, "%dh %dm", hours, minutes);
  return String(buf);
}

struct Date
{
  Weekday weekday;
  uint8_t day;
  Month month;
  uint16_t year;
};

/**
 * Returns the current date as a date object  
 */
Date get_current_date() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("RTC failed");
    Date fallback;
    fallback.day = 0;
    fallback.month = January;
    fallback.year = 0;
    fallback.weekday = Sunday;
    return fallback;
  }

  Date current_date;
  current_date.day = timeinfo.tm_mday;
  current_date.month = static_cast<Month>(timeinfo.tm_mon);
  current_date.year = timeinfo.tm_year;
  current_date.weekday = static_cast<Weekday>(timeinfo.tm_wday);
  return current_date;
}

/**
 * Returns the current time formatted in "hh:mm" (e.g. 13:05)
 */
String get_current_time()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("RTC failed");
    return "Time not set";
  }

  char buf[20];
  strftime(buf, sizeof(buf), "%H:%M", &timeinfo);
  return String(buf);
}

#endif