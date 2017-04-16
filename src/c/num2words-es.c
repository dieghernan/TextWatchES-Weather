#include <pebble.h>
#include "num2words-es.h"
#include "string.h"

#define true 1
#define false 0

// Options
#define DEBUG false
#include <stddef.h>
#include <string.h>


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
static const char* const MIN_ES1[]={
"en punto",
"y uno",
"y dos",
"y tres",
"y cuatro",
"y cinco",
"y seis",
"y siete",
"y ocho",
"y nueve",
"y diez",
"y once",
"y doce",
"y trece",
"y catorce",
"y cuarto",
"dieci",
"dieci",
"dieci",
"dieci",
"veinte",
"veinti",
"veinti",
"veinti",
"veinti",
"veinti",
"veinti",
"veinti",
"veinti",
"veinti",
"y media",
"treinta",
"treinta",
"treinta",
"treinta",
"treinta",
"treinta",
"treinta",
"treinta",
"treinta",
"menos",
"cuarenta",
"cuarenta",
"cuarenta",
"cuarenta",
"menos",
"cuarenta",
"cuarenta",
"cuarenta",
"cuarenta",
"menos",
"cincuenta",
"cincuenta",
"cincuenta",
"cincuenta",
"menos",
"cincuenta",
"cincuenta",
"cincuenta",
"cincuenta"
};

const char* const MIN_ES2[]={
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
"",
"",
"seis",
"siete",
"ocho",
"nueve",
"",
"uno",
"dos",
"tres",
"cuatro",
"cinco",
"seis",
"siete",
"ocho",
"nueve",
"",
"y uno",
"y dos",
"y tres",
"y cuatro",
"y cinco",
"y seis",
"y siete",
"y ocho",
"y nueve",
"veinte ",
"y uno",
"y dos",
"y tres",
"y cuatro",
"cuarto ",
"y seis",
"y siete",
"y ocho",
"y nueve",
"diez ",
"y uno",
"y dos",
"y tres",
"y cuatro",
"cinco ",
"y seis",
"y siete",
"y ocho",
"y nueve",
"en punto"
};


//Init_StrMonthDat: Create strings for Months and Days
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
	
const char* const DAYS_ES[] = {
"",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"10",
"11",
"12",
"13",
"14",
"15",
"16",
"17",
"18",
"19",
"20",
"21",
"22",
"23",
"24",
"25",
"26",
"27",
"28",
"29",
"30",
"31",
};
//End_StrMonthDat


const char* const WEEKDAY_ES[] = {
"Dom",
"Lun",
"Mar",
"Mie",
"Jue",
"Vie",
"Sab",
};
//End_Weekday


void time_to_3words_ES(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){

  //hour - line1
   //shift 1 hour the label for this minutes
  if ( minutes>35 && minutes % 5 == 0) {hours=(hours+1);                                                                
  }
  hours=hours % 12;
  strcpy(line1, HOUR_ES[hours]);
  //minute 
  //optimized for spanish
  strcpy(line2,MIN_ES1[minutes]);
  strcpy(line3,MIN_ES2[minutes]);
  
  //line to mark bold
  // in spanish the hour is always in the first line
 
  *LineBold=1; 
  
}

void PopatInit_ES(int minute, int *lenatinit){
*lenatinit=strlen(MIN_ES2[minute]);
}

void WriteDate_ES(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){

  strcpy(iterweekday, WEEKDAY_ES[WD]);
  strcpy(iterdate, DAYS_ES[Dy]);
  strcpy(itermonth, MONTHS_ES[Mnth]);
}

void Animations_ES(int Minute, int *LenBefore, int *LenNow, int *LenAfter){

 //Len Before
 if (Minute==0){	
	    *LenBefore=strlen(MIN_ES2[59]);		
	    }
else { 
	    *LenBefore=strlen(MIN_ES2[Minute-1]);
      }


// Len Now
*LenNow=strlen(MIN_ES2[Minute]);

//Len After
 if (Minute==59){	
	*LenAfter=strlen(MIN_ES2[0]);
	}
	
else { 
	*LenAfter=strlen(MIN_ES2[Minute+1]);
  }
}
