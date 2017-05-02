#include <pebble.h>
#include "num2words-se.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_SE[] = {
  "tolv",
  "ett",
  "två",
  "tre",
  "fyra",
  "fem",
  "sex",
  "sju",
  "åtta",
  "nio",
  "tio",
  "elva",
  "tolv",
  "ett"
};
static const char* const MIN_SE1[]={
  "klockan är",
  "ett",
  "två",
  "tre",
  "fyra",
  "fem",
  "sex",
  "sju",
  "åtta",
  "nio",
  "tio",
  "elva",
  "tolv",
  "tretton",
  "fjorton",
  "kvart",
  "sexton",
  "sjutton",
  "arton",
  "nitton",
  "tjugo"
};
//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_SE[] = {
  "Jan.",
  "Feb.",
  "Mar.",
  "Apr.",
  "Maj.",
  "Jun.",
  "Jul.",
  "Aug.",
  "Sep.",
  "Okt.",
  "Nov.",
  "Dec."
};
const char* const WEEKDAY_SE[] = {
  "Sö.",
  "Må.",
  "Ti.",
  "On.",
  "To.",
  "Fr.",
  "Lö."
};
void WriteDate_NN(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  
}
void WriteDate_SE(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_SE[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_SE[Mnth]);
}