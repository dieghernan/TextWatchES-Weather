#pragma once
#include "string.h"


void time_to_3words_FR(int hours, int minutes,int *LineBold, char *line1, char *line2, char *line3);
void PopatInit_FR(int minute, int *lenatinit);
void WriteDate_FR(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth );
void Animations_FR(int Minute, int *LenBefore, int *LenNow, int *LenAfter);

extern const char* const MONTHS_FR[];
extern const char* const DAYS_FR[];
extern const char* const WEEKDAY_FR[];
extern const char* const MIN_FR2[];