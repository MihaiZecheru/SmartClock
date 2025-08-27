#ifndef ENUMS_H
#define ENUMS_H

// Weekday enum
// The week in the system starts with Monday, but the date API uses Sunday as day 0 so that's how the enum is set up
enum Weekday { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
const char* WeekdayStrings[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

// Month enum
enum Month { January, February, March, April, May, June, July, August, September, October, November, December };
const char* MonthStrings[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

// WeatherOverview enum
enum WeatherOverview { Clear, Cloudy, Rainy, Snowy, Misty, Smokey, Hazy, Dusty, Foggy, Stormy, Sandy };
const char* WeatherStrings[11] = { "Clear", "Cloudy", "Rainy", "Snowy", "Misty", "Smokey", "Hazy", "Dusty", "Foggy", "Stormy", "Sandy" };

// MoonPhase enum
enum MoonPhase { NewMoon, WaxingCrescent, FirstQuarter, WaxingGibbous, FullMoon, WaningGibbous, LastQuarter, WaningCrescent };
const char* MoonPhaseStrings[8] = { "New Moon", "Waxing Crescent", "First Quarter", "Waxing Gibbous", "Full Moon", "Waning Gibbous", "Last Quarter", "Waning Crescent" };

#endif