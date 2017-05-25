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
static const char* const MIN_NN_C[]={
  "",
  "en",
  "to",
  "tre",
  "fire",
  "fem",
  "seks",
  "sju",
  "åtte",
  "ni",
  "ti"  
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
  "kvart",
  "seksten",
  "sytten",
  "atten",
  "nitten"
};
static const char* const MIN_NNAUX[] = {
  "null",
  "",
  "tjue",
  "tretti",
  "førti",
  "femti"
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
  //Clean lines at init
  strcpy(line1,"");
  strcpy(line2, "");
  strcpy(line3, "");
  //shift 1 hour the label for this minutes
  if ( minutes>=20) {hours=(hours+1);}
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
    if (minutes<=19){
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
void time_to_3words_NN2(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean lines at init
  strcpy(line1,"");
  strcpy(line2, "");
  strcpy(line3, "");
  //Line 1 is always hour except at oclock
  hours=hours % 12;
  if (minutes==0){
    strcpy(line1,MIN_NN1[minutes]);
    strcpy(line2,HOUR_NN[hours]);
    *LineBold=2;
    strcpy(line3,"");
  }
  else {
    strcpy(line1, HOUR_NN[hours]);
    *LineBold=1;
    //Line2
    if (minutes<10){
      strcpy(line2,MIN_NNAUX[0]);    
    }
    else if (minutes>=20){
      strcpy(line2,MIN_NNAUX[minutes/10]);     
    }
    else if (minutes==15){
      strcpy(line2,"femten");
    }
    else {
      strcpy(line2,MIN_NN1[minutes]);
    }
    //Line3
    if (minutes%10==0){
      strcpy(line3,"");
    }
    else if (minutes<=9 || minutes>=20){
      strcpy(line3, MIN_NN_C[minutes%10]);
    } 
  }
}
void WriteDate_NN(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_NN[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_NN[Mnth]);
}