#include <pebble.h>
#include "num2words-es.h"
#include "string.h"
#include <stddef.h>
static const char* const HOUR_ES[] = {
  "doce",
  "una",
  "dos",
  "tres",
  "cuatro",
  "cinco",
  "seis",
  "siete",
  "ocho",
  "nueve",
  "diez",
  "once",
  "doce",
  "una"
};
static const char* const MIN_AUX_ES[]={
"",
"dieci",
"veinti",
"treinta",
"cuarenta",
"cincuenta"
};
static const char* const MIN_ES1[]={
"en punto",
"uno",
"dos",
"tres",
"cuatro",
"cinco",
"seis",
"siete",
"ocho",
"nueve",
"diez",
"once",
"doce",
"trece",
"catorce",
"cuarto"
};
const char* const MONTHS_ES[] = {
"Ene",
"Feb",
"Mar",
"Abr",
"May",
"Jun",
"Jul",
"Ago",
"Sep",
"Oct",
"Nov",
"Dic",
};
const char* const WEEKDAY_ES[] = {
"Dom",
"Lun",
"Mar",
"Mie",
"Jue",
"Vie",
"Sab",
};
void time_to_3words_ES(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
    //hour - line1
   //shift 1 hour the label for this minutes
  if ( minutes>35 && minutes % 5 == 0) {hours=(hours+1);                                                                
  }
  hours=hours % 12;
  strcpy(line1, HOUR_ES[hours]);
  //minute 
  //optimized for spanish
  // First do exceptions
  if (minutes==0 || minutes==20 || minutes==30 ){    
    if (minutes==0){
      strcpy(line2, MIN_ES1[0]);
    }
    else if (minutes==20){
      strcpy(line2,"y veinte");
    }
    else if (minutes==30){
      strcpy(line2,"y media");
    }
    strcpy(line3,"");
  }
  else if (minutes>35 && minutes % 5 == 0){
    strcpy(line2,"menos");
    if (minutes==40){
      strcpy(line3,"veinte");
    }
    else {
      strcpy(line3,MIN_ES1[60-minutes]);
    }
  }
  else if (minutes<16){
    strcpy(line2,"y ");
    strcat(line2,MIN_ES1[minutes]);    
    strcpy(line3,"");    
  }
  else if (minutes<60){
    strcpy(line2,MIN_AUX_ES[minutes/10]);
    if (minutes<30){
      strcpy(line3,MIN_ES1[minutes%10]);
    }
    else{
      strcpy(line3,"y ");
      strcat(line3,MIN_ES1[minutes % 10]);      
    }  
  }
  //line to mark bold
  // in spanish the hour is always in the first line 
  *LineBold=1;   
}
int Len_ES(int min){
  if (min<16 || min==20 || min==30){
    return 0;
  }
  else return 10;  
}
void PopatInit_ES(int minute, int *lenatinit){
*lenatinit=Len_ES(minute);
}
void WriteDate_ES(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_ES[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d", Dy);
  strcpy(itermonth, MONTHS_ES[Mnth]);
}
void Animations_ES(int Minute, int *LenBefore, int *LenNow, int *LenAfter){
*LenNow=Len_ES(Minute);  
if (Minute==0){	
	    *LenBefore=Len_ES(59);		
	    }
else { 
	    *LenBefore=Len_ES(Minute-1);
}
if (Minute==59){	
	*LenAfter=Len_ES(0);
	}	
else { 
	*LenAfter=Len_ES(Minute+1);
  }
}