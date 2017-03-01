#include <pebble.h>
#include "main.h"
#define BUFFER_SIZE 44

//Include weather icons
#include "iconmap.h"

//Include languages
#include "num2words-es.h"
#include "num2words-en.h"

///////////////////////////
// 1. Define structures////
///////////////////////////

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
static TextLayer *s_temp_layer;
static TextLayer *s_wicon_layer;

// Chars
static char line1Str[2][BUFFER_SIZE];
static char line2Str[2][BUFFER_SIZE];
static char line3Str[2][BUFFER_SIZE];

//Fonts
static GFont s_weather_font;
static GFont Bold;
static GFont BoldReduced1;
static GFont BoldReduced2;
static GFont Light;
static GFont LightReduced1;
static GFont LightReduced2;

//Others
PropertyAnimation *scroll_down;
PropertyAnimation *scroll_up;
static bool PoppedDownNow;
static bool PoppedDownAtInit;
GRect bounds;

///////////////////////////
//////Init Configuration///
///////////////////////////
//Init Clay
ClaySettings settings;
// Initialize the default settings
static void prv_default_settings() { 
  settings.BackgroundColor = GColorBlack;
  settings.ForegroundColor = GColorWhite;
  settings.WeatherUnit = false;
  settings.LangKey=1; 
  settings.DateFormat=1;
}
///////////////////////////
//////End Configuration///
///////////////////////////

