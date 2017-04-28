#include <pebble.h>
#include "num2words-nn.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_NN[] = {
  "tolv",
  "ett",
  "to",
  "tre",
  "fire",
  "fem",
  "seks",
  "sju",
  "åtte",
  "ni",
  "ti",
  "elleve",
  "tolv",
  "ett"
};
static const char* const MIN_NN1[]={
  "klokka er",
  "ett",
  "to",
  "tre",
  "fire",
  "fem",
  "seks",
  "sju",
  "åtte",
  "ni",
  "ti",
  "elleve",
  "tolv",
  "tretten",
  "fjorten",
  "kvart"
};
//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_NN[] = {
  "Jan.",
  "Feb.",
  "Mar.",
  "Apr.",
  "Mai.",
  "Jun.",
  "Jul.",
  "Aug.",
  "Sep.",
  "Okt.",
  "Nov.",
  "Des."
};
const char* const WEEKDAY_NN[] = {
  "Sø.",
  "Ma.",
  "Ti.",
  "On.",
  "To.",
  "Fr.",
  "Lø."
};
//End_Weekday
void time_to_3words_NN(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean line3 at init
  strcpy(line3, "");
  //shift 1 hour the label for this minutes
  if ( minutes>15) {hours=(hours+1);}
  //Exceptions first
  hours=hours % 12;
  if (minutes==0 || minutes==30){
    if (minutes==0){
      strcpy(line1,MIN_NN1[minutes]);
    }
    else {
      strcpy(line1,"halv");
    }
    strcpy(line2,HOUR_NN[hours]);
    *LineBold=2;
  }
  else {
    if (minutes<=15){
      strcpy(line1,MIN_NN1[minutes]);
      strcpy(line2,"over");
    }
    else if (minutes<30){
      strcpy(line1,MIN_NN1[30-minutes]);
      strcpy(line2, "på halv");
    }
    else if (minutes<45){
      strcpy(line1,MIN_NN1[minutes-30]);
      strcpy(line2, "over halv");
    }
    else{
      strcpy(line1,MIN_NN1[60-minutes]);
      strcpy(line2, "på");
    }
    strcpy(line3, HOUR_NN[hours]);
    *LineBold=3;
  }
}
void WriteDate_NN(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_NN[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_NN[Mnth]);
}
int Len_NN(int min){
  if (min==0 || min==30){
    return 0;
  }
  else return 10;
}
void Animations_NN(int Minute, int *LenBefore, int *LenNow, int *LenAfter){
  *LenNow=Len_NN(Minute);
  if (Minute==0){
    *LenBefore=Len_NN(59);
  }
  else {
    *LenBefore=Len_NN(Minute-1);
  }
  if (Minute==59){
    *LenAfter=Len_NN(0);
  }
  else {
    *LenAfter=Len_NN(Minute+1);
  }
}