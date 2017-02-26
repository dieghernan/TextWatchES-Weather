#pragma once
#include "string.h"


void time_to_3words_ES(int hours, int minutes,int *LineBold, char *line1, char *line2, char *line3);
void PopatInit_ES(int minute, int *lenatinit);
void WriteDate_ES(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth );
void Animations_ES(int Minute, int *LenBefore, int *LenNow, int *LenAfter);

extern const char* const MONTHS_ES[];
extern const char* const DAYS_ES[];
extern const char* const WEEKDAY_ES[];
extern const char* const MIN_ES2[];