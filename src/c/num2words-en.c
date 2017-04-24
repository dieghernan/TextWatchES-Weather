#include <pebble.h>
#include "num2words-en.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_EN[] = {
  "twelve",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
  "ten",
  "eleven",
  "twelve",
  "one"
};
static const char* const MIN_AUX_EN[]={
    "",
  "teen",
  "twenty",
  "thirty",
  "fourty",
  "fifty"
};
static const char* const MIN_EN1[]={
"o'clock",
"one",
"two",
"three",
"four",
"five",
"six",
"seven",
"eight",
"nine",
"ten",
"eleven",
"twelve",
"thir",
"four",
"quarter",
"sixteen"
};
//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_EN[] = {
"Jan",
"Feb",
"Mar",
"Apr",
"May",
"Jun",
"Jul",
"Aug",
"Sep",
"Oct",
"Nov",
"Dec",
};
const char* const WEEKDAY_EN[] = {
"Sun",
"Mon",
"Tue",
"Wed",
"Thu",
"Fri",
"Sat",
};
void time_to_3words_EN(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //hour - line1
   //shift 1 hour the label for this minutes
  if ( minutes>35 && minutes % 5 == 0) {hours=(hours+1);                                                                
  }
  hours=hours % 12;
  //Exceptions first
if (minutes==15 || minutes==30 || minutes == 40 || minutes == 45 || minutes==50 ||  minutes==55 ){
  if (minutes<=30){
    if (minutes==15){
      strcpy(line1, MIN_EN1[minutes]);
    }
    else {
      strcpy(line1, "half");
    }
    strcpy(line2,"past");
  }
  else {
    if (minutes==40){
      strcpy(line1, MIN_AUX_EN[2]);
    }
    else {
      strcpy(line1, MIN_EN1[60-minutes]);
    }
    strcpy(line2,"to");    
  }  
  strcpy(line3, HOUR_EN[hours]); 
  *LineBold=3; 
}
  else {
    strcpy(line1, HOUR_EN[hours]);
    if (minutes<13 || minutes==16){
      strcpy(line2, MIN_EN1[minutes]);
      strcpy(line3, "");
    }
    else if (minutes<20){
      strcpy(line2, MIN_EN1[minutes % 10]);
      strcpy(line3,  MIN_AUX_EN[minutes/10]);    
    }
    else {
      strcpy(line2,  MIN_AUX_EN[minutes/10]);
      strcpy(line3, MIN_EN1[minutes % 10]);    
    }
    *LineBold=1;
  }  
}
int Len_EN(int min){
  if (min<13 || min==16 || min==20){
    return 0;
  }
  else return 10;  
}
void PopatInit_EN(int minute, int *lenatinit){
*lenatinit=Len_EN(minute);
}
void WriteDate_EN(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_EN[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_EN[Mnth]);
}
void Animations_EN(int Minute, int *LenBefore, int *LenNow, int *LenAfter){
*LenNow=Len_EN(Minute);  
if (Minute==0){	
	    *LenBefore=Len_EN(59);		
	    }
else { 
	    *LenBefore=Len_EN(Minute-1);
}
if (Minute==59){	
	*LenAfter=Len_EN(0);
	}	
else { 
	*LenAfter=Len_EN(Minute+1);
  }
}