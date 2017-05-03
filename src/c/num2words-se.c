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
void time_to_3words_SE(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean line3 at init
  strcpy(line3, "");
  //shift 1 hour the label for this minutes
  if ( minutes>20) {hours=(hours+1);}
  //Exceptions first
  hours=hours % 12;
  if (minutes==0 || minutes==30 || minutes>=40){
    if (minutes==0){
      strcpy(line1,MIN_SE1[minutes]);
    }
    else if (minutes==30) {
      strcpy(line1,"halv");
    }
    else {
      strcpy(line1,MIN_SE1[60-minutes]);
      strcat(line1, " i");
    }
    strcpy(line2,HOUR_SE[hours]);
    *LineBold=2;
  }
  else {
    if (minutes<=20){
      strcpy(line1,MIN_SE1[minutes]);
      strcpy(line2,"över");
    }
    else if (minutes<30){
      strcpy(line1,MIN_SE1[30-minutes]);
      strcpy(line2, "i halv");
    }
    else if (minutes<40){
      strcpy(line1,MIN_SE1[minutes-30]);
      strcpy(line2, "över halv");
    }
    strcpy(line3, HOUR_SE[hours]);
    *LineBold=3;
  }
}
void WriteDate_SE(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_SE[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_SE[Mnth]);
}