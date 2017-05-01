#include <pebble.h>
#include "num2words-it.h"
#include <stddef.h>
#include <string.h>
static const char* const HOUR_IT[] = {
  "mezzanotte",
  "una",
  "due",
  "tre",
  "quattro",
  "cinque",
  "sei",
  "sette",
  "otto",
  "nove",
  "dieci",
  "undici",
  "mezzogiorno",
  "una"
};
static const char* const MIN_IT1[]={
  "in punto",
  "una",
  "due",
  "tre",
  "quattro",
  "cinque",
  "sei",
  "sette",
  "otto",
  "nove",
  "dieci",
  "undici",
  "dodici",
  "tredici",
  "quattor",
  "un quarto",
  "sedici",
};
const char* const MIN_IT_AUX[]={
  "e dicias",
  "e dici",
  "e dician",
  "e ventuno",
  "e ventidue",
  "e ventitré",
  "e trentuno",
  "e trentadue",
  "e trentatré",
};
//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_IT[] = {
  "Gen",
  "Feb",
  "Mar",
  "Apr",
  "Mag",
  "Giu",
  "Lug",
  "Ago",
  "Set",
  "Ott",
  "Nov",
  "Dic"
};
const char* const WEEKDAY_IT[] = {
  "Dom",
  "Lun",
  "Mar",
  "Mer",
  "Gio",
  "Ven",
  "Sab"
};
//End_Weekday
void time_to_3words_IT(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean line 3 at init
  strcpy(line3, "");
  //shift 1 hour the label for this minutes
  if ( minutes>39) {hours=(hours+1);}
  if (hours>13){
    hours=hours % 12;
  }
  // in italian the hour is always in the first line
  *LineBold=1;
  strcpy(line1, HOUR_IT[hours]);
  //minute optimized for italian
  //Exceptions first
  if (minutes==0){
    strcpy(line2, MIN_IT1[0]);
  }
  else if (minutes==30){
    strcpy(line2, "e mezzo");
  }
  else if (minutes==14){
    strcpy(line2, "e quattor");
    strcpy(line3, "dici"); 
  }
  else if (minutes>=17 && minutes<=19){
    strcpy(line2, MIN_IT_AUX[minutes-17]);
    strcpy(line3, MIN_IT1[minutes%10]); 
  }
  else if (minutes>=21 && minutes <=23){
    strcpy(line2, MIN_IT_AUX[minutes-18]);
  }
  else if (minutes>=31 && minutes <=33){
    strcpy(line2, MIN_IT_AUX[minutes-25]);
  }
  else if (minutes<20){
    strcpy(line2,"e ");
    strcat(line2, MIN_IT1[minutes]); 
  }
  else if (minutes==20){
    strcpy(line2,"e venti");
  }
  else if (minutes<30){
    strcpy(line2,"e venti");
    strcpy(line3,MIN_IT1[minutes%10]);
  }
  else if (minutes<40){
    strcpy(line2,"e trenta");
    strcpy(line3,MIN_IT1[minutes%10]);
  }
  else {
    strcpy(line2,"meno");
    if (minutes==40){
      strcpy(line3,"venti"); 
    }
    else if (minutes==41){
      strcpy(line3,"diciannove");
    }
    else if (minutes==42){
      strcpy(line3,"diciotto");
    }
    else if (minutes==43){
      strcpy(line3,"diciassette");
    }
    else if (minutes==46){
      strcpy(line3,"quattordici"); 
    }
    else{
      strcpy(line3,MIN_IT1[60-minutes]);
    }
  }
} 
void WriteDate_IT(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_IT[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_IT[Mnth]);
}