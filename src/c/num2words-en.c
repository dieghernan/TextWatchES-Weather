#include <pebble.h>
#include "num2words-en.h"
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

static const char* const MIN_ES2[]={
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
"y nueve"
};

void time_to_3words(int hours, int minutes, char *line1, char *line2, char *line3, size_t length){

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
    
  
}
