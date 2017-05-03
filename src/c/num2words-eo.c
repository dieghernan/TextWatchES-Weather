#include <pebble.h>
#include "num2words-eo.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_EO[] = {
  "dek du",
  "unu",
  "du",
  "tri",
  "kvar",
  "kvin",
  "ses",
  "sep",
  "ok",
  "naŭ",
  "dek",
  "dek unu",
  "dek du",
  "unu"
};
const char* const MONTHS_EO[] = {
  "Jan",
  "Feb",
  "Mar",
  "Apr",
  "Maj",
  "Jun",
  "Jul",
  "Aŭg",
  "Sep",
  "Okt",
  "Nov",
  "Dic",
};
const char* const WEEKDAY_EO[] = {
  "Dim",
  "Lun",
  "Mar",
  "Mer",
  "Jxa",
  "Ven",
  "Sab",
};
void time_to_3words_EO(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean line3 at init
  strcpy(line3, "");
  //shift 1 hour the label for this minutes
  if ( minutes>30) {
    hours=(hours+1);
  }
  hours=hours % 12;
  //Exceptions first
  if (minutes==0){
    strcpy(line1,"la ");
    strcat(line1,HOUR_EO[hours]);
    strcat(line1,"a");
    strcpy(line2,"gŭste");
    *LineBold=1;
  }
  else if(minutes==30){
    strcpy(line1,"la ");
    strcat(line1,HOUR_EO[hours]);
    strcat(line1,"a");
    strcpy(line2,"duono");
    *LineBold=1;
  }
  else {
    //Line1
    if (minutes==15 || minutes==45){
      strcpy(line1,"kvarono");
    }
    else if (minutes <=10 || minutes>=50){
      if (minutes<=10) strcpy(line1,HOUR_EO[minutes]);
      else strcpy(line1,HOUR_EO[60-minutes]);
    }
    else if (minutes <20 || minutes>40){
      strcpy(line1,"dek ");
      if (minutes<20) strcat(line1,HOUR_EO[minutes%10]);
      else strcat(line1,HOUR_EO[(60-minutes)%10]);
    }
    else if (minutes==20 || minutes==40){
      strcpy(line1,"dudek");
    }
    else if (minutes<30){
      strcpy(line1,"dudek ");
      strcat(line1,HOUR_EO[minutes%10]);
    }
    else {
      strcpy(line1,"dudek ");
      strcat(line1,HOUR_EO[(60-minutes)%10]);
    }
    //Line2
    if (minutes<30){
      strcpy(line2,"post");
    }
    else {
      strcpy(line2,"antaŭ");
    }
    //Line3
    strcpy(line3,"la ");
    strcat(line3,HOUR_EO[hours]);
    strcat(line3,"a");
    *LineBold=3;
  }
}
void WriteDate_EO(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_EO[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_EO[Mnth]);
}