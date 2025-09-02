#ifndef ENUMS_H
#define ENUMS_H

// Weekday enum used for displaying data
// The week in the system starts with Monday, but the date API uses Sunday as day 0 so that's how the enum is set up
enum Weekday { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };
const char* WeekdayStrings[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

// Month enum used for displaying data
enum Month { January, February, March, April, May, June, July, August, September, October, November, December };
const char* MonthStrings[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

// WeatherOverview enum used for displaying data
enum WeatherOverview { Clear, Cloudy, Rainy, Snowy, Misty, Smokey, Hazy, Dusty, Foggy, Stormy, Sandy };
const char* WeatherStrings[11] = { "Clear", "Cloudy", "Rainy", "Snowy", "Misty", "Smokey", "Hazy", "Dusty", "Foggy", "Stormy", "Sandy" };

// MoonPhase enum used for displaying data
enum MoonPhase { NewMoon, WaxingCrescent, FirstQuarter, WaxingGibbous, FullMoon, WaningGibbous, LastQuarter, WaningCrescent };
const char* MoonPhaseStrings[8] = { "New Moon", "Waxing Crescent", "First Quarter", "Waxing Gibbous", "Full Moon", "Waning Gibbous", "Last Quarter", "Waning Crescent" };

// Screen enum for keeping track of the currently displayed screen.
// Used in cycling the active screen with the button
enum Screen { HomeScreen, WeatherScreen, DayMoonScreen };

// Units enum for use in tracking which units to use for the display data
enum UnitSystem { Metric, Imperial };

#endif