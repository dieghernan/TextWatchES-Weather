#pragma once


void time_to_3words_BR(int hours, int minutes,int *LineBold, char *line1, char *line2, char *line3);
void PopatInit_BR(int minute, int *lenatinit);
void WriteDate_BR(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth );
void Animations_BR(int Minute, int *LenBefore, int *LenNow, int *LenAfter);

extern const char* const MONTHS_BR[];
extern const char* const DAYS_BR[];
extern const char* const WEEKDAY_BR[];
extern const char* const MIN_BR2[];