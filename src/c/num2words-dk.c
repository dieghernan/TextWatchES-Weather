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
"fireog",
"femog",
"seksog",
"syvog",
"otteog",
"niog",
"halv",
"niog",
"otteog",
"syvog",
"seksog",
"femog",
"fireog",
"treog",
"toog",
"énog",
"tyve",
"nitten",
"atten",
"sytten",
"seksten",
"kvart",
"fjorten",
"tretten",
"tolv",
"elleve",
"ti",
"ni",
"otte",
"syv",
"seks",
"fem",
"fire",
"tre",
"to",
"et"
};
const char* const MIN_DK2[]={
"",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"over",
"tyve over",
"tyve over",
"tyve over",
"tyve over",
"tyve over",
"tyve over",
"tyve over",
"tyve over",
"tyve over",
"",
"tyve i",
"tyve i",
"tyve i",
"tyve i",
"tyve i",
"tyve i",
"tyve i",
"tyve i",
"tyve i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i",
"i"
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
  //hour - line1
  //shift 1 hour the label for this minutes
  if ( minutes>15) {hours=(hours+1);                                                                
  }
  hours=hours % 12;
  if (minutes==0 || minutes==30){
    strcpy(line1,MIN_DK1[minutes]);
    strcpy(line2,HOUR_DK[hours]);
    strcpy(line3,MIN_DK2[minutes]); 
    *LineBold=2;
  }
  else {
    strcpy(line1,MIN_DK1[minutes]);
    strcpy(line2,MIN_DK2[minutes]);
    strcpy(line3, HOUR_DK[hours]); 
    *LineBold=3; 
  }
}
void PopatInit_DK(int minute, int *lenatinit){
*lenatinit=strlen(MIN_DK2[minute]);
}
void WriteDate_DK(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_DK[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_DK[Mnth]);
}
void Animations_DK(int Minute, int *LenBefore, int *LenNow, int *LenAfter){
 //Len Before
 if (Minute==0){	
	    *LenBefore=strlen(MIN_DK2[59]);		
	    }
else { 
	    *LenBefore=strlen(MIN_DK2[Minute-1]);
      }
// Len Now
*LenNow=strlen(MIN_DK2[Minute]);
//Len After
 if (Minute==59){	
	*LenAfter=strlen(MIN_DK2[0]);
	}	
else { 
	*LenAfter=strlen(MIN_DK2[Minute+1]);
  }
}