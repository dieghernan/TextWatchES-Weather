#include <pebble.h>
#include "iconmap.h"
#include "string.h"


void conditions_yahoo(int YahooCode, TextLayer *IconLayer )
{  
   
  if (YahooCode ==0){text_layer_set_text(IconLayer,"a");} //tornado
else if (YahooCode ==1){text_layer_set_text(IconLayer,"b");} //tropical storm
else if (YahooCode ==2){text_layer_set_text(IconLayer,"c");} //hurricane
else if (YahooCode ==3){text_layer_set_text(IconLayer,"d");} //severe thunderstorms
else if (YahooCode ==4){text_layer_set_text(IconLayer,"d");} //thunderstorms
else if (YahooCode ==5){text_layer_set_text(IconLayer,"e");} //mixed rain and snow
else if (YahooCode ==6){text_layer_set_text(IconLayer,"e");} //mixed rain and sleet
else if (YahooCode ==7){text_layer_set_text(IconLayer,"e");} //mixed snow and sleet
else if (YahooCode ==8){text_layer_set_text(IconLayer,"f");} //freezing drizzle
else if (YahooCode ==9){text_layer_set_text(IconLayer,"g");} //drizzle
else if (YahooCode ==10){text_layer_set_text(IconLayer,"f");} //freezing rain
else if (YahooCode ==11){text_layer_set_text(IconLayer,"g");} //showers
else if (YahooCode ==12){text_layer_set_text(IconLayer,"g");} //showers
else if (YahooCode ==13){text_layer_set_text(IconLayer,"h");} //snow flurries
else if (YahooCode ==14){text_layer_set_text(IconLayer,"h");} //light snow showers
else if (YahooCode ==15){text_layer_set_text(IconLayer,"h");} //blowing snow
else if (YahooCode ==16){text_layer_set_text(IconLayer,"h");} //snow
else if (YahooCode ==17){text_layer_set_text(IconLayer,"f");} //hail
else if (YahooCode ==18){text_layer_set_text(IconLayer,"e");} //sleet
else if (YahooCode ==19){text_layer_set_text(IconLayer,"i");} //dust
else if (YahooCode ==20){text_layer_set_text(IconLayer,"j");} //foggy
else if (YahooCode ==21){text_layer_set_text(IconLayer,"k");} //haze
else if (YahooCode ==22){text_layer_set_text(IconLayer,"m");} //smoky
else if (YahooCode ==23){text_layer_set_text(IconLayer,"l");} //blustery
else if (YahooCode ==24){text_layer_set_text(IconLayer,"l");} //windy
else if (YahooCode ==25){text_layer_set_text(IconLayer,"h");} //cold
else if (YahooCode ==26){text_layer_set_text(IconLayer,"n");} //cloudy
else if (YahooCode ==27){text_layer_set_text(IconLayer,"p");} //mostly cloudy (night)
else if (YahooCode ==28){text_layer_set_text(IconLayer,"o");} //mostly cloudy (day)
else if (YahooCode ==29){text_layer_set_text(IconLayer,"p");} //partly cloudy (night)
else if (YahooCode ==30){text_layer_set_text(IconLayer,"o");} //partly cloudy (day)
else if (YahooCode ==31){text_layer_set_text(IconLayer,"q");} //clear (night)
else if (YahooCode ==32){text_layer_set_text(IconLayer,"r");} //sunny
else if (YahooCode ==33){text_layer_set_text(IconLayer,"s");} //fair (night)
else if (YahooCode ==34){text_layer_set_text(IconLayer,"t");} //fair (day)
else if (YahooCode ==35){text_layer_set_text(IconLayer,"e");} //mixed rain and hail
else if (YahooCode ==36){text_layer_set_text(IconLayer,"u");} //hot
else if (YahooCode ==37){text_layer_set_text(IconLayer,"b");} //isolated thunderstorms
else if (YahooCode ==38){text_layer_set_text(IconLayer,"b");} //scattered thunderstorms
else if (YahooCode ==39){text_layer_set_text(IconLayer,"b");} //scattered thunderstorms
else if (YahooCode ==40){text_layer_set_text(IconLayer,"g");} //scattered showers
else if (YahooCode ==41){text_layer_set_text(IconLayer,"h");} //heavy snow
else if (YahooCode ==42){text_layer_set_text(IconLayer,"h");} //scattered snow showers
else if (YahooCode ==43){text_layer_set_text(IconLayer,"h");} //heavy snow
else if (YahooCode ==44){text_layer_set_text(IconLayer,"t");} //partly cloudy
else if (YahooCode ==45){text_layer_set_text(IconLayer,"b");} //thundershowers
else if (YahooCode ==46){text_layer_set_text(IconLayer,"h");} //snow showers
else if (YahooCode ==47){text_layer_set_text(IconLayer,"b");} //isolated thundershowers
}