////////////////////////////
////Init: Animations procs//
////////////////////////////
void makeScrollUp(struct tm *t){
  GRect from = layer_get_bounds((Layer *)scroll);
	GRect to = layer_get_bounds((Layer *)scroll);
	GRect rect = layer_get_bounds((Layer *)scroll);
	if(rect.origin.y == 21){
		from.origin.y = 0;
		to.origin.y = -21;
	} else {
		from.origin.y = 21;
		to.origin.y = 0;
	}
	scroll_down = property_animation_create_layer_frame((Layer *)scroll, &from, &to);
	animation_set_duration(property_animation_get_animation(scroll_down), 800);
	animation_set_delay(property_animation_get_animation(scroll_down), (59000-1000*t->tm_sec));
	animation_set_curve(property_animation_get_animation(scroll_down), AnimationCurveEaseOut);
	animation_schedule(property_animation_get_animation(scroll_down));
	// reset PoppedDown indicator
	PoppedDownNow = false;
}
void makeScrollUpNow(){
	GRect from = layer_get_bounds((Layer *)scroll);
	GRect to = layer_get_bounds((Layer *)scroll);
	GRect rect = layer_get_bounds((Layer *)scroll);
	if(rect.origin.y == 21){
		from.origin.y = 0;
		to.origin.y = -21;
	} else {
		from.origin.y = 21;
		to.origin.y = 0;
	}
	scroll_down = property_animation_create_layer_frame((Layer *)scroll, &from, &to);
	animation_set_duration(property_animation_get_animation(scroll_down), 400);
	animation_set_curve(property_animation_get_animation(scroll_down), AnimationCurveEaseOut);
	animation_schedule(property_animation_get_animation(scroll_down));
	// reset PoppedDown indicator
	PoppedDownNow = false;
}
void makeScrollDown(){
	GRect from = layer_get_bounds((Layer *)scroll);
	GRect to = layer_get_bounds((Layer *)scroll);
	if(PoppedDownAtInit == true){
		from.origin.y = -21;
		to.origin.y = 0;
	} else {
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
	animation_set_curve(property_animation_get_animation(line->nextAnimation), AnimationCurveEaseOut);
	animation_schedule(property_animation_get_animation(line->nextAnimation));
	
  GRect rect2 = layer_get_frame((Layer *)current);
	rect2.origin.x -= bounds.size.w;
	line->currentAnimation = property_animation_create_layer_frame((Layer *)current, NULL, &rect2);
	animation_set_duration(property_animation_get_animation(line->currentAnimation), 400);
	animation_set_curve(property_animation_get_animation(line->currentAnimation), AnimationCurveEaseOut);
	
  animation_set_handlers(property_animation_get_animation(line->currentAnimation), (AnimationHandlers) {
	  .stopped = (AnimationStoppedHandler)animationStoppedHandler
	  }, 
  current);
	
  animation_schedule(property_animation_get_animation(line->currentAnimation));
}
// Pop down to center before initial display when only 2 lines of text
void makePopDown(){
	GRect rect = layer_get_bounds((Layer *)scroll);
	rect.origin.y = 21;
	layer_set_bounds(scroll, rect);
}
////////////////////////////
////End: Animations procs//
////////////////////////////

////////////////////////////
////Init: Layer updating////
////////////////////////////
// Update text line
void updateLineTo(Line *line, char lineStr[2][BUFFER_SIZE], char *value) {
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
	
	makeAnimationsForLayers(line, current, next);
}
// Check to see if the current text line needs to be updated
bool needToUpdateLine(Line *line, char lineStr[2][BUFFER_SIZE], char *nextValue) {
	char *currentStr;
	GRect rect = layer_get_frame((Layer *)line->currentLayer);
	currentStr = (rect.origin.x == 0) ? lineStr[0] : lineStr[1];

	if (memcmp(currentStr, nextValue, strlen(nextValue)) != 0 ||
		(strlen(nextValue) == 0 && strlen(currentStr) != 0)) {
		return true;
	}
	return false;
}
////////////////////////////
////End: Layer updating////
////////////////////////////

////////////////////////////
////Init: Layer formatting//
////////////////////////////
// Configure line of text
void configureLineLayer(TextLayer *textlayer) {
	text_layer_set_text_color(textlayer, settings.ForegroundColor);
	text_layer_set_background_color(textlayer, GColorClear);
  text_layer_set_text_alignment(textlayer, GTextAlignmentCenter);
}
// Configure font of text
void configureLayer(TextLayer *textlayer, char *Text, int bold, int ref) {
  int lenstring;
  lenstring=strlen(Text);
  bool issquare=PBL_IF_RECT_ELSE(true,false);
  text_layer_set_overflow_mode(textlayer, GTextOverflowModeFill);
  
  // Update font depending of it is an hour - bold and the lenght, so size will be reduced to fit bounds of the layer
  // Also, squares and round Pebbles fits different lengths - taken into account
  if (issquare){
      if (bold==ref){
        if (lenstring<8){
          //Bold and big
          text_layer_set_font(textlayer,Bold);        
        }
        //Bold reduced1
        else if (lenstring<9){
          text_layer_set_font(textlayer,BoldReduced1);                             
        }
        //Bold Reduced 2
        else {
          text_layer_set_font(textlayer,BoldReduced2);
        }
      }
      else {if (lenstring<8){
        //Light and big
        text_layer_set_font(textlayer,Light);  
      }
      //Light reduced 1
      else if (lenstring<9) {
        text_layer_set_font(textlayer,LightReduced1);
      }
       //Light Reduced 2
      else {
        text_layer_set_font(textlayer,LightReduced2);
      }
    }
  }
  else { 
       if (bold==ref){
        if (lenstring<9){
          //Bold and big
          text_layer_set_font(textlayer,Bold);        
        }
        //Bold reduced
        else {
          text_layer_set_font(textlayer,BoldReduced1); 
        }
      }
      else {if (lenstring<9){
        //Light and big
        text_layer_set_font(textlayer,Light);  
      }
      //Light reduced
      else {
        text_layer_set_font(textlayer,LightReduced1);
      } 
    }
  };
}
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
////////////////////////////
////End: Layer formatting//
////////////////////////////

//////////////////////////////////////
///// Init: Updating time and date////
/////////////////////////////////////
// Update screen based on new time
void display_time(struct tm *t, int atinit) {
  // The current time text will be stored in the following 3 strings
	char textLine1[BUFFER_SIZE];
	char textLine2[BUFFER_SIZE];
	char textLine3[BUFFER_SIZE];
  int LineToPutinBold=0;

  // Language settings
  if (settings.LangKey==1){        //Spanish
    time_to_3words_ES(t->tm_hour, t->tm_min,&LineToPutinBold, textLine1, textLine2, textLine3);
  }
  else if (settings.LangKey==2){   //English
    time_to_3words_EN(t->tm_hour, t->tm_min,&LineToPutinBold, textLine1, textLine2, textLine3);
  };
    
  // Configure fonts  
  configureLayer(line1.currentLayer,textLine1,LineToPutinBold,1);
  configureLayer(line2.currentLayer,textLine2,LineToPutinBold,2);
  configureLayer(line3.currentLayer,textLine3,LineToPutinBold,3);
  configureLayer(line1.nextLayer,textLine1,LineToPutinBold,1);
  configureLayer(line2.nextLayer,textLine2,LineToPutinBold,2);
  configureLayer(line3.nextLayer,textLine3,LineToPutinBold,3);
  
  //Adjust vertical alignment
 	int offset = PBL_IF_ROUND_ELSE((bounds.size.h - 145) / 2,5);
  
  verticalAlignTextLayer(line1.currentLayer, offset);
  verticalAlignTextLayer(line1.nextLayer,    offset);
  verticalAlignTextLayer(line2.currentLayer, 37+offset);
  verticalAlignTextLayer(line2.nextLayer,    37+offset);
  verticalAlignTextLayer(line3.currentLayer, 74+offset);
  verticalAlignTextLayer(line3.nextLayer,    74+offset);

  //Update lines
  if (needToUpdateLine(&line1, line1Str, textLine1)) {
		updateLineTo(&line1, line1Str, textLine1);
  }
	if (needToUpdateLine(&line2, line2Str, textLine2)) {
		updateLineTo(&line2, line2Str, textLine2);
	}
	if (needToUpdateLine(&line3, line3Str, textLine3)) {
		updateLineTo(&line3, line3Str, textLine3);	
  }
}
// Update graphics when timer ticks
static void time_timer_tick(struct tm *t, TimeUnits units_changed) {
  if (units_changed & MINUTE_UNIT ) {
	  layer_mark_dirty(back_layer);  
	}
	
	// Update text time
	display_time(t,0);
  
  // Set Up and Down animations
  int LBef=0;
  int Lnow=0;
  int LAft=0;
  
  //Different based on Language
  if (settings.LangKey==1){        //Spanish
    Animations_ES(t->tm_min, &LBef, &Lnow, &LAft);
  }
  else if (settings.LangKey==2){      //English
    Animations_EN(t->tm_min, &LBef, &Lnow, &LAft);                         
  }
  
 	// Recenter screen if last time was 3 lines, but new time is 2 lines
	// Don't do this if time was just initialized already centered
  if(LBef>0 && Lnow==0  ){
    if(PoppedDownNow == false){
		  makeScrollDown();
		}
	}

    // Prepare for next time being 3 lines, if current time is 2 lines
		if(Lnow==0 && LAft > 0  ){
		  makeScrollUp(t);
		}
  
  // Get weather update every 30 minutes
	if(t->tm_min % 30 == 0) {
  	// Begin dictionary
  	DictionaryIterator *iter;
  	app_message_outbox_begin(&iter);
 		// Add a key-value pair
  	dict_write_uint8(iter, 0, 0);
    // Send the message!
 		app_message_outbox_send();
	}
}
// Proc to update Date and Month layer
static void back_update_proc(Layer *layer, GContext *ctx) {
  time_t now = time(NULL);
  struct tm *t   = localtime(&now);
  GRect bounds = layer_get_bounds(layer);
  
  char WeekDay_END[BUFFER_SIZE];
  char Date_END[BUFFER_SIZE];
  char Month_END[BUFFER_SIZE];

  // Set language
  if (settings.LangKey==1){        //Spanish
    WriteDate_ES(t->tm_wday, t->tm_mon, t->tm_mday, WeekDay_END, Date_END,Month_END);
  }
  else if (settings.LangKey==2){  //English
    WriteDate_EN(t->tm_wday, t->tm_mon, t->tm_mday, WeekDay_END, Date_END,Month_END);                               
  }
  
  // Display day of week
  graphics_context_set_text_color(ctx, settings.ForegroundColor);
	graphics_draw_text(ctx, WeekDay_END, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD),
					   GRect(0, bounds.size.h - 48, bounds.size.w, 30), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
   
	// Display date
  char builddate[BUFFER_SIZE];
  //Build based on config settings
  if (settings.DateFormat==1){  //DD MM
    strcpy(builddate,Date_END);
    strcat(builddate," ");
    strcat(builddate,Month_END);
  }
  else {                        //MM DD
    strcpy(builddate,Month_END);
    strcat(builddate," ");
    strcat(builddate,Date_END);
  }
  graphics_context_set_text_color(ctx, settings.ForegroundColor);
	graphics_draw_text(ctx, builddate, fonts_get_system_font(FONT_KEY_GOTHIC_24), 
					   GRect(0, bounds.size.h - 30, bounds.size.w, 30), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
} // End build
//////////////////////////////////////
///// End: Updating time and date////
/////////////////////////////////////

/////////////////////////////////////////
////Init: Handle Settings and Weather////
/////////////////////////////////////////
// Read settings from persistent storage
static void prv_load_settings() {
  // Load the default settings
  prv_default_settings();
  // Read settings from persistent storage, if they exist
  persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}
// Save the settings to persistent storage
static void prv_save_settings(int ChangeLang, int LangBefore) {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
  // Update date
  layer_set_update_proc(back_layer, back_update_proc);
  layer_mark_dirty(back_layer);
  
  //Update time only if change of language
	time_t now = time(NULL);
	struct tm *t   = localtime(&now);
  // Content of line 3 now
  int LenBeforeSave=0;
  if (LangBefore==1){      //Spanish
    PopatInit_ES(t->tm_min, &LenBeforeSave);}
  else if (LangBefore==2){  //English
    PopatInit_EN(t->tm_min, &LenBeforeSave);
  }
  // Adjust animations to fit the change of language - study how long will be line 3 after change language
  int LenAfterSave=0;
  if (settings.LangKey==1){
    PopatInit_ES(t->tm_min, &LenAfterSave);}
  else if (settings.LangKey==2){
    PopatInit_EN(t->tm_min, &LenAfterSave);
  }
  //Update text if language has changed
  //Adjust position using animations
  if (ChangeLang>0){
    if (LenBeforeSave==0 && LenAfterSave != 0){
      // Scroll up if before were 2 lines and after 3 lines
      makeScrollUpNow() ;
    }
    // Display time
    display_time(t,1);
    if (LenBeforeSave>0 && LenAfterSave == 0){
      // Pop down if before were 3 lines and now 2 lines
      makeScrollDown();
    }
  }
}
// Handle the response from AppMessage
static void prv_inbox_received_handler(DictionaryIterator *iter, void *context) {
  // Background Color
  Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_BackgroundColor);
  if (bg_color_t) {
    settings.BackgroundColor = GColorFromHEX(bg_color_t->value->int32);
	}

  // Foreground Color
 	Tuple *fg_color_t = dict_find(iter, MESSAGE_KEY_ForegroundColor);
  if (fg_color_t) {
    settings.ForegroundColor = GColorFromHEX(fg_color_t->value->int32);
  }  
  
  // Store language applied before refreshing
  int LangBefSave=settings.LangKey;
  // Language
  Tuple *lang_t=dict_find(iter, MESSAGE_KEY_Lang);
  if (lang_t){
    settings.LangKey=atoi(lang_t->value->cstring);
  };
  int LangAftSave=settings.LangKey;

  // Date format
  Tuple *dateformat_t=dict_find(iter,MESSAGE_KEY_DateFormat);
  if (dateformat_t){
    settings.DateFormat=atoi(dateformat_t->value->cstring);
  }
  
  //Update colors
  window_set_background_color(s_main_window, settings.BackgroundColor);
	layer_mark_dirty(back_layer);
	text_layer_set_text_color(line1.currentLayer, settings.ForegroundColor);
	text_layer_set_text_color(line1.nextLayer, settings.ForegroundColor);
	text_layer_set_text_color(line2.currentLayer, settings.ForegroundColor);
	text_layer_set_text_color(line2.nextLayer, settings.ForegroundColor);
	text_layer_set_text_color(line3.currentLayer, settings.ForegroundColor);
	text_layer_set_text_color(line3.nextLayer, settings.ForegroundColor);
 	text_layer_set_text_color(s_temp_layer, settings.ForegroundColor);
	text_layer_set_text_color(s_wicon_layer , settings.ForegroundColor);
  
  // Mark if language has changed
  int LangChanged=0;
  if (LangAftSave != LangBefSave )
      {LangChanged=1;
  }
 
  // Save the new settings to persistent storage
  prv_save_settings(LangChanged,LangBefSave);
 
  // Weather information
  static char temperature_buffer[8];
  // Read tuples for data
  Tuple *temp_tuple = dict_find(iter, MESSAGE_KEY_WeatherTemp);
  Tuple *conditions_tuple = dict_find(iter, MESSAGE_KEY_WeatherCond);
  
  // If all data is available, use it
  if(temp_tuple && conditions_tuple) {
     //Temp Layer
    	snprintf(temperature_buffer, sizeof(temperature_buffer), "%s", temp_tuple->value->cstring);
     	text_layer_set_text(s_temp_layer, temperature_buffer);
    
    	//Translate condition code from Yahoo to character - here I applied a customized font
   	 	conditions_yahoo((int)conditions_tuple->value->int32,s_wicon_layer);
  }  
}
/////////////////////////////////////////
////End: Handle Settings and Weather////
/////////////////////////////////////////

//////////////////////////////////
////Init: Creating Watchface/////
/////////////////////////////////
//Build watchface
static void prv_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);

  back_layer = layer_create(bounds);
	layer_set_update_proc(back_layer, back_update_proc);
	layer_add_child(window_layer, back_layer);  
}
// Window Unload event
static void prv_window_unload(Window *window) {
 	layer_destroy(back_layer);
}
static void prv_init(void) {
  prv_load_settings();
    // Listen for AppMessages
  app_message_register_inbox_received(prv_inbox_received_handler);
  app_message_open(128, 128);
  // Configure main window
	s_main_window = window_create();
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = prv_window_load,
		.unload = prv_window_unload,
	});
  
  // Load fonts
  Bold=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GBOLD_39));
  BoldReduced1=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GBOLD_34));
  BoldReduced2=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GBOLD_30));
  Light=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GLIGHT_39));
  LightReduced1=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GLIGHT_34));
  LightReduced2=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_GLIGHT_30));
  s_weather_font=fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_WEATHERFONT_24));
    
  window_stack_push(s_main_window, true);
  Layer *root = window_get_root_layer(s_main_window);
	
  //Set bounds and offsets
	bounds = layer_get_bounds(root);
	int offset = PBL_IF_ROUND_ELSE((bounds.size.h - 145) / 2,5);
	int middlescreen=bounds.size.w/2;
 	int offsetweatherh=PBL_IF_RECT_ELSE(30,20);
  int offsetweatherv=PBL_IF_RECT_ELSE(10,0);

  // Create layers
  // Scroll
	scroll = layer_create(bounds); 
  // 1st line layer
	line1.currentLayer = text_layer_create(GRect(0, offset, bounds.size.w, 50));
	line1.nextLayer = text_layer_create(GRect(bounds.size.w, offset, bounds.size.w, 50));
	configureLineLayer(line1.currentLayer);
	configureLineLayer(line1.nextLayer);
  // 2nd line layer
	line2.currentLayer = text_layer_create(GRect(0, 37 + offset, bounds.size.w, 50));
	line2.nextLayer = text_layer_create(GRect(bounds.size.w, 37 + offset, bounds.size.w, 50));
	configureLineLayer(line2.currentLayer);
	configureLineLayer(line2.nextLayer);
	// 3rd line layer
	line3.currentLayer = text_layer_create(GRect(0, 74 + offset, bounds.size.w, 50));
	line3.nextLayer = text_layer_create(GRect(bounds.size.w, 74 + offset, bounds.size.w, 50));
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
 
  // Create temperature Layer
  s_temp_layer = text_layer_create(GRect(0,  bounds.size.h - 44+offsetweatherv, middlescreen-offsetweatherh, 30));
  // Style the text
  text_layer_set_background_color(s_temp_layer, GColorClear);
  text_layer_set_text_color(s_temp_layer, settings.ForegroundColor);
  text_layer_set_text_alignment(s_temp_layer, GTextAlignmentRight);
  text_layer_set_font(s_temp_layer,fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child( back_layer,text_layer_get_layer(s_temp_layer));

 	//Create layer for conditions
  s_wicon_layer=text_layer_create(GRect(middlescreen+offsetweatherh,  bounds.size.h - 40+offsetweatherv, 25, 30));
  text_layer_set_background_color(s_wicon_layer, GColorClear);
  text_layer_set_text_color(s_wicon_layer, settings.ForegroundColor);
  text_layer_set_text_alignment(s_wicon_layer, GTextAlignmentLeft);
  text_layer_set_font(s_wicon_layer, s_weather_font);
 	layer_add_child(window_get_root_layer(s_main_window), text_layer_get_layer(s_wicon_layer)); 

 	// Configure text time on init
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	display_time(t,1);
	// Register for minute ticks
	tick_timer_service_subscribe(MINUTE_UNIT, time_timer_tick);
	
  // initialize PoppedDown indicators
	PoppedDownNow = false;
	PoppedDownAtInit = false;
	// If initial display of time is only 2 lines of text, display centered
  // Based on languague on init
   int LenInit_END=0;
  if (settings.LangKey==1){        // Spanish
    PopatInit_ES(t->tm_min, &LenInit_END);}
  else if (settings.LangKey==2){  //English
    PopatInit_EN(t->tm_min, &LenInit_END);
  }
  
  // Check Line3 at init
	if(LenInit_END == 0 ){
		makePopDown();
		// signal that this has been done, so an extra animation isn't triggered, and the down animation knows the right
		// starting place
		PoppedDownNow = true;
		PoppedDownAtInit = true;
	}
}
static void prv_deinit(void) {
	window_destroy(s_main_window);
	tick_timer_service_unsubscribe();
	app_message_deregister_callbacks();    //Destroy the callbacks for clean up
	text_layer_destroy(line1.currentLayer);
	text_layer_destroy(line1.nextLayer);
	text_layer_destroy(line2.currentLayer);
	text_layer_destroy(line2.nextLayer);
	text_layer_destroy(line3.currentLayer);
	text_layer_destroy(line3.nextLayer);
  text_layer_destroy(s_temp_layer);
  text_layer_destroy(s_wicon_layer);
	layer_destroy(scroll);
}
int main(void) {
  prv_init();
  app_event_loop();
  prv_deinit();
}
//////////////////////////////////
////End: Creating Watchface/////
/////////////////////////////////