#include <pebble.h>
#include "main.h"
#include "num2words-en.h"
#define BUFFER_SIZE 44

#include "iconmap.h"



//Init_StrMonthDat: Create strings for Months and Days
static const char* const MONTHS_ES[] = {
"Ene ",
"Feb ",
"Mar ",
"Abr ",
"May ",
"Jun ",
"Jul ",
"Ago ",
"Sep ",
"Oct ",
"Nov ",
"Dic ",
};
	
static const char* const DAYS_ES[] = {
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


static const char* const WEEKDAY_ES[] = {
"Dom",
"Lun",
"Mar",
"Mie",
"Jue",
"Vie",
"Sab",
};
//End_Weekday

//Init_CrStruct: Create Structure
typedef struct {
	TextLayer *currentLayer;
	TextLayer *nextLayer;	
	PropertyAnimation *currentAnimation;
	PropertyAnimation *nextAnimation;
} Line;

Line line1;
Line line2;
Line line3;

GRect bounds;

static char line1Str[2][BUFFER_SIZE];
static char line2Str[2][BUFFER_SIZE];
static char line3Str[2][BUFFER_SIZE];

static Window *s_main_window;

Layer *back_layer;
Layer *scroll;
PropertyAnimation *scroll_down;
PropertyAnimation *scroll_up;

static TextLayer *s_temp_layer;
static GFont s_weather_font;
static TextLayer *s_wicon_layer;

static bool PoppedDownNow;
static bool PoppedDownAtInit;

//Init_Clay
ClaySettings settings;

// Initialize the default settings
static void prv_default_settings() { 
  settings.BackgroundColor = GColorBlack;
  settings.ForegroundColor = GColorWhite;
}

//End_CrStruct
// Draw time indicators
static void back_update_proc(Layer *layer, GContext *ctx) {

	time_t now = time(NULL);
	struct tm *t   = localtime(&now);
	
	GRect bounds = layer_get_bounds(layer);
  
  
	
	

	// Display day of week
	char iterweekday;
	//trftime(&tempstring, 10, "%A", t);
  strcpy(&iterweekday, WEEKDAY_ES[t->tm_wday]);
	graphics_context_set_text_color(ctx, settings.ForegroundColor);
	graphics_draw_text(ctx, &iterweekday, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD),
					   GRect(0, bounds.size.h - 48, 180, 30), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  
char iterdatemonth;
	// Display date
    strcpy(&iterdatemonth, MONTHS_ES[t->tm_mon]);
    strcat(&iterdatemonth, DAYS_ES[t->tm_mday]);
	graphics_context_set_text_color(ctx, settings.ForegroundColor);
	graphics_draw_text(ctx, &iterdatemonth, fonts_get_system_font(FONT_KEY_GOTHIC_24), 
					   GRect(0, bounds.size.h - 30, 180, 30), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
}






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
  // Update the display based on new settings
 window_set_background_color(s_main_window, settings.BackgroundColor);
 text_layer_set_text_color(s_temp_layer, settings.ForegroundColor);
  text_layer_set_text_color(s_wicon_layer , settings.ForegroundColor);
  layer_set_update_proc(back_layer, back_update_proc);
}

// Update the display elements
static void prv_update_display() {
  // Background color
  window_set_background_color(s_main_window, settings.BackgroundColor);
 

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
  
  window_set_background_color(s_main_window, settings.BackgroundColor);
	layer_mark_dirty(back_layer);
	text_layer_set_text_color(line1.currentLayer, settings.ForegroundColor);
	text_layer_set_text_color(line1.nextLayer, settings.ForegroundColor);
	text_layer_set_text_color(line2.currentLayer, settings.ForegroundColor);
	text_layer_set_text_color(line2.nextLayer, settings.ForegroundColor);
	text_layer_set_text_color(line3.currentLayer, settings.ForegroundColor);
	text_layer_set_text_color(line3.nextLayer, settings.ForegroundColor);

 
  // Save the new settings to persistent storage
  prv_save_settings();
  
  // Store incoming information
  static char temperature_buffer[8];
  static char icon_buffer[8];
  
  // Read tuples for data
  Tuple *temp_tuple = dict_find(iter, MESSAGE_KEY_KEY_TEMPERATURE);
  Tuple *conditions_tuple = dict_find(iter, MESSAGE_KEY_KEY_CONDITIONS);
  Tuple *weathericon_tuple=dict_find(iter,MESSAGE_KEY_KEY_ICON);
  // If all data is available, use it
  if(temp_tuple && conditions_tuple) {
    //Temp Layer
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%dc", (int)temp_tuple->value->int32);
    text_layer_set_text(s_temp_layer, temperature_buffer);
    
    //Translate condition value
    int condint=(int)conditions_tuple->value->int32;
    snprintf(icon_buffer, sizeof(weathericon_tuple), "%s", weathericon_tuple->value->cstring);
      
    code_to_text(condint,icon_buffer,s_wicon_layer);
    
  }  
}

//AppMessage for update weather

// Handle the response from AppMessage
static void updateweather(DictionaryIterator *iter, void *context) {
    
  // Store incoming information
  static char temperature_buffer[8];
  static char icon_buffer[8];
  
  // Read tuples for data
  Tuple *temp_tuple = dict_find(iter, MESSAGE_KEY_KEY_TEMPERATURE);
  Tuple *conditions_tuple = dict_find(iter, MESSAGE_KEY_KEY_CONDITIONS);
  Tuple *weathericon_tuple=dict_find(iter,MESSAGE_KEY_KEY_ICON);
  // If all data is available, use it
  if(temp_tuple && conditions_tuple) {
    //Temp Layer
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%dc", (int)temp_tuple->value->int32);
    text_layer_set_text(s_temp_layer, temperature_buffer);
    
    //Translate condition value
    int condint=(int)conditions_tuple->value->int32;
    snprintf(icon_buffer, sizeof(weathericon_tuple), "%s", weathericon_tuple->value->cstring);
      
    code_to_text(condint,icon_buffer,s_wicon_layer);
    
  }  
}


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



// Configure the first line of text
void configureLineLayer(TextLayer *textlayer, bool right) {
	text_layer_set_text_color(textlayer, settings.ForegroundColor);
	text_layer_set_background_color(textlayer, GColorClear);
        if (right) {
          text_layer_set_text_alignment(textlayer, GTextAlignmentRight);
        } else {
          text_layer_set_text_alignment(textlayer, GTextAlignmentCenter);
        }
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
	}, current);
	
	animation_schedule(property_animation_get_animation(line->currentAnimation));
}

