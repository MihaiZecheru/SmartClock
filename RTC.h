#ifndef RTC_H
#define RTC_H

#include "API.h"

void init_rtc()
{
  turn_wifi_on();
  configTzTime("PST8PDT,M3.2.0,M11.1.0", "pool.ntp.org");

  // Wait until time is set
  struct tm timeinfo;
  int retries = 0;
  while (!getLocalTime(&timeinfo) && retries < 30) {
    Serial.println("Waiting for NTP time...");
    delay(500);
    retries++;
  }

  if (retries < 30) Serial.println("RTC initialized");
  else Serial.println("Failed to get time from NTP");

  turn_wifi_off();
}

#endif