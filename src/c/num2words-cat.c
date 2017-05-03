#include <pebble.h>
#include "num2words-cat.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_CAT[] = {
  "dotze",
  "una",
  "dues",
  "tres",
  "quatre",
  "cinc",
  "sis",
  "set",
  "vuit",
  "nou",
  "deu",
  "onze",
  "dotze",
  "una"
};
static const char* const MIN_AUX_CAT[]={
  "la",
  "les",
  "un quart",
  "dos quarts",
  "tres quarts"
};
static const char* const MIN_CAT1[]={
  "en punt",
  "un",
  "dos",
  "tres",
  "quatre",
  "cinc",
  "sis",
  "set",
  "vuit",
  "nou",
  "deu",
  "onze",
  "dotze",
  "tretze",
  "catorze"
};
const char* const MONTHS_CAT[] = {
  "Gen",
  "Feb",
  "Mar",
  "Abr",
  "Mai",
  "Jun",
  "Jul",
  "Ago",
  "Set",
  "Oct",
  "Nov",
  "Des",
};
const char* const WEEKDAY_CAT[] = {
  "Dg.",
  "Dl.",
  "Dt.",
  "Dc.",
  "Dj.",
  "Dv.",
  "Ds.",
};
void time_to_3words_CAT(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean line3 at init
  strcpy(line3, "");  
}
void WriteDate_CAT(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_CAT[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_CAT[Mnth]);
}
