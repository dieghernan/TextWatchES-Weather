#include <pebble.h>
#include "num2words-cat.h"
#include "string.h"
#include <stddef.h>
//Mixed system: http://www.comunicaciodigital.com/rellotge_catala/quarts_mixt.htm
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
  "un",
  "dos",
  "tres",
  "quatre",
  "cinc",
  "sis",
  "mig",
  "vuit",
  "nou",
  "deu"
};
static const char* const MIN_AUX_CAT[]={
  "a ",
  "i ",
  " per",
  " quarts",
  " quart"
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
  "Des"
};
const char* const WEEKDAY_CAT[] = {
  "dg",
  "dl",
  "dt",
  "dc",
  "dj",
  "dv",
  "ds"
};
void hour_l(int h, char* linehour){
  if (h==1){
    strcpy(linehour,"la ");
  }
  else {
    strcpy(linehour, "las ");
  }
  strcat(linehour,HOUR_CAT[h]);
}
void hour_d(int h, char* linehour){
  if (h==1 || h==11){
    strcpy(linehour,"d'");
  }
  else {
    strcpy(linehour, "de ");
  }
  strcat(linehour,HOUR_CAT[h]);
}
void time_to_3words_CAT(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean lines at init
  strcpy(line1,"");
  strcpy(line2,"");
  strcpy(line3,"");
  if (minutes > 10 || minutes==7) {
    hours=hours+1;
  }
  hours=hours % 12;
  // Put minutes under 11
  if (minutes==7){
    strcpy(line1,MIN_CAT1[7]);
    strcat(line1,MIN_AUX_CAT[4]);
    hour_d(hours,line2);
    *LineBold=2;
  }
  else if (minutes==0){
    hour_l(hours,line1);
    *LineBold=1;
    strcpy(line2, MIN_CAT1[minutes]);
  }
  else if (minutes<=10){
    hour_l(hours,line1);
    *LineBold=1;
    strcpy(line2,MIN_AUX_CAT[1]);
    strcat(line2, MIN_CAT1[minutes]);
  }
  else {
    //Line1
    if((60-minutes)%15 >=1 && (60-minutes)%15 <=4 ){
      strcpy(line1,MIN_CAT1[(60-minutes)%15]);
      strcat(line1,MIN_AUX_CAT[2]);
    }
    else {
      strcpy(line1,MIN_CAT1[minutes/15]);
      if ((minutes/15)==1){
        strcat(line1,MIN_AUX_CAT[4]);
      }
      else {
        strcat(line1,MIN_AUX_CAT[3]);
      }
    }
    //Line 2
    if (minutes>=56){
      *LineBold=2;
      strcpy(line2,MIN_AUX_CAT[0]);
      if (hours==1){
        strcat(line2,"la ");
      }
      else {
        strcat(line2,"las ");
      }
      strcat(line2,HOUR_CAT[hours]);
    }
    else if (minutes%15==5 || minutes%15==7 || minutes%15==10){
      strcpy(line2,MIN_AUX_CAT[1]);
      strcat(line2,MIN_CAT1[minutes%15]);
    }
    else if(minutes%15>10){
      strcpy(line2,MIN_AUX_CAT[0]);
      strcat(line2,MIN_CAT1[(minutes/15)+1]);
      if (minutes<=15){
        strcat(line2,MIN_AUX_CAT[4]);
      }
      else {
        strcat(line2,MIN_AUX_CAT[3]);
      }
    }
    else {
      *LineBold=2;
      hour_d(hours,line2);
    }
    //Line3
    if (minutes>=56 || minutes%15==0){
      strcpy(line3,"");
    }
    else if (minutes%15==5 || minutes%15==7 || minutes%15>=10){
      *LineBold=3;      
      hour_d(hours, line3);
    }
    else {
      strcpy(line3, MIN_AUX_CAT[1]);
      strcat(line3,MIN_CAT1[minutes%15]);
    }
  }
}
void WriteDate_CAT(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_CAT[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_CAT[Mnth]);
}