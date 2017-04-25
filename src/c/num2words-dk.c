#include <pebble.h>
#include "num2words-dk.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_DK[] = {
  "tolv",
  "et",
  "to",
  "tre",
  "fire",
  "fem",
  "seks",
  "syv",
  "otte",
  "ni",
  "ti",
  "elleve",
  "tolv",
  "et"
};
static const char* const MIN_DK1[]={
  "klokken",
  "et",
  "to",
  "tre",
  "fire",
  "fem",
  "seks",
  "syv",
  "otte",
  "ni",
  "ti",
  "elleve",
  "tolv",
  "tretten",
  "fjorten",
  "kvart",
  "seksten",
  "sytten",
  "atten",
  "nitten",
  "tyve",
  "énog",
  "toog",
  "treog",
  "fireog"
};
//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_DK[] = {
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
const char* const WEEKDAY_DK[] = {
  "Sø.",
  "Ma.",
  "Ti.",
  "On.",
  "To.",
  "Fr.",
  "Lø."
};
//End_Weekday
void time_to_3words_DK(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //hour - line1
  //shift 1 hour the label for this minutes
  if ( minutes>=25) {hours=(hours+1);}
  hours=hours % 12;
  // Exceptions first
  if (minutes==0 ||  minutes==30){
    if (minutes==0){
      strcpy(line1, MIN_DK1[0]);
    }
    else {
      strcpy(line1,"halv");      
    }
    strcpy(line2,HOUR_DK[hours]);
    strcpy(line3, "");
    *LineBold=2;    
  }
  else {
    if (minutes<=20){
      strcpy(line1, MIN_DK1[minutes]);
      strcpy(line2, "over");
    }
    else if (minutes<25){
      strcpy(line1, MIN_DK1[minutes]);
      strcpy(line2, "tyve over");      
    }
    else if (minutes<=30){
      strcpy(line1,MIN_DK1[30-minutes]);
      strcpy(line2,"i halv");    
    }
    else if (minutes<=35){
      strcpy(line1,MIN_DK1[minutes-30]);
      strcpy(line2,"over halv");     
    }     
    else if (minutes<40){
      strcpy(line1, MIN_DK1[60-minutes]);
      strcpy(line2, "tyve i");
    }
    else {
      strcpy(line1, MIN_DK1[60-minutes]);
      strcpy(line2, "i");
    }
    strcpy(line3,HOUR_DK[hours]);
    *LineBold=3;
  }
}
int Len_DK(int min){
  if (min==0 || min==30){
    return 0;
  }
  else return 10;
}
void PopatInit_DK(int minute, int *lenatinit){
  *lenatinit=Len_DK(minute);
}
void WriteDate_DK(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_DK[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_DK[Mnth]);
}
void Animations_DK(int Minute, int *LenBefore, int *LenNow, int *LenAfter){
  *LenNow=Len_DK(Minute);
  if (Minute==0){	
    *LenBefore=Len_DK(59);
  }
  else {
    *LenBefore=Len_DK(Minute-1);
  }
  if (Minute==59){
    *LenAfter=Len_DK(0);
  }
  else {
    *LenAfter=Len_DK(Minute+1);
  }
}
