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
"e una",
"e due",
"e tre",
"e quattro",
"e cinque",
"e sei",
"e sette",
"e otto",
"e nove",
"e dieci",
"e undici",
"e dodici",
"e tredici",
"e quattor",
"e un quarto",
"e sedici",
"e dicias",
"e dici",
"e dician",
"e venti",
"e ventuno",
"e ventidue",
"e ventitré",
"e venti",
"e venti",
"e venti",
"e venti",
"e venti",
"e venti",
"e mezzo",
"e trentuno",
"e trentadue",
"e trentatré",
"e trenta",
"e trenta",
"e trenta",
"e trenta",
"e trenta",
"e trenta",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
"meno",
""
};
const char* const MIN_IT2[]={
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
"",
"dici",
"",
"",
"sette",
"otto",
"nove",
"",
"",
"",
"",
"quattro",
"cinque",
"sei",
"sette",
"otto",
"nove",
"",
"",
"",
"",
"quattro",
"cinque",
"sei",
"sette",
"otto",
"nove",
"venti",
"diciannove",
"diciotto",
"diciassette",
"sedici",
"un quarto",
"quattordici",
"tredici",
"dodici",
"undici",
"dieci",
"nove",
"otto",
"sette",
"sei",
"cinque",
"quattro",
"tre",
"due",
"una",
""
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
  //hour - line1
   //shift 1 hour the label for this minutes
  if ( minutes>39) {
    hours=(hours+1);                                                                
  }
  if (hours>13){
  hours=hours % 12;
  }
  strcpy(line1, HOUR_IT[hours]);
  //minute 
  //optimized for italian
  strcpy(line2,MIN_IT1[minutes]);
  strcpy(line3,MIN_IT2[minutes]);  
  // in italianthe hour is always in the first line 
  *LineBold=1;   
}
void PopatInit_IT(int minute, int *lenatinit){
*lenatinit=strlen(MIN_IT2[minute]);
}
void WriteDate_IT(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_IT[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_IT[Mnth]);
}
void Animations_IT(int Minute, int *LenBefore, int *LenNow, int *LenAfter){
 //Len Before
 if (Minute==0){	
	    *LenBefore=strlen(MIN_IT2[59]);		
	    }
else { 
	    *LenBefore=strlen(MIN_IT2[Minute-1]);
      }
// Len Now
*LenNow=strlen(MIN_IT2[Minute]);
//Len After
 if (Minute==59){	
	*LenAfter=strlen(MIN_IT2[0]);
	}	
else { 
	*LenAfter=strlen(MIN_IT2[Minute+1]);
  }
}