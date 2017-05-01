#include <pebble.h>
#include "num2words-de.h"
#include "string.h"
#include <stddef.h>
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
  "zwanzig"
};
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
  "Dez."
};
const char* const WEEKDAY_DE[] = {
  "So.",
  "Mo.",
  "Di.",
  "Mi.",
  "Do.",
  "Fr.",
  "Sa."
};
void time_to_3words_DE(int hours, int minutes, int *LineBold,char *line1, char *line2, char *line3){
  //Clean line3 at init
  strcpy(line3, "");
  //shift 1 hour the label for this minutes
  if ( minutes>20) {hours=(hours+1);}
  hours=hours % 12;
  // Exceptions first
  if (minutes==0 ){
    strcpy(line1, HOUR_DE[hours]);
    strcpy(line2,MIN_DE1[minutes]);
    *LineBold=1;
  }
  else if (minutes==30){
    strcpy(line1,"halb");
    strcpy(line2, HOUR_DE[hours]);
    *LineBold=2;
  }
  else {
    if (minutes<=20) {
      strcpy(line1,MIN_DE1[minutes]);
      strcpy(line2,"nach");
    }
    else if (minutes<=30) {
      strcpy(line1,MIN_DE1[10-minutes%10]);
      strcpy(line2,"vor halb");
    }
    else if (minutes<40) {
      strcpy(line1,MIN_DE1[minutes%10]);
      strcpy(line2,"nach halb");
    }
    else {
      strcpy(line1,MIN_DE1[60-minutes]);
      strcpy(line2,"vor");
    }
    strcpy(line3, HOUR_DE[hours]);
    *LineBold=3;
  }
}
void WriteDate_DE(int WD, int Mnth, int Dy, char *iterweekday, char *iterdate, char *itermonth ){
  strcpy(iterweekday, WEEKDAY_DE[WD]);
  snprintf(iterdate, sizeof(iterdate), "%d.", Dy);
  strcpy(itermonth, MONTHS_DE[Mnth]);
}