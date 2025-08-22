#pragma once

// Weekday enum
enum Weekday { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
const char* WeekdayStrings[7] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

// Month enum
enum Month { January, February, March, April, May, June, July, August, September, October, November, December };
const char* MonthStrings[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

// WeatherOverview enum
enum WeatherOverview { Sunny, Cloudy, Rainy, Windy };
const char* WeatherStrings[4] = { "Sunny", "Cloudy", "Rainy", "Windy" };

// MoonPhase enum
enum MoonPhase { NewMoon, WaxingCrescent, FirstQuarter, WaxingGibbous, FullMoon, WaningGibbous, LastQuarter, WaningCrescent };
const char* MoonPhaseStrings[8] = { "New Moon", "Waxing Crescent", "First Quarter", "Waxing Gibbous", "Full Moon", "Waning Gibbous", "Last Quarter", "Waning Crescent" };
