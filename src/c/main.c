#include <pebble.h>
#include "main.h"
#define BUFFER_SIZE 20
//Include languages
#include "num2words-es.h"
#include "num2words-en.h"
#include "num2words-de.h"
#include "num2words-fr.h"
#include "num2words-br.h"
#include "num2words-it.h"
#include "num2words-nn.h"
#include "num2words-dk.h"
// 1. Define structures////
// Struct Line
typedef struct {
  TextLayer *currentLayer;
  TextLayer *nextLayer;
  PropertyAnimation *currentAnimation;
  PropertyAnimation *nextAnimation;
} Line;
Line line1;
Line line2;
Line line3;
// Layers
static Window *s_main_window;
Layer *back_layer;
Layer *scroll;
// Chars
static char line1Str[2][BUFFER_SIZE];
static char line2Str[2][BUFFER_SIZE];
static char line3Str[2][BUFFER_SIZE];
// Weather information
char tempstring[44], condstringday[44],condstringnight[44];
char textbefore1[BUFFER_SIZE], textbefore2[BUFFER_SIZE],textbefore3[BUFFER_SIZE];
//Fonts
static GFont FontCond;
static GFont Bold;
static GFont BoldReduced1;
static GFont BoldReduced2;
static GFont BoldReduced3;
static GFont Light;
static GFont LightReduced1;
static GFont LightReduced2;
static GFont LightReduced3;
static GFont FontWDay;
static GFont FontDate;
static GFont FontSymbol;
//Others
PropertyAnimation *scroll_down;
PropertyAnimation *scroll_up;
static bool AtInit;
static bool PopUpNow=false;
GRect bounds;
static int offsetpebble, s_loop,s_countdown;
static int mast_hour, mast_min, mast_mon, mast_wday, mast_day;
//////Init Configuration///
//Init Clay
ClaySettings settings;
// Initialize the default settings
static void prv_default_settings() {
  settings.BackgroundColor = GColorOxfordBlue;
  settings.ForegroundColor = GColorWhite;
  settings.BackgroundColorNight=GColorWhite;
  settings.ForegroundColorNight=GColorOxfordBlue;
  settings.NightTheme=false;
  settings.WeatherUnit = false;
  settings.LangKey=1;
  settings.DateFormat=1;
  settings.IsNightNow=false;
  settings.HourSunrise =600;
  settings.HourSunset =1700;
  settings.GPSOn=false;
  settings.UpSlider=30;
  settings.DisplayTemp=false;
  settings.BTOn=true;
  settings.FuzzyMode=false;
  settings.BatteryBar=false;
  settings.AnimMode=true;
}
//////End Configuration///
static void bluetooth_callback(bool connected) {  
  settings.BTOn=connection_service_peek_pebble_app_connection();
  layer_mark_dirty(back_layer);
}
//////Lang Selector ///
void writetimeto3words(int hour_i,int minute_i,int *linebold_i,char *line1_i, char *line2_i, char *line3_i, int lang_i){
  if (lang_i==1){ //Spanish
    time_to_3words_ES(hour_i , minute_i,linebold_i ,line1_i, line2_i, line3_i);
  }
  else if (lang_i==2){ //English
    time_to_3words_EN(hour_i , minute_i,linebold_i ,line1_i, line2_i, line3_i);
  }
  else if (lang_i==3){ //German
    time_to_3words_DE(hour_i , minute_i,linebold_i ,line1_i, line2_i, line3_i);
  }
  else if (lang_i==4){ //French
    time_to_3words_FR(hour_i , minute_i,linebold_i ,line1_i, line2_i, line3_i);
  }
  else if (lang_i==5){ //PortugueseBR
    time_to_3words_BR(hour_i , minute_i,linebold_i ,line1_i, line2_i, line3_i);
  }
  else if (lang_i==6){ //Italian
    time_to_3words_IT(hour_i , minute_i,linebold_i ,line1_i, line2_i, line3_i);
  }
  else if (lang_i==7){ //Norwegian
    time_to_3words_NN(hour_i , minute_i,linebold_i ,line1_i, line2_i, line3_i);
  }
  else if (lang_i==8){ //Danish
    time_to_3words_DK(hour_i , minute_i,linebold_i ,line1_i, line2_i, line3_i);
  }
}
void writedatelang(int week,int Mon,int Day, char* iterwd,char * iterdat, char * itermon, int Lang){
  if (Lang==1){ //Spanish
    WriteDate_ES(week , Mon ,Day, iterwd ,iterdat,itermon);
  }
  else if (Lang==2){ //English
    WriteDate_EN(week , Mon ,Day, iterwd ,iterdat,itermon);
  }
  else if (Lang==3){ //German
    WriteDate_DE(week , Mon ,Day, iterwd ,iterdat,itermon);
  }
  else if (Lang==4){ //French
    WriteDate_FR(week , Mon ,Day, iterwd ,iterdat,itermon);
  }
  else if (Lang==5){ //Portuguese - BR
    WriteDate_BR(week , Mon ,Day, iterwd ,iterdat,itermon);
  }
  else if (Lang==6){ //Italian
    WriteDate_IT(week , Mon ,Day, iterwd ,iterdat,itermon);
  }
  else if (Lang==7){ //Norwegian
    WriteDate_NN(week , Mon ,Day, iterwd ,iterdat,itermon);
  }
  else if (Lang==8){ //Danish
    WriteDate_DK(week , Mon ,Day, iterwd ,iterdat,itermon);
  }
}
//////End Lang Selector///
//////Define Function ///
static int limit(int nline){
  int isround=PBL_IF_ROUND_ELSE(1, 0);
  if (isround==1){
    if (nline==1){return 130;}
    else if (nline==2){return 160;}
    else return 150;
  }
  else return 123;
}
// Callback for js request
void request_watchjs(){
  //Starting loop at 0
  s_loop=0;
  // Begin dictionary
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  // Add a key-value pair
  dict_write_uint8(iter, 0, 0);
  // Send the message!
  app_message_outbox_send();
}
///BT Connection
static GColor ColorSelect(bool isactive, bool gpsstate, bool isnight, GColor ColorDay, GColor ColorNight){
  if (isactive && isnight && gpsstate){
    return ColorNight;
  }
  else {
    return ColorDay;
  }
}
//////End Function ///
////Init: Animations procs//
void makeScrollUpNow(){
  GRect from = layer_get_bounds((Layer *)scroll);
  GRect to = layer_get_bounds((Layer *)scroll);
  GRect rect = layer_get_bounds((Layer *)scroll);
  if(rect.origin.y == 21){
    from.origin.y = 0;
    to.origin.y = -21;
  }
  else {
    from.origin.y = 21;
    to.origin.y = 0;
  }
  scroll_down = property_animation_create_layer_frame((Layer *)scroll, &from, &to);
  animation_set_duration(property_animation_get_animation(scroll_down), 800);
  animation_set_curve(property_animation_get_animation(scroll_down), AnimationCurveEaseOut);
  animation_schedule(property_animation_get_animation(scroll_down)); 
}
void makeScrollDown(){
  GRect from = layer_get_bounds((Layer *)scroll);
  GRect to = layer_get_bounds((Layer *)scroll);
  GRect rect = layer_get_bounds((Layer *)scroll);
  if(rect.origin.y == 21){
    from.origin.y = -21;
    to.origin.y = 0;
  }
  else {
    from.origin.y = 0;
    to.origin.y = 21;
  }
  scroll_down = property_animation_create_layer_frame((Layer *)scroll, &from, &to);
  animation_set_duration(property_animation_get_animation(scroll_down), 800);
  animation_set_delay(property_animation_get_animation(scroll_down), 600);
  animation_set_curve(property_animation_get_animation(scroll_down), AnimationCurveEaseOut);
  animation_schedule(property_animation_get_animation(scroll_down));  
}
// Text Animation handler
void animationStoppedHandler(struct Animation *animation, bool finished, void *context) {
  Layer *current = (Layer *)context;
  GRect rect = layer_get_frame(current);
  rect.origin.x = bounds.size.w;
  layer_set_frame(current, rect);
}
// Animate text line
void makeAnimationsForLayers(Line *line, TextLayer *current, TextLayer *next) {
  if (line->nextAnimation != NULL)
    property_animation_destroy(line->nextAnimation);
  if (line->currentAnimation != NULL)
    property_animation_destroy(line->currentAnimation);
  GRect rect = layer_get_frame((Layer *)next);
  rect.origin.x -= bounds.size.w;
  line->nextAnimation = property_animation_create_layer_frame((Layer *)next, NULL, &rect);
  animation_set_duration(property_animation_get_animation(line->nextAnimation), 400);
  if (PopUpNow){
    animation_set_delay(property_animation_get_animation(line->nextAnimation), 1000);
  }
  
  animation_set_curve(property_animation_get_animation(line->nextAnimation), AnimationCurveEaseOut);
  animation_schedule(property_animation_get_animation(line->nextAnimation));
  GRect rect2 = layer_get_frame((Layer *)current);
  rect2.origin.x -= bounds.size.w;
  line->currentAnimation = property_animation_create_layer_frame((Layer *)current, NULL, &rect2);
  animation_set_duration(property_animation_get_animation(line->currentAnimation), 400);
  if (PopUpNow){
    animation_set_delay(property_animation_get_animation(line->currentAnimation), 1000);
  }
  animation_set_curve(property_animation_get_animation(line->currentAnimation), AnimationCurveEaseOut);
  animation_set_handlers(property_animation_get_animation(line->currentAnimation), (AnimationHandlers) {
    .stopped = (AnimationStoppedHandler)animationStoppedHandler},
                         current);
  animation_schedule(property_animation_get_animation(line->currentAnimation));
}

