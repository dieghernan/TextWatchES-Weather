#include <pebble.h>
#include "num2words-de.h"
#include "string.h"

#define true 1
#define false 0

// Options
#define DEBUG false
#include <stddef.h>
#include <string.h>

/* Colloquial way of expressing the hour */

static const char* const HOUR_DE[] = {
  "zwölf",
  "eins",
  "zwei",
  "drei",
  "vier",
  "fünf",
  "sechs",
  "sieben",
  "acht",
  "neun",
  "zehn",
  "elf",
  "zwölf",
  "eins"
};
static const char* const MIN_DE1[]={
"Uhr",
"eins",
"zwei",
"drei",
"vier",
"fünf",
"sechs",
"sieben",
"acht",
"neun",
"zehn",
"elf",
"zwölf",
"dreizehn",
"vierzehn",
"Viertel",
"sechzehn",
"siebzehn",
"achtzehn",
"neunzehn",
"zwanzig",
"neun",
"acht",
"sieben",
"sechs",
"fünf",
"vier",
"drei",
"zwei",
"eins",
"halb",
"eins",
"zwei",
"drei",
"vier",
"fünf",
"sechs",
"sieben",
"acht",
"neun",
"zwanzig",
"neunzehn",
"achtzehn",
"siebzehn",
"sechzehn",
"Viertel",
"vierzehn",
"dreizehn",
"zwölf",
"elf",
"zehn",
"neun",
"acht",
"sieben",
"sechs",
"fünf",
"vier",
"drei",
"zwei",
"eins"
};

const char* const MIN_DE2[]={
"",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"nach",
"vor halb",
"vor halb",
"vor halb",
"vor halb",
"vor halb",
"vor halb",
"vor halb",
"vor halb",
"vor halb",
"",
"nach halb",
"nach halb",
"nach halb",
"nach halb",
"nach halb",
"nach halb",
"nach halb",
"nach halb",
"nach halb",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor",
"vor"
};

//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_DE[] = {
"Jan.",
"Feb.",
"Mrz.",
"Apr.",
"Mai.",
"Jun.",
"Jul.",
"Aug.",
"Sep.",
"Okt.",
"Nov.",
"Dez.",
};
	
const char* const DAYS_DE[] = {
"",
"1.",
"2.",
"3.",
"4.",
"5.",
"6.",
"7.",
"8.",
"9.",
"10.",
"11.",
"12.",
"13.",
"14.",
"15.",
"16.",
"17.",
"18.",
"19.",
"20.",
"21.",
"22.",
"23.",
"24.",
"25.",
"26.",
"27.",
"28.",
"29.",
"30.",
"31.",
};
//End_StrMonthDat


const char* const WEEKDAY_DE[] = {
"So.",
"Mo.",
"Di.",
"Mi.",
"Do.",
"Fr.",
"Sa.",
};
//End_Weekday


void time_to_3words_DE(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){


  //hour - line1
  //shift 1 hour the label for this minutes
  if ( minutes>20) {hours=(hours+1);                                                                
  }
  hours=hours % 12;

  if (minutes==0 ){
    strcpy(line1, HOUR_DE[hours]);
    strcpy(line2,MIN_DE1[minutes]);
    strcpy(line3,MIN_DE2[minutes]); 
    *LineBold=1;
  }
    else if (minutes==30){
      
    strcpy(line1,MIN_DE1[minutes]);
    strcpy(line2, HOUR_DE[hours]);
    strcpy(line3,MIN_DE2[minutes]);
    *LineBold=2; 
      
    
  }
  else {
    strcpy(line1,MIN_DE1[minutes]);
    strcpy(line2,MIN_DE2[minutes]);
    strcpy(line3, HOUR_DE[hours]); 
    *LineBold=3; 
  }


}

void PopatInit_DE(int minute, int *lenatinit){
*lenatinit=strlen(MIN_DE2[minute]);
}

void WriteDate_DE(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){

  strcpy(iterweekday, WEEKDAY_DE[WD]);
  strcpy(iterdate, DAYS_DE[Dy]);
  strcpy(itermonth, MONTHS_DE[Mnth]);
}

void Animations_DE(int Minute, int *LenBefore, int *LenNow, int *LenAfter){

 //Len Before
 if (Minute==0){	
	    *LenBefore=strlen(MIN_DE2[59]);		
	    }
else { 
	    *LenBefore=strlen(MIN_DE2[Minute-1]);
      }


// Len Now
*LenNow=strlen(MIN_DE2[Minute]);

//Len After
 if (Minute==59){	
	*LenAfter=strlen(MIN_DE2[0]);
	}
	
else { 
	*LenAfter=strlen(MIN_DE2[Minute+1]);
  }
}
