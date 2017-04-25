#pragma once
#include "string.h"
void time_to_3words_IT(int hours, int minutes,int *LineBold, char *line1, char *line2, char *line3);
void PopatInit_IT(int minute, int *lenatinit);
void WriteDate_IT(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth );
void Animations_IT(int Minute, int *LenBefore, int *LenNow, int *LenAfter);
extern const char* const MONTHS_IT[];
extern const char* const DAYS_IT[];
extern const char* const WEEKDAY_IT[];