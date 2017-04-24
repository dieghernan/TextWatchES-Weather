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
"sixteen",
"seven",
"eight",
"nine",
"twenty",
"twenty",
"twenty",
"twenty",
"twenty",
"twenty",
"twenty",
"twenty",
"twenty",
"twenty",
"half",
"thirty",
"thirty",
"thirty",
"thirty",
"thirty",
"thirty",
"thirty",
"thirty",
"thirty",
"twenty",
"fourty",
"fourty",
"fourty",
"fourty",
"quarter",
"fourty",
"fourty",
"fourty",
"fourty",
"ten",
"fifty",
"fifty",
"fifty",
"fifty",
"five",
"fifty",
"fifty",
"fifty",
"fifty"
};
const char* const MIN_EN2[]={
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"teen",
"teen",
"past",
"",
"teen",
"teen",
"teen",
"",
"one",
"two",
"three",
"four",
"five",
"six",
"seven",
"eight",
"nine",
"past",
"one",
"two",
"three",
"four",
"five",
"six",
"seven",
"eight",
"nine",
"to",
"one",
"two",
"three",
"four",
"to",
"six",
"seven",
"eight",
"nine",
"to",
"one",
"two",
"three",
"four",
"to",
"six",
"seven",
"eight",
"nine"
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
//End_Weekday
void time_to_3words_EN(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //hour - line1
   //shift 1 hour the label for this minutes
  if ( minutes>35 && minutes % 5 == 0) {hours=(hours+1);                                                                
  }
  hours=hours % 12;
if (minutes==15 || minutes==30 || minutes == 40 || minutes == 45 || minutes==50 ||  minutes==55 ){
  strcpy(line1,MIN_EN1[minutes]);
  strcpy(line2,MIN_EN2[minutes]);
  strcpy(line3, HOUR_EN[hours]); 
  *LineBold=3; 
}
else {
  strcpy(line1, HOUR_EN[hours]);
  strcpy(line2,MIN_EN1[minutes]);
  strcpy(line3,MIN_EN2[minutes]); 
  *LineBold=1;
}  
}
void PopatInit_EN(int minute, int *lenatinit){
*lenatinit=strlen(MIN_EN2[minute]);
}
void WriteDate_EN(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_EN[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_EN[Mnth]);
}
void Animations_EN(int Minute, int *LenBefore, int *LenNow, int *LenAfter){
 //Len Before
 if (Minute==0){	
	    *LenBefore=strlen(MIN_EN2[59]);		
	    }
else { 
	    *LenBefore=strlen(MIN_EN2[Minute-1]);
      }
// Len Now
*LenNow=strlen(MIN_EN2[Minute]);
//Len After
 if (Minute==59){	
	*LenAfter=strlen(MIN_EN2[0]);
	}	
else { 
	*LenAfter=strlen(MIN_EN2[Minute+1]);
  }
}