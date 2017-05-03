#include <pebble.h>
#include "num2words-nl.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_NL[] = {
  "twaalf",
  "één",
  "twee",
  "drie",
  "vier",
  "vijf",
  "zes",
  "zeven",
  "acht",
  "negen",
  "tien",
  "elf",
  "twaalf",
  "één"
};
static const char* const MIN_NL1[]={
  "uur",
  "één",
  "twee",
  "drie",
  "vier",
  "vijf",
  "zes",
  "zeven",
  "acht",
  "negen",
  "tien",
  "elf",
  "twaalf",
  "dertien",
  "veertien",
  "kwart"
};
//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_NL[] = {
  "Jan.",
  "Feb.",
  "Maa.",
  "Apr.",
  "Mei.",
  "Jun.",
  "Jul.",
  "Aug.",
  "Sep.",
  "Okt.",
  "Nov.",
  "Dec."
};
const char* const WEEKDAY_NL[] = {
  "Zo.",
  "Ma.",
  "Di.",
  "Wo.",
  "Do.",
  "Vr.",
  "Za."
};
//End_Weekday
void time_to_3words_NL(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean line3 at init
  strcpy(line3, "");
  //shift 1 hour the label for this minutes
  if ( minutes>15) {hours=(hours+1);}
  //Exceptions first
  hours=hours % 12;
  if (minutes==0){
    strcpy(line1,HOUR_NL[hours]);
    strcpy(line2,MIN_NL1[minutes]);
    *LineBold=1;
  }
  else if (minutes==30){
    strcpy(line1,"half");
    strcpy(line2,HOUR_NL[hours]);
    *LineBold=2;
  }
  else {
    if (minutes<=15){
      strcpy(line1,MIN_NL1[minutes]);
      strcpy(line2,"over");
    }
    else if (minutes<30){
      strcpy(line1,MIN_NL1[30-minutes]);
      strcpy(line2, "voor half");
    }
    else if (minutes<45){
      strcpy(line1,MIN_NL1[minutes-30]);
      strcpy(line2, "over half");
    }
    else{
      strcpy(line1,MIN_NL1[60-minutes]);
      strcpy(line2, "voor");
    }
    strcpy(line3, HOUR_NL[hours]);
    *LineBold=3;
  }
}
void WriteDate_NL(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_NL[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_NL[Mnth]);
}