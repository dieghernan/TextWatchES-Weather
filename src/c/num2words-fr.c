#include <pebble.h>
#include "num2words-fr.h"
#include "string.h"

#define true 1
#define false 0

// Options
#define DEBUG false
#include <stddef.h>
#include <string.h>


static const char* const HOUR_FR[] = {
"douze",
"une",
"deux",
"trois",
"quatre",
"cinq",
"six",
"sept",
"huit",
"neuf",
"dix",
"onze",
"douze",
"une"
};

static const char* const MIN_FR1[]={
"pile",
"et une",
"deux",
"trois",
"quatre",
"cinq",
"six",
"sept",
"huit",
"neuf",
"dix",
"onze",
"douze",
"treize",
"quatorze",
"et quart",
"seize",
"dix",
"dix",
"dix",
"vingt",
"vingt",
"vingt",
"vingt",
"vingt",
"vingt",
"vingt",
"vingt",
"vingt",
"vingt",
"et demie",
"trente",
"trente",
"trente",
"trente",
"trente",
"trente",
"trente",
"trente",
"trente",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins",
"moins"
};

const char* const MIN_FR2[]={
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
"",
"sept",
"huit",
"neuf",
"",
"et une",
"deux",
"trois",
"quatre",
"cinq",
"six",
"sept",
"huit",
"neuf",
"",
"et une",
"deux",
"trois",
"quatre",
"cinq",
"six",
"sept",
"huit",
"neuf",
"vingt",
"dix-neuf",
"dix-huit",
"dix-sept",
"seize",
"le quart",
"quatorze",
"treize",
"douze",
"onze",
"dix",
"neuf",
"huit",
"sept",
"six",
"cinq",
"quatre",
"trois",
"deux",
"une"
};


//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_FR[] = {
"Jan",
"Fév",
"Mar",
"Avr",
"Mai",
"Jui",
"Jui",
"Aoû",
"Sep",
"Oct",
"Nov",
"Déc"
};
	
const char* const DAYS_FR[] = {
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


const char* const WEEKDAY_FR[] = {
"Dim",
"Lun",
"Mar",
"Mer",
"Jeu",
"Ven",
"Sam",
};
//End_Weekday


void time_to_3words_FR(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){

  //hour - line1
   //shift 1 hour the label for this minutes
  if ( minutes>39) {hours=(hours+1);                                                                
  }
  hours=hours % 12;
  strcpy(line1, HOUR_FR[hours]);
  //minute 
  //optimized for spanish
  strcpy(line2,MIN_FR1[minutes]);
  strcpy(line3,MIN_FR2[minutes]);
  
  //line to mark bold
  // in french the hour is always in the first line
 
  *LineBold=1; 
  
}

void PopatInit_FR(int minute, int *lenatinit){
*lenatinit=strlen(MIN_FR2[minute]);
}

void WriteDate_FR(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){

  strcpy(iterweekday, WEEKDAY_FR[WD]);
  strcpy(iterdate, DAYS_FR[Dy]);
  strcpy(itermonth, MONTHS_FR[Mnth]);
}

void Animations_FR(int Minute, int *LenBefore, int *LenNow, int *LenAfter){

 //Len Before
 if (Minute==0){	
	    *LenBefore=strlen(MIN_FR2[59]);		
	    }
else { 
	    *LenBefore=strlen(MIN_FR2[Minute-1]);
      }


// Len Now
*LenNow=strlen(MIN_FR2[Minute]);

//Len After
 if (Minute==59){	
	*LenAfter=strlen(MIN_FR2[0]);
	}
	
else { 
	*LenAfter=strlen(MIN_FR2[Minute+1]);
  }
}
