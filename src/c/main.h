#pragma once
#include <pebble.h>
#define SETTINGS_KEY 1
// A structure containing our settings
typedef struct ClaySettings {
  GColor BackgroundColor;
  GColor ForegroundColor;
  GColor BackgroundColorNight;
  GColor ForegroundColorNight;
  bool NightTheme;
  bool WeatherUnit;
  int LangKey;
  int DateFormat;
  bool IsNightNow;
  bool GPSOn;
  bool DisplayTemp;
  bool BTOn;
  bool FuzzyMode;
  int HourSunrise;
  int HourSunset;
  int UpSlider;
} __attribute__((__packed__)) ClaySettings;