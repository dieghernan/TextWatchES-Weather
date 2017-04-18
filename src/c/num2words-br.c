#include <pebble.h>
#include "num2words-br.h"

#include "string.h"

#define true 1
#define false 0

// Options
#define DEBUG false
#include <stddef.h>
#include <string.h>


static const char* const HOUR_BR[] = {
"doze",
"uma",
"duas",
"três",
"quatro",
"cinco",
"seis",
"sete",
"oito",
"nove",
"dez",
"onze",
"doze",
"uma"
};

static const char* const MIN_BR1[]={
"horas",
"e um",
"e dois",
"e três",
"e quatro",
"e cinco",
"e seis",
"e sete",
"e oito",
"e nove",
"e dez",
"e onze",
"e doze",
"e treze",
"e catorze",
"quinze",
"dezasseis",
"dezassete",
"dezoito",
"dezanove",
"vinte",
"vinte",
"vinte",
"vinte",
"vinte",
"vinte",
"vinte",
"vinte",
"vinte",
"vinte",
"e meia",
"trinta",
"trinta",
"trinta",
"trinta",
"trinta",
"trinta",
"trinta",
"trinta",
"trinta",
"vinte",
"dezanove",
"dezoito",
"dezassete",
"dezasseis",
"quinze",
"catorze",
"treze",
"doze",
"onze",
"dez",
"nove",
"oito",
"sete",
"seis",
"cinco",
"quatro",
"três",
"dois",
"um"
};

const char* const MIN_BR2[]={
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
"",
"",
"",
"",
"e um",
"e dois",
"e três",
"e quatro",
"e cinco",
"e seis",
"e sete",
"e oito",
"e nove",
"",
"e um",
"e dois",
"e três",
"e quatro",
"e cinco",
"e seis",
"e sete",
"e oito",
"e nove",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as",
"para as"
};


//Init_StrMonthDat: Create strings for Months and Days
const char* const MONTHS_BR[] = {
"Jan",
"Fev",
"Mar",
"Abr",
"Mai",
"Jun",
"Jul",
"Ago",
"Set",
"Out",
"Nov",
"Dez"
};
	
const char* const DAYS_BR[] = {
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


const char* const WEEKDAY_BR[] = {
"Dom",
"Seg",
"Ter",
"Qua",
"Qui",
"Sex",
"Sab"
};


void time_to_3words_BR(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){


  //hour - line1
   //shift 1 hour the label for this minutes
  if ( minutes>39) {hours=(hours+1);                                                                
  }

  hours=hours % 12;

  if (minutes<40){  
    
    strcpy(line1, HOUR_BR[hours]);
    // Fix plural
    if (minutes==0 && hours==1){
      strcpy(line2,"hora");
    }
    else {
      strcpy(line2,MIN_BR1[minutes]);
    }     
    strcpy(line3,MIN_BR2[minutes]);
    *LineBold=1; 
  }
  else {
    strcpy(line1,MIN_BR1[minutes]);
    strcpy(line2,MIN_BR2[minutes]);
    strcpy(line3, HOUR_BR[hours]);
    *LineBold=3;     
  }
  
}

void PopatInit_BR(int minute, int *lenatinit){
*lenatinit=strlen(MIN_BR2[minute]);
}


void WriteDate_BR(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){

  strcpy(iterweekday, WEEKDAY_BR[WD]);
  strcpy(iterdate, DAYS_BR[Dy]);
  strcpy(itermonth, MONTHS_BR[Mnth]);
}

void Animations_BR(int Minute, int *LenBefore, int *LenNow, int *LenAfter){

 //Len Before
 if (Minute==0){	
	    *LenBefore=strlen(MIN_BR2[59]);		
	    }
else { 
	    *LenBefore=strlen(MIN_BR2[Minute-1]);
      }


// Len Now
*LenNow=strlen(MIN_BR2[Minute]);

//Len After
 if (Minute==59){	
	*LenAfter=strlen(MIN_BR2[0]);
	}
	
else { 
	*LenAfter=strlen(MIN_BR2[Minute+1]);
  }
}
//End_Weekday