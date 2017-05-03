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
static const char* const MIN_CAT1[]={
  "en punt",
  "tocades",
  "tocades",
  "ben tocades",
  "gairebé",
  "i cinc",
  "vora",
  "mig quart",
  "mig quart",
  "gairebé",
  "i deu",
  "vora",
  "vora",
  "vora",
  "gairebé",
  "un quart",
  "un quart",
  "un quart",
  "un quart",
  "gairebé un",
  "un quart",
  "vora un",
  "un quart",
  "un quart",
  "gairebé un",
  "un quart",
  "vora",
  "vora",
  "vora",
  "gairebé",
  "dos quarts",
  "dos quarts",
  "dos quarts",
  "dos quarts",
  "gairebé dos",
  "dos quarts",
  "vora dos",
  "dos quarts",
  "dos quarts",
  "gairebé dos",
  "dos quarts",
  "vora",
  "vora",
  "vora",
  "gairebé",
  "tres quarts",
  "tres quarts",
  "tres quarts",
  "tres quarts",
  "gairebé tres",
  "tres quarts",
  "vora tres",
  "tres quarts",
  "tres quarts",
  "gairebé tres",
  "tres quarts",
  "vora",
  "vora",
  "vora",
  "a punt"
};
static const char* const MIN_CAT2[]={
  "",
  "",
  "",
  "",
  "i cinc",
  "",
  "mig quart",
  "",
  "",
  "i deu",
  "",
  "un quart",
  "un quart",
  "un quart",
  "un quart",
  "",
  "tocat",
  "tocat",
  "ben tocat",
  "quart i cinc",
  "i cinc",
  "quart i mig",
  "i mig",
  "i mig",
  "quart i deu",
  "i deu",
  "dos quarts",
  "dos quarts",
  "dos quarts",
  "dos quarts",
  "",
  "tocats",
  "tocats",
  "ben tocats",
  "quarts i cinc",
  "i cinc",
  "quarts i mig",
  "i mig",
  "i mig",
  "quarts i deu",
  "i deu",
  "tres quarts",
  "tres quarts",
  "tres quarts",
  "tres quarts",
  "",
  "tocats",
  "tocats",
  "ben tocats",
  "quarts i cinc",
  "i cinc",
  "quarts i mig",
  "i mig",
  "i mig",
  "quarts i deu",
  "i deu",
  "",
  "",
  "",
  "de tocar"
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
  "Ds."
};
void time_to_3words_CAT(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean lines at init
  strcpy(line1,"");
  strcpy(line2,"");
  strcpy(line3,"");
  if (minutes <= 5 || minutes==9 || minutes==10) {
    hours = hours+0;
  }
  else {
    hours=hours+1;
  }
  hours=hours % 12;
  // Hours first
  if (minutes<=5 || minutes==10){
    if (hours==1){
      strcpy(line1,"la ");
    }
    else {
      strcpy(line1,"las ");
    }
    strcat(line1,HOUR_CAT[hours]);
    *LineBold=1;
  }
  else if (minutes==4 || minutes ==9 || minutes==56 || minutes==57 || minutes==58){
    if (hours==1){
      strcpy(line2,"la ");
    }
    else {
      strcpy(line2,"las ");
    }
    strcat(line2,HOUR_CAT[hours]);
    *LineBold=2;
  }
  else if (minutes==59){
    if (hours==1){
      strcpy(line3,"la ");
    }
    else {
      strcpy(line3,"las ");
    }
    strcat(line3,HOUR_CAT[hours]);
    *LineBold=3;
  }
  else if (minutes==7 || minutes==8 || minutes==15 || minutes==30 || minutes==45){
    if (hours==1 || hours==11){strcpy(line2,"d'");}
    else {strcpy(line2,"de ");}
    strcat(line2,HOUR_CAT[hours]);
    *LineBold=2;
  }
  else {
    if (hours==1 || hours==11){strcpy(line3,"d'");}
    else {strcpy(line3,"de ");}
    strcat(line3,HOUR_CAT[hours]);
    *LineBold=3;
  }
  // First part of minute
  if (minutes==0 || minutes==5 || minutes==10){
    strcpy(line2,MIN_CAT1[minutes]);
  }
  else if (minutes>=1 || minutes <=3){
    if (minutes<3){
      if (hours==1) strcpy(line2,"tocada");
      else strcpy(line2,"tocades");
    }
    else{
      if (hours==1) strcpy(line2,"ben tocada");
      else strcpy(line2,"ben tocades");
    }
  }
  // if empty in line1 put minute
  else if (strlen(line1)==0){
    strcpy(line1,MIN_CAT1[minutes]);
  }
  //Last part of minute
  if (strlen(line2)==0){
    strcpy(line2,MIN_CAT2[minutes]);
  }
  else if (strlen(line3)==0){
    strcpy(line3,MIN_CAT2[minutes]);
  }
}
void WriteDate_CAT(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_CAT[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_CAT[Mnth]);
}