void NoAnimationsForLayers(Line *line, TextLayer *current, TextLayer *next) {
  if (line->nextAnimation != NULL)
    property_animation_destroy(line->nextAnimation);
  if (line->currentAnimation != NULL)
    property_animation_destroy(line->currentAnimation);
  GRect rect = layer_get_frame((Layer *)next);
  rect.origin.x -= bounds.size.w;
  line->nextAnimation = property_animation_create_layer_frame((Layer *)next, NULL, &rect);
  animation_set_duration(property_animation_get_animation(line->nextAnimation), 0);
  animation_set_curve(property_animation_get_animation(line->nextAnimation), AnimationCurveEaseOut);
  animation_schedule(property_animation_get_animation(line->nextAnimation));
  GRect rect2 = layer_get_frame((Layer *)current);
  rect2.origin.x -= bounds.size.w;
  line->currentAnimation = property_animation_create_layer_frame((Layer *)current, NULL, &rect2);
  animation_set_duration(property_animation_get_animation(line->currentAnimation), 0);
  animation_set_curve(property_animation_get_animation(line->currentAnimation), AnimationCurveEaseOut);
  animation_set_handlers(property_animation_get_animation(line->currentAnimation), (AnimationHandlers) {
    .stopped = (AnimationStoppedHandler)animationStoppedHandler},
                         current);
  animation_schedule(property_animation_get_animation(line->currentAnimation));
}
// Pop down to center before initial display when only 2 lines of text
void makePopDown(){
  GRect rect = layer_get_bounds((Layer *)scroll);
  rect.origin.y = 21;
  layer_set_bounds(scroll, rect);
}
void makePopUp(){
  GRect rect = layer_get_bounds((Layer *)scroll);
  rect.origin.y = 0;
  layer_set_bounds(scroll, rect);
}
////End: Animations procs//
////Init: Layer updating////
//Vertical alignment
static void verticalAlignTextLayer(TextLayer *layer, int inity) {
  GRect frame = layer_get_frame(text_layer_get_layer(layer));
  GSize content = text_layer_get_content_size(layer);
  // Adjust position of the layer so visually all the text are aligned to the bottom
  // This is neccesary cuz Pebble works aligning to the top - doesnt like how it looks
  int offsetv;
  //Handle nulls, no need to change
  if (content.h==0){
    offsetv=0;
  }
  else {
    offsetv=39-content.h;
  }
  layer_set_frame(text_layer_get_layer(layer),
                  GRect(frame.origin.x, inity + offsetv, frame.size.w, frame.size.h));
}
void sizeandbold(TextLayer *linelayer, int linr, int linb) {
  if (linr==linb){text_layer_set_font(linelayer,Bold);}
  else {text_layer_set_font(linelayer,Light);}
  int evlimit=limit(linr);
  const char * textonlayer;
  textonlayer=text_layer_get_text(linelayer);
  char textget[BUFFER_SIZE];
  snprintf(textget, sizeof(textget), "%s",textonlayer);
  GSize sizetext=text_layer_get_content_size(linelayer);
  int width=sizetext.w;
  if (linr==linb){
    if (width>evlimit){
      text_layer_set_font(linelayer,BoldReduced1);
      GSize sizetext2=text_layer_get_content_size(linelayer);
      int width2=sizetext2.w;
      if (width2>evlimit ){
        text_layer_set_font(linelayer,BoldReduced2);
        GSize sizetext3=text_layer_get_content_size(linelayer);
        int width3=sizetext3.w;
        if (width3>evlimit){
          text_layer_set_font(linelayer, BoldReduced3);
        }
      }
    }
  }
  else {
    if (width>evlimit){
      text_layer_set_font(linelayer,LightReduced1);
      GSize sizetext2=text_layer_get_content_size(linelayer);
      int width2=sizetext2.w;
      if (width2>evlimit ){
        text_layer_set_font(linelayer,LightReduced2);
        GSize sizetext3=text_layer_get_content_size(linelayer);
        int width3=sizetext3.w;
        if (width3>evlimit){
          text_layer_set_font(linelayer, LightReduced3);
        }
      }
    }
  }
  int offsetline=0;
  if (linr==2){
    offsetline=37;
  }
  else if (linr==3){
    offsetline=74;
  }
  //Adjust vertical alignment
  verticalAlignTextLayer(linelayer, offsetpebble+offsetline);
};
// Update text line
void updateLineStatic(Line *line, char lineStr[2][BUFFER_SIZE], char *value, int linref, int linbold) {
  TextLayer *next, *current;
  GRect rect = layer_get_frame((Layer *)line->currentLayer);
  current = (rect.origin.x == 0) ? line->currentLayer : line->nextLayer;
  next = (current == line->currentLayer) ? line->nextLayer : line->currentLayer;
  // Update correct text only
  if (current == line->currentLayer) {
    memset(lineStr[1], 0, BUFFER_SIZE);
    memcpy(lineStr[1], value, strlen(value));
    text_layer_set_text(next, lineStr[1]);
  }
  else {
    memset(lineStr[0], 0, BUFFER_SIZE);
    memcpy(lineStr[0], value, strlen(value));
    text_layer_set_text(next, lineStr[0]);
  }
  sizeandbold(next,linref,linbold);
  text_layer_set_text(current, "");
  NoAnimationsForLayers(line, current, next);
}
void updateLineTo(Line *line, char lineStr[2][BUFFER_SIZE], char *value, int linref, int linbold) {
  TextLayer *next, *current;
  GRect rect = layer_get_frame((Layer *)line->currentLayer);
  current = (rect.origin.x == 0) ? line->currentLayer : line->nextLayer;
  next = (current == line->currentLayer) ? line->nextLayer : line->currentLayer;
  // Update correct text only
  if (current == line->currentLayer) {
    memset(lineStr[1], 0, BUFFER_SIZE);
    memcpy(lineStr[1], value, strlen(value));
    text_layer_set_text(next, lineStr[1]);
  }
  else {
    memset(lineStr[0], 0, BUFFER_SIZE);
    memcpy(lineStr[0], value, strlen(value));
    text_layer_set_text(next, lineStr[0]);
  }
  sizeandbold(next,linref,linbold);
  makeAnimationsForLayers(line, current, next);
}
bool checkupdate(char text1[BUFFER_SIZE],char text2[BUFFER_SIZE]){
  if (strcmp(text1,text2)==0){
    return false ;
  }
  else {
    return true;
  }
}
////End: Layer updating////
////Init: Layer formatting//
// Configure line of text
void TextColorFormatting(){
  window_set_background_color(s_main_window,ColorSelect(settings.NightTheme, true,settings.IsNightNow,settings.BackgroundColor, settings.BackgroundColorNight));
  text_layer_set_text_color(line1.currentLayer, ColorSelect(settings.NightTheme, true, settings.IsNightNow, settings.ForegroundColor, settings.ForegroundColorNight));
  text_layer_set_text_color(line1.nextLayer, ColorSelect(settings.NightTheme, true, settings.IsNightNow, settings.ForegroundColor, settings.ForegroundColorNight));
  text_layer_set_text_color(line2.currentLayer,ColorSelect(settings.NightTheme, true, settings.IsNightNow, settings.ForegroundColor, settings.ForegroundColorNight));
  text_layer_set_text_color(line2.nextLayer, ColorSelect(settings.NightTheme, true, settings.IsNightNow, settings.ForegroundColor, settings.ForegroundColorNight));
  text_layer_set_text_color(line3.currentLayer, ColorSelect(settings.NightTheme, true, settings.IsNightNow, settings.ForegroundColor, settings.ForegroundColorNight));
  text_layer_set_text_color(line3.nextLayer, ColorSelect(settings.NightTheme,true, settings.IsNightNow, settings.ForegroundColor, settings.ForegroundColorNight));  
}
void configureLineLayer(TextLayer *textlayer) {
  text_layer_set_text_color(textlayer, ColorSelect(settings.NightTheme, settings.GPSOn, settings.IsNightNow, settings.ForegroundColor, settings.ForegroundColorNight));
  text_layer_set_background_color(textlayer, GColorClear);
  text_layer_set_text_alignment(textlayer, GTextAlignmentCenter);
}
////End: Layer formatting//
///// Init: Updating time and date////
// Update screen based on new time
void display_static(){
  // The current time text will be stored in the following 3 strings
  char textLine1[BUFFER_SIZE];
  char textLine2[BUFFER_SIZE];
  char textLine3[BUFFER_SIZE];
  int LineToPutinBold=0;
  // Language settings
  writetimeto3words(mast_hour, mast_min, &LineToPutinBold, textLine1, textLine2, textLine3,settings.LangKey);
   // Set Up and Down animations
  int LBef=strlen(textbefore3);
  int Lnow=strlen(textLine3);
  // Animations
  if (AtInit){
    if (Lnow==0){
      makePopDown();
    }    
  }
  else if(LBef>0 && Lnow==0 ){
    makePopDown();    
  }
  else if(LBef==0 && Lnow > 0 ){
    makePopUp();   
  }
  AtInit=false;
  //Update lines
  if (checkupdate(textbefore1,textLine1)) {
    updateLineStatic(&line1, line1Str, textLine1,1,LineToPutinBold);
  }
  if (checkupdate(textbefore2,textLine2)) {
    updateLineStatic(&line2, line2Str, textLine2,2,LineToPutinBold);
  }
  if (checkupdate(textbefore3,textLine3)) {
    updateLineStatic(&line3, line3Str, textLine3,3,LineToPutinBold);
  }
    // Save
  strcpy(textbefore1, textLine1);
  strcpy(textbefore2, textLine2);
  strcpy(textbefore3, textLine3);
}
void display_animated(){
  // The current time text will be stored in the following 3 strings
  char textLine1[BUFFER_SIZE];
  char textLine2[BUFFER_SIZE];
  char textLine3[BUFFER_SIZE];
  int LineToPutinBold=0;
  // Language settings
  writetimeto3words(mast_hour, mast_min, &LineToPutinBold, textLine1, textLine2, textLine3,settings.LangKey);
   // Set Up and Down animations
  int LBef=strlen(textbefore3);
  int Lnow=strlen(textLine3);
  // Animations
  if (AtInit){
    if (Lnow==0){
      makePopDown();
    }    
  }
  else if(LBef>0 && Lnow==0 ){
    makeScrollDown();
  }
  else if(LBef==0 && Lnow > 0 ){
    PopUpNow=true;
    makeScrollUpNow();
  }
  AtInit=false;
  //Update lines
  if (checkupdate(textbefore1,textLine1)) {
    updateLineTo(&line1, line1Str, textLine1,1,LineToPutinBold);
  }
  if (checkupdate(textbefore2,textLine2)) {
    updateLineTo(&line2, line2Str, textLine2,2,LineToPutinBold);
  }
  if (checkupdate(textbefore3,textLine3)) {
    updateLineTo(&line3, line3Str, textLine3,3,LineToPutinBold);
  }
    // Save
  strcpy(textbefore1, textLine1);
  strcpy(textbefore2, textLine2);
  strcpy(textbefore3, textLine3);
  PopUpNow=false;
}
void timetoclock(bool isfuzzy){
  time_t now = time(NULL);
  struct tm *t = localtime(&now);  
  int minaux;
  minaux=t->tm_min;
  if (isfuzzy){
    if (minaux >= 58){
      mast_hour=t->tm_hour+1;
      mast_min=0;      
    }
    else {
      mast_hour=t->tm_hour;
      minaux=minaux+2;
      minaux=minaux/5;
      mast_min=5*minaux;
    }
  }
  else {
    mast_hour=t->tm_hour;
    mast_min=t->tm_min;    
  }
  mast_mon=t->tm_mon;
  mast_day=t->tm_mday;
  mast_wday=t->tm_wday;
  if (settings.AnimMode){
    display_animated();
  }
  else {
    display_static();
  }
}
// Update graphics when timer ticks
static void time_timer_tick(struct tm *t, TimeUnits units_changed) {
  timetoclock(settings.FuzzyMode);
  if (units_changed & MINUTE_UNIT ) {
    layer_mark_dirty(back_layer);
  }
  //BT: Evaluate reconnection
  bool CheckBT=connection_service_peek_pebble_app_connection();
  if (!settings.BTOn &&  CheckBT ){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "BT reconnected");
    settings.BTOn=true;
    // Update weather info
    request_watchjs();
  }
 //Update toggle
  settings.BTOn=CheckBT;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Tick at %d", t->tm_min);
  s_loop=0;
  if (s_countdown==0){
    //Reset
    s_countdown=settings.UpSlider;
  }
  else {
    s_countdown=s_countdown-1;
  }
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Countdown to update %d", s_countdown);
  // Evaluate if is day or night
  int nowthehouris=t->tm_hour*100+t->tm_min;
  if (settings.HourSunrise<=nowthehouris && nowthehouris<=settings.HourSunset){
    settings.IsNightNow=false;
  }
  else {
    settings.IsNightNow=true;
  }
  // Extra catch on sunrise and sunset
  if (nowthehouris==settings.HourSunrise || nowthehouris==settings.HourSunset){
    s_countdown=1;
  }
  if (settings.GPSOn && settings.NightTheme){
    //Extra catch around 1159 to gather information of today
    if (nowthehouris==1159 && s_countdown>5) {s_countdown=1;};
    // Change Color of background
    layer_mark_dirty(back_layer);
    TextColorFormatting();
  }
  if(s_countdown== 0 || s_countdown==5) {
    if (settings.DisplayTemp ){
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Update weather at %d", t->tm_min);
      request_watchjs();
    }
  }
  if (!settings.GPSOn){
    if (settings.DisplayTemp ){
      if (settings.UpSlider>15){
        if(s_countdown % 15 == 0){
          APP_LOG(APP_LOG_LEVEL_DEBUG, "Attempt to request GPS on %d", t->tm_min);
          request_watchjs();
        }
      }
    }
  }
}
// Proc to update Date and Month layer
static void back_update_proc(Layer *layer, GContext *ctx) {
  // Colors
  graphics_context_set_text_color(ctx,ColorSelect(settings.NightTheme, true, settings.IsNightNow, settings.ForegroundColor, settings.ForegroundColorNight));
  GRect bounds2layer = layer_get_bounds(layer);
  if (settings.BatteryBar){
    int battlevel=battery_state_service_peek().charge_percent;
    graphics_context_set_stroke_color(ctx,ColorSelect(settings.NightTheme, 
                                                    true, settings.IsNightNow, settings.ForegroundColor, settings.ForegroundColorNight));
    graphics_context_set_stroke_width(ctx, 2);
    graphics_draw_line(ctx,GPoint(bounds2layer.origin.x, bounds2layer.origin.y),GPoint(bounds2layer.size.w*battlevel/100,bounds2layer.origin.y));  
  }
  //Translate
  char WeekDay_END[BUFFER_SIZE];
  char Date_END[BUFFER_SIZE];
  char Month_END[BUFFER_SIZE];
  // Set language
  writedatelang(mast_wday,mast_mon,mast_day, WeekDay_END, Date_END,Month_END,settings.LangKey);
  //Draw day of the week
  GRect WDay_rect=GRect(bounds2layer.origin.x,bounds2layer.origin.y,bounds2layer.size.w,bounds2layer.size.h);
  graphics_draw_text(ctx, WeekDay_END, FontWDay, WDay_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
  //Draw date
  char builddate[BUFFER_SIZE];
  //Build based on config settings
  if (settings.DateFormat==1){ //DD MM
    strcpy(builddate,Date_END);
    strcat(builddate," ");
    strcat(builddate,Month_END);
  }
  else { //MM DD
    strcpy(builddate,Month_END);
    strcat(builddate," ");
    strcat(builddate,Date_END);
  }
  GRect Date=GRect(WDay_rect.origin.x,WDay_rect.origin.y+20,WDay_rect.size.w,WDay_rect.size.h);
  graphics_draw_text(ctx, builddate, FontDate, Date, GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, NULL);
  int offsetx=PBL_IF_ROUND_ELSE(0, 10);
  int offsety=PBL_IF_ROUND_ELSE(5, 10);
  
  int offsetconnect;
  if (!settings.BTOn || !settings.GPSOn){
    offsetconnect=5;
  }
  else {
    offsetconnect=0;
  }  
  //Draw Rect for temp
  GRect temprect=GRect(WDay_rect.origin.x,
                       WDay_rect.origin.y+offsetconnect,
                       WDay_rect.size.w/2-25-offsetx/3,
                       WDay_rect.size.h);
  //Draw Rect for cond
  GRect condrect=GRect(WDay_rect.size.w/2+25+offsetx,
                       WDay_rect.origin.y+offsety,
                       WDay_rect.size.w,
                       WDay_rect.size.h);

  //If Bluetooth off and some info was requested display warning
  if (!settings.BTOn){
    if (settings.DisplayTemp){
      graphics_draw_text(ctx, "a",
                         FontSymbol,
                         temprect,
                         GTextOverflowModeWordWrap, GTextAlignmentRight, NULL
                        );
    }
  }
  //If connected but GPS off then display warning
  else {
    if (!settings.GPSOn){
      if (settings.DisplayTemp){
        graphics_draw_text(ctx, "b",
                           FontSymbol,
                           temprect,
                           GTextOverflowModeWordWrap, GTextAlignmentRight, NULL
                          );
      }
    }
    // If BT on and GPS on display according with preferences
    else{
      //If weather active create text
      if (settings.DisplayTemp){
        // Create temp display
        graphics_draw_text(ctx, tempstring, FontWDay, temprect, GTextOverflowModeTrailingEllipsis, GTextAlignmentRight, NULL);
        // Create condition display
        if (settings.IsNightNow){
          graphics_draw_text(ctx, condstringnight, FontCond,condrect, GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        }
        else {
          graphics_draw_text(ctx, condstringday, FontCond,condrect, GTextOverflowModeTrailingEllipsis, GTextAlignmentLeft, NULL);
        }
      }
    }
  }
} // End build
///// End: Updating time and date////
////Init: Handle Settings and Weather////
// Read settings from persistent storage
static void prv_load_settings() {
  // Load the default settings
  prv_default_settings();
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}
// Save the settings to persistent storage
static void prv_save_settings() {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}
// Handle the response from AppMessage
static void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  s_loop=s_loop+1;
  if (s_loop==1){
    //Clean vars
    strcpy(tempstring, "");
    strcpy(condstringday, "");
    strcpy(condstringnight, "");
  }
  // Background Color
  Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_BackgroundColor);
  if (bg_color_t) {
    settings.BackgroundColor = GColorFromHEX(bg_color_t->value->int32);
  }
  Tuple *nbg_color_t = dict_find(iter, MESSAGE_KEY_BackgroundColorNight);
  if (nbg_color_t) {
    settings.BackgroundColorNight = GColorFromHEX(nbg_color_t->value->int32);
  }
  // Foreground Color
  Tuple *fg_color_t = dict_find(iter, MESSAGE_KEY_ForegroundColor);
  if (fg_color_t) {
    settings.ForegroundColor = GColorFromHEX(fg_color_t->value->int32);
  }
  Tuple *nfg_color_t = dict_find(iter, MESSAGE_KEY_ForegroundColorNight);
  if (nfg_color_t) {
    settings.ForegroundColorNight = GColorFromHEX(nfg_color_t->value->int32);
  }
  // Get display handlers
  Tuple *frequpdate=dict_find(iter, MESSAGE_KEY_UpSlider);
  if (frequpdate){
    settings.UpSlider=(int)frequpdate->value->int32;
    //Restart the counter
    s_countdown=settings.UpSlider;
  }
  Tuple *distemp_t=dict_find(iter,MESSAGE_KEY_DisplayTemp);
  if (distemp_t){
    if (distemp_t->value->int32==0){
      settings.DisplayTemp=false;
    }
    else settings.DisplayTemp=true;
  }
  Tuple *fuzzy_t=dict_find(iter,MESSAGE_KEY_FuzzyMode);
  if (fuzzy_t){
    if (fuzzy_t->value->int32==0){
      settings.FuzzyMode=false;
    }
    else settings.FuzzyMode=true;
  }
  Tuple *anim_t=dict_find(iter,MESSAGE_KEY_AnimMode);
  if (anim_t){
    if (anim_t->value->int32==0){
      settings.AnimMode=false;
    }
    else settings.AnimMode=true;
  }
  Tuple *battt=dict_find(iter,MESSAGE_KEY_BatteryBar);
  if (battt){
    if (battt->value->int32==0){
      settings.BatteryBar=false;
    }
    else settings.BatteryBar=true;
  }
  Tuple *disntheme_t=dict_find(iter,MESSAGE_KEY_NightTheme);
  if (disntheme_t){
    if (disntheme_t->value->int32==0){
      settings.NightTheme=false;
    }
    else {
      settings.NightTheme=true;}
  }
  //Control of data from http
  // Weather Cond
  Tuple *wcond_t=dict_find(iter, MESSAGE_KEY_WeatherCondDay);
  if (wcond_t){
    snprintf(condstringday , sizeof(condstringday), "%s", wcond_t->value->cstring);
  }
  Tuple *n_wcond_t=dict_find(iter, MESSAGE_KEY_WeatherCondNight);
  if (n_wcond_t){
    snprintf(condstringnight , sizeof(condstringnight), "%s", n_wcond_t->value->cstring);
  }
  // Weather Temp
  Tuple *wtemp_t=dict_find(iter, MESSAGE_KEY_WeatherTemp);
  if (wtemp_t){
    snprintf(tempstring, sizeof(tempstring), "%s", wtemp_t->value->cstring);
  }
  //Hour Sunrise and Sunset
  Tuple *sunrise_t=dict_find(iter, MESSAGE_KEY_HourSunrise);
  if (sunrise_t){
    settings.HourSunrise=(int)sunrise_t->value->int32;
  }
  Tuple *sunset_t=dict_find(iter, MESSAGE_KEY_HourSunset);
  if (sunset_t){
    settings.HourSunset=(int)sunset_t->value->int32;
  }
  //Control of data gathered for http
  APP_LOG(APP_LOG_LEVEL_DEBUG, "After loop %d temp is %s Cond is %s Sunrise is %d Sunset is %d", s_loop,tempstring,condstringday,settings.HourSunrise,settings.HourSunset);
  if (strcmp(tempstring, "") !=0 && strcmp(condstringday, "") !=0 && strcmp(condstringnight, "")){
    APP_LOG(APP_LOG_LEVEL_DEBUG,"GPS on at loop %d",s_loop);
    settings.GPSOn=true;
  }
  else {
    APP_LOG(APP_LOG_LEVEL_DEBUG,"Missing info at loop %d, GPS off",s_loop);
    settings.GPSOn=false;
  }
  //In every request reset countdown
  s_countdown=settings.UpSlider;
  // If GPS disconnected change to 15 minutes
  if (!settings.GPSOn){
    if (settings.DisplayTemp ){
      if (settings.UpSlider>15){
        s_countdown=15;
      }
    }
  }  
  //End data gathered
  // Store language applied before refreshing
  // Language
  Tuple *lang_t=dict_find(iter, MESSAGE_KEY_Lang);
  if (lang_t){
    settings.LangKey=atoi(lang_t->value->cstring);
  };
  // Date format
  Tuple *dateformat_t=dict_find(iter,MESSAGE_KEY_DateFormat);
  if (dateformat_t){
    settings.DateFormat=atoi(dateformat_t->value->cstring);
  }
  //Update colors
  TextColorFormatting();
  layer_mark_dirty(back_layer);
  timetoclock(settings.FuzzyMode);
  // Save the new settings to persistent storage
  prv_save_settings();
}
////End: Handle Settings and Weather////
////Init: Creating Watchface/////
//Build watchface
static void prv_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  int offsetsq=PBL_IF_RECT_ELSE(5, 0 );
  back_layer = layer_create(GRect(0,bounds.size.h-45+offsetsq,bounds.size.w, 45));
  layer_set_update_proc(back_layer, back_update_proc);
  layer_add_child(window_layer, back_layer);
}
// Window Unload event
static void prv_window_unload(Window *window) {
  layer_destroy(back_layer);
  window_destroy(s_main_window);
  text_layer_destroy(line1.currentLayer);
  text_layer_destroy(line1.nextLayer);
  text_layer_destroy(line2.currentLayer);
  text_layer_destroy(line2.nextLayer);
  text_layer_destroy(line3.currentLayer);
  text_layer_destroy(line3.nextLayer);
  layer_destroy(scroll);
  fonts_unload_custom_font(FontCond);
  fonts_unload_custom_font(Bold);
  fonts_unload_custom_font(BoldReduced1);
  fonts_unload_custom_font(BoldReduced2);
  fonts_unload_custom_font(BoldReduced3);
  fonts_unload_custom_font(Light);
  fonts_unload_custom_font(LightReduced1);
  fonts_unload_custom_font(LightReduced2);
  fonts_unload_custom_font(LightReduced3);
  fonts_unload_custom_font(FontWDay);
  fonts_unload_custom_font(FontDate);
  fonts_unload_custom_font(FontSymbol);
}
void main_window_push() {
  s_main_window = window_create();
  Layer *root = window_get_root_layer(s_main_window);
  //Set bounds and offsets
  bounds = layer_get_bounds(root);
  offsetpebble= PBL_IF_ROUND_ELSE((bounds.size.h - 145) / 2-5,5);
  // Create layers
  // Scroll
  scroll = layer_create(bounds);
  // 1st line layer
  line1.currentLayer = text_layer_create(GRect(0, offsetpebble, bounds.size.w, 50));
  line1.nextLayer = text_layer_create(GRect(bounds.size.w, offsetpebble, bounds.size.w, 50));
  configureLineLayer(line1.currentLayer);
  configureLineLayer(line1.nextLayer);
  // 2nd line layer
  line2.currentLayer = text_layer_create(GRect(0, 37 + offsetpebble, bounds.size.w, 50));
  line2.nextLayer = text_layer_create(GRect(bounds.size.w, 37 + offsetpebble, bounds.size.w, 50));
  configureLineLayer(line2.currentLayer);
  configureLineLayer(line2.nextLayer);
  // 3rd line layer
  line3.currentLayer = text_layer_create(GRect(0, 74 + offsetpebble, bounds.size.w, 50));
  line3.nextLayer = text_layer_create(GRect(bounds.size.w, 74 + offsetpebble, bounds.size.w, 50));
  configureLineLayer(line3.currentLayer);
  configureLineLayer(line3.nextLayer);
  // Load layers
  layer_add_child(root, scroll);
  layer_add_child(scroll, (Layer *)line1.currentLayer);
  layer_add_child(scroll, (Layer *)line1.nextLayer);
  layer_add_child(scroll, (Layer *)line2.currentLayer);
  layer_add_child(scroll, (Layer *)line2.nextLayer);
  layer_add_child(scroll, (Layer *)line3.currentLayer);
  layer_add_child(scroll, (Layer *)line3.nextLayer);
  TextColorFormatting();
  // Configure text time on init
  AtInit=true;
  timetoclock(settings.FuzzyMode);
  // Configure main window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = prv_window_load,
    .unload = prv_window_unload,
  });
  window_stack_push(s_main_window, true);
}
static void prv_init(void) {
  prv_load_settings();
  //Starting loop at 0
  s_loop=0;
  s_countdown=settings.UpSlider;
  //Clean vars
  strcpy(tempstring, "");
  strcpy(condstringday, "");
  strcpy(condstringnight, "");
  // Listen for AppMessages
  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(256, 256);
  // Load fonts
  Bold=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GBOLD_39));
  BoldReduced1=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GBOLD_34));
  BoldReduced2=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GBOLD_30));
  BoldReduced3=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GBOLD_22));
  Light=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GLIGHT_39));
  LightReduced1=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GLIGHT_34));
  LightReduced2=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GLIGHT_30));
  LightReduced3=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GLIGHT_22));
  FontCond=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_WICON_26));
  FontWDay=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GBOLD_16));
  FontDate=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GLIGHT_16));
  FontSymbol =fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SYMBOL_14));
  main_window_push();
  // Register for minute ticks
  tick_timer_service_subscribe(MINUTE_UNIT, time_timer_tick);
    connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = bluetooth_callback
  });
}
static void prv_deinit(void) {
  tick_timer_service_unsubscribe();
  app_message_deregister_callbacks(); //Destroy the callbacks for clean up
}
int main(void) {
  prv_init();
  app_event_loop();
  prv_deinit();
}
////End: Creating Watchface///