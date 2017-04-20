#include <pebble.h>
#include "num2words-nn.h"
#include "string.h"

#define true 1
#define false 0

// Options
#define DEBUG false
#include <stddef.h>
#include <string.h>

/* Colloquial way of expressing the hour */

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
"fjorten",
"tretten",
"tolv",
"elleve",
"ti",
"ni",
"åtte",
"sju",
"seks",
"fem",
"fire",
"tre",
"to",
"ett",
"halv",
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
"fjorten",
"tretten",
"tolv",
"elleve",
"ti",
"ni",
"åtte",
"sju",
"seks",
"fem",
"fire",
"tre",
"to",
"ett"
};

const char* const MIN_NN2[]={
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
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"på halv",
"",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"over halv",
"på",
"på",
"på",
"på",
"på",
"på",
"på",
"på",
"på",
"på",
"på",
"på",
"på",
"på",
"på"
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
	
const char* const DAYS_NN[] = {
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


  //hour - line1
  //shift 1 hour the label for this minutes
  if ( minutes>15) {hours=(hours+1);                                                                
  }
  hours=hours % 12;

  if (minutes==0 || minutes==30){
    strcpy(line1,MIN_NN1[minutes]);
    strcpy(line2,HOUR_NN[hours]);
    strcpy(line3,MIN_NN2[minutes]); 
    *LineBold=2;
  }

  else {
    strcpy(line1,MIN_NN1[minutes]);
    strcpy(line2,MIN_NN2[minutes]);
    strcpy(line3, HOUR_NN[hours]); 
    *LineBold=3; 
  }


}

void PopatInit_NN(int minute, int *lenatinit){
*lenatinit=strlen(MIN_NN2[minute]);
}

void WriteDate_NN(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){

  strcpy(iterweekday, WEEKDAY_NN[WD]);
  strcpy(iterdate, DAYS_NN[Dy]);
  strcpy(itermonth, MONTHS_NN[Mnth]);
}

void Animations_NN(int Minute, int *LenBefore, int *LenNow, int *LenAfter){

 //Len Before
 if (Minute==0){	
	    *LenBefore=strlen(MIN_NN2[59]);		
	    }
else { 
	    *LenBefore=strlen(MIN_NN2[Minute-1]);
      }


// Len Now
*LenNow=strlen(MIN_NN2[Minute]);

//Len After
 if (Minute==59){	
	*LenAfter=strlen(MIN_NN2[0]);
	}
	
else { 
	*LenAfter=strlen(MIN_NN2[Minute+1]);
  }
}
