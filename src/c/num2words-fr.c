#include <pebble.h>
#include "num2words-fr.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_FR[] = {
  "douze",
  "une",
  "deux",
  "trois",
  "quatre",
  "cinq",
  "six",
  "sept",
  "huit",
  "neuf",
  "dix",
  "onze",
  "douze",
  "une"
};
static const char* const MIN_FR1[]={
  "pile",
  "et une",
  "deux",
  "trois",
  "quatre",
  "cinq",
  "six",
  "sept",
  "huit",
  "neuf",
  "dix",
  "onze",
  "douze",
  "treize",
  "quatorze",
  "et quart",
  "seize"
};
//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_FR[] = {
  "Jan",
  "Fév",
  "Mar",
  "Avr",
  "Mai",
  "Jui",
  "Jui",
  "Aoû",
  "Sep",
  "Oct",
  "Nov",
  "Déc"
};
const char* const WEEKDAY_FR[] = {
  "Dim",
  "Lun",
  "Mar",
  "Mer",
  "Jeu",
  "Ven",
  "Sam",
};
//End_Weekday
void time_to_3words_FR(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //hour - line1
  //shift 1 hour the label for this minutes
  if ( minutes>39) {hours=(hours+1);}
  hours=hours % 12;
  strcpy(line1, HOUR_FR[hours]);
  *LineBold=1;
  //minute
  // Exceptions first
  if (minutes<=16){
    strcpy(line2,MIN_FR1[minutes]);
    strcpy(line3,"");
  }
  else if (minutes<20){
    strcpy(line2,"dix");
    strcpy(line3,MIN_FR1[minutes-10]);
  }
  else if (minutes==20){
    strcpy(line2,"vingt");
    strcpy(line3,"");
  }
  else if (minutes<30){
    strcpy(line2,"vingt");
    strcpy(line3,MIN_FR1[minutes-20]);
  }
  else if (minutes==30){
    strcpy(line2,"et demie");
    strcpy(line3,"");
  }
  else if (minutes<40){
    strcpy(line2,"trente");
    strcpy(line3,MIN_FR1[minutes-30]);
  }
  else {
    strcpy(line2,"moins");
    if (minutes==40){
      strcpy(line3,"vingt");
    }
    else if (minutes<44){
      strcpy(line3,"dix-");
      strcat(line3,MIN_FR1[50-minutes]);
    }
    else if (minutes==45){
      strcpy(line3,"le quart");
    }
    else if (minutes==59){
      strcpy(line3,"une");
    }
    else {
      strcpy(line3,MIN_FR1[60-minutes]);
    }
  }
}
int Len_FR(int min){
  if (min<17 || min==20 || min==30){
    return 0;
  }
  else return 10;
}
void WriteDate_FR(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_FR[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_FR[Mnth]);
}
void Animations_FR(int Minute, int *LenBefore, int *LenNow, int *LenAfter){
  *LenNow=Len_FR(Minute);
  if (Minute==0){
    *LenBefore=Len_FR(59);
  }
  else {
    *LenBefore=Len_FR(Minute-1);
  }
  if (Minute==59){
    *LenAfter=Len_FR(0);
  }
  else {
    *LenAfter=Len_FR(Minute+1);
  }
}