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
  //Clean Line3 at init
  strcpy(line3, "");
  //shift 1 hour the label for this minutes
  if ( minutes>=25) {hours=(hours+1);}
  hours=hours % 12;
  // Exceptions first
  if (minutes==0 ||  minutes==30 || minutes>=40){
    if (minutes==0){
      strcpy(line1, MIN_DK1[0]);
    }
    else if(minutes==30){
      strcpy(line1,"halv");      
    }
    else {
      strcpy(line1,MIN_DK1[60-minutes]);  
      strcat(line1," i");          
    }
    strcpy(line2,HOUR_DK[hours]);
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
    else {
      strcpy(line1, MIN_DK1[60-minutes]);
      strcpy(line2, "tyve i");
    }
    strcpy(line3,HOUR_DK[hours]);
    *LineBold=3;
  }
}
void WriteDate_DK(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_DK[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_DK[Mnth]);
}