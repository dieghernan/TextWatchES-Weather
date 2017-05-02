#include <pebble.h>
#include "num2words-br.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_BR[] = {
  "doze",
  "uma",
  "duas",
  "três",
  "quatro",
  "cinco",
  "seis",
  "sete",
  "oito",
  "nove",
  "dez",
  "onze",
  "doze",
  "uma"
};
static const char* const MIN_AUX_BR[]={
  "",
  "",
  "vinte",
  "trinta"
};
static const char* const MIN_BR1[]={
  "horas",
  "um",
  "dois",
  "três",
  "quatro",
  "cinco",
  "seis",
  "sete",
  "oito",
  "nove",
  "dez",
  "onze",
  "doze",
  "treze",
  "catorze",
  "quinze",
  "dezasseis",
  "dezassete",
  "dezoito",
  "dezanove",
  "vinte"
};
//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_BR[] = {
  "Jan",
  "Fev",
  "Mar",
  "Abr",
  "Mai",
  "Jun",
  "Jul",
  "Ago",
  "Set",
  "Out",
  "Nov",
  "Dez"
};
const char* const WEEKDAY_BR[] = {
  "Dom",
  "Seg",
  "Ter",
  "Qua",
  "Qui",
  "Sex",
  "Sab"
};
void time_to_3words_BR(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean Line3 at init
  strcpy(line3,"");
  //shift 1 hour the label for this minutes
  if ( minutes>39) {hours=(hours+1);}
  hours=hours % 12;
  //Exceptions first
  if (minutes<40){
    //hour - line1
    strcpy(line1, HOUR_BR[hours]);
    // Fix plural for 1hour
    if (minutes==0 && hours==1){
      strcpy(line2,"hora");
    }
    else if (minutes==20){
      strcpy(line2, "e vinte");
    }
    else if (minutes==30){
      strcpy(line2,"e meia");
    }
    else if (minutes==0){
      strcpy(line2, MIN_BR1[minutes]);
    }
    else if (minutes<=14){
      strcpy(line2, "e ");
      strcat(line2, MIN_BR1[minutes]);
    }
    else if(minutes<20){
      strcpy(line2, MIN_BR1[minutes]);
    }
    else if (minutes<40){
      strcpy(line2, MIN_AUX_BR[minutes/10]);
      strcpy(line3, "e ");
      strcat(line3, MIN_BR1[minutes % 10]);
    }
    *LineBold=1;
  }
  else {
    strcpy(line1,MIN_BR1[60-minutes]);
    strcpy(line2,"para as");
    strcpy(line3, HOUR_BR[hours]);
    *LineBold=3;
  }
}
void WriteDate_BR(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_BR[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_BR[Mnth]);
}