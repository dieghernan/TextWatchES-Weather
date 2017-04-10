#pragma once
#include "string.h"


void time_to_3words_DE(int hours, int minutes,int *LineBold, char *line1, char *line2, char *line3);
void PopatInit_DE(int minute, int *lenatinit);
void WriteDate_DE(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth );
void Animations_DE(int Minute, int *LenBefore, int *LenNow, int *LenAfter);

extern const char* const MONTHS_DE[];
extern const char* const DAYS_DE[];
extern const char* const WEEKDAY_DE[];
extern const char* const MIN_DE2[];