// Pop down to center before initial display when only 2 lines of text
void makePopDown(){
	
	GRect rect = layer_get_bounds((Layer *)scroll);
	rect.origin.y = 21;
	layer_set_bounds(scroll, rect);
}
static void prv_window_load(Window *window) {
   Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);

  back_layer = layer_create(bounds);
	layer_set_update_proc(back_layer, back_update_proc);

	layer_add_child(window_layer, back_layer);  
 
  prv_update_display();
}

	

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
	} else {
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


// Update screen based on new time
void display_time(struct tm *t) {
	// The current time text will be stored in the following 3 strings
	char textLine1[BUFFER_SIZE];
	char textLine2[BUFFER_SIZE];
	char textLine3[BUFFER_SIZE];
	
	time_to_3words(t->tm_hour, t->tm_min, textLine1, textLine2, textLine3,BUFFER_SIZE);
	
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

	// Update back layer (indicators for current time, sunrise, sunset, day of week, and date)
	if (units_changed & MINUTE_UNIT ) {
		layer_mark_dirty(back_layer);  
	}
	
	// Update text time
	display_time(t);
	
	// Recenter screen if last time was 3 lines, but new time is 2 lines
	// Don't do this if time was just initialized already centered
  //optimized for spanish
	
		if(t->tm_min == 0 || t->tm_min == 20 || t->tm_min == 30  ){
			if(PoppedDownNow == false){
				makeScrollDown();
			}
		}
	
		// Prepare for next time being 3 lines, if current time is 2 lines
		if(t->tm_min == 15 || t->tm_min == 20 || t->tm_min == 30  ){
			makeScrollUp(t);
			}
 // Get weather update every 30 minutes
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
  
  window_stack_push(s_main_window, true);
  
  Layer *root = window_get_root_layer(s_main_window);
	bounds = layer_get_bounds(root);
	int offset = (bounds.size.h - 145) / 2;
  int middlescreen=bounds.size.w/2;
  	
  //Layers for weather
  
  // Create temperature Layer
  s_temp_layer = text_layer_create(
      GRect(0,  bounds.size.h - 44, middlescreen-25, 30));
  // Style the text
    text_layer_set_background_color(s_temp_layer, GColorClear);
    text_layer_set_text_color(s_temp_layer, settings.ForegroundColor);
    text_layer_set_text_alignment(s_temp_layer, GTextAlignmentRight);
    //text_layer_set_text(s_temp_layer, "");
    text_layer_set_font(s_temp_layer,fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
       layer_add_child(window_get_root_layer(s_main_window), text_layer_get_layer(s_temp_layer));

  // Create icon layer
  
  
  // Create GFont
  s_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_WEATHER_ICON_26));
  //Create layer for icons
  s_wicon_layer=text_layer_create( 
   GRect(110,  bounds.size.h - 44, 30, 30));
  
  text_layer_set_background_color(s_wicon_layer, GColorClear);
  text_layer_set_text_color(s_wicon_layer, settings.ForegroundColor);
  text_layer_set_text_alignment(s_wicon_layer, GTextAlignmentLeft);
  text_layer_set_font(s_wicon_layer, s_weather_font);
  //Sample
  //text_layer_set_text(s_wicon_layer, "4");
  layer_add_child(window_get_root_layer(s_main_window), text_layer_get_layer(s_wicon_layer));
  
  
  
  
	scroll = layer_create(bounds);
  

  
// 1st line layer
	line1.currentLayer = text_layer_create(GRect(bounds.origin.x, offset, bounds.size.w, 50));
	line1.nextLayer = text_layer_create(GRect(bounds.size.w, offset, bounds.size.w, 50));
	configureLineLayer(line1.currentLayer, false);
	configureLineLayer(line1.nextLayer, false);
  text_layer_set_font(line1.currentLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_font(line1.nextLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  
	// 2nd line layer
	line2.currentLayer = text_layer_create(
                        GRect(0, 37 + offset, bounds.size.w, 50));
	line2.nextLayer = text_layer_create(
                        GRect(bounds.size.w, 37 + offset, bounds.size.w, 50));
	configureLineLayer(line2.currentLayer, false);
	configureLineLayer(line2.nextLayer, false);

	// 3rd line layer
	line3.currentLayer = text_layer_create(
                        GRect(0, 74 + offset, bounds.size.w, 50));
	line3.nextLayer = text_layer_create(
                        GRect(bounds.size.w, 74 + offset, bounds.size.w, 50));
	configureLineLayer(line3.currentLayer, false);
	configureLineLayer(line3.nextLayer, false);

  text_layer_set_font(line2.currentLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  text_layer_set_font(line2.nextLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  text_layer_set_font(line3.currentLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  text_layer_set_font(line3.nextLayer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  
  	// Configure text time on init
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	display_time(t);
  

  
// Load layers
	layer_add_child(root, scroll);
	layer_add_child(scroll, (Layer *)line1.currentLayer);
	layer_add_child(scroll, (Layer *)line1.nextLayer);
	layer_add_child(scroll, (Layer *)line2.currentLayer);
	layer_add_child(scroll, (Layer *)line2.nextLayer);
	layer_add_child(scroll, (Layer *)line3.currentLayer);
	layer_add_child(scroll, (Layer *)line3.nextLayer);
  

	// Register for minute ticks
	tick_timer_service_subscribe(MINUTE_UNIT, time_timer_tick);
	
	// inititialize PoppedDown indicators
	PoppedDownNow = false;
	PoppedDownAtInit = false;
	//////////////////////////////////////
  
  // If initial display of time is only 2 lines of text, display centered
  // optimized for spanish

		if(t->tm_min <= 15 || t->tm_min == 20 || t->tm_min == 30 ){
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


