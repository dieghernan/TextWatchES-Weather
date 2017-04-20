#pragma once
#include "string.h"


void time_to_3words_NN(int hours, int minutes,int *LineBold, char *line1, char *line2, char *line3);
void PopatInit_NN(int minute, int *lenatinit);
void WriteDate_NN(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth );
void Animations_NN(int Minute, int *LenBefore, int *LenNow, int *LenAfter);

extern const char* const MONTHS_NN[];
extern const char* const DAYS_NN[];
extern const char* const WEEKDAY_NN[];
extern const char* const MIN_NN2[];