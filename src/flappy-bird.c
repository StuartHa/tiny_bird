#include <pebble.h>
#include "title.h"
#include "bird.h"
#include "game.h"

static Window *window;
static Layer *layer;


GBitmap* ground;
int y, int_y;
int v, int_v;
int ground_x;
int tube_x1, tube_x2;
int tube_y1, tube_y2;
bool title;
bool beginning_stage;
bool collision;
bool title_cb_var;
int score = 0;
int best_score = 0;
char score_str[20];
char best_score_str[20];
bool unscore;

static void update_game_state(void) {

}

void beginning_stage_cb(void* p) {
  beginning_stage = false;
  tube_x1 = 144;
  tube_y1 = 15 + rand() % 65;
  tube_x2 = 230;
  tube_y2 = 15 + rand() % 65;
}

static void button_click_handler(void) {
  if(title) {
    title = false;
    collision = false;
    title_cb_var = false;
    ground_x = 0;
    beginning_stage = true;
    app_timer_register(4000, beginning_stage_cb, NULL);
    int_v = -26;
    v = -3;
    int_y = 500;
    y = 50;
    tube_x1 = 10000;
    tube_x2 = 10000;
    unscore = false;
  } else if (!collision){
  int_v = -26;
  v = -3;
  }
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, game_up_click_handler);
}

void update_cb(Layer* layer, GContext* ctx) {
    
  if(title) {
    if( score > best_score) {
      best_score = score;
      persist_write_int(42, best_score);
    }
    score = 0;

    title_draw(ctx, &best_score);
  } else {
//    bird_draw(bird);
//    ground_draw();
//    tube_draw(tube1);
//    tube_draw(tube2);


    graphics_draw_bitmap_in_rect(ctx, ground, (GRect) {.origin = {ground_x, 158}, .size = {170, 10}});

    if(!beginning_stage) {
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_rect(ctx, (GRect) {.origin = {tube_x1, 158 - tube_y1}, .size = {25, tube_y1}}, 0, GCornerNone);
    graphics_fill_rect(ctx, (GRect) {.origin = {tube_x1 - 2, 158 - tube_y1 - 10}, .size = {29, 10}}, 0, GCornerNone);
    
    graphics_fill_rect(ctx, (GRect) {.origin = {tube_x1, 0}, .size = {25, 158 - tube_y1 - 20 - 55}}, 0, GCornerNone);
    graphics_fill_rect(ctx, (GRect) {.origin = {tube_x1 - 2, 158 - tube_y1 - 20 - 55}, .size = {29, 10}}, 0, GCornerNone);


    graphics_fill_rect(ctx, (GRect) {.origin = {tube_x2, 158 - tube_y2}, .size = {25, tube_y2}}, 0, GCornerNone);
    graphics_fill_rect(ctx, (GRect) {.origin = {tube_x2 - 2, 158 - tube_y2 - 10}, .size = {29, 10}}, 0, GCornerNone);
    
    graphics_fill_rect(ctx, (GRect) {.origin = {tube_x2, 0}, .size = {25, 158 - tube_y2 - 20 - 55}}, 0, GCornerNone);
    graphics_fill_rect(ctx, (GRect) {.origin = {tube_x2 - 2, 158 - tube_y2 - 20 - 55}, .size = {29, 10}}, 0, GCornerNone);
    }

    graphics_fill_rect(ctx, (GRect) {.origin = {100, 7 }, .size = {35, 25}}, 2, GCornersAll);
    snprintf(score_str, 3, "%i", score);
    graphics_draw_text(ctx, score_str, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21), (GRect) {.origin = {100,7}, .size = {35,25}}, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
 }
}



void title_cb(void* b) {
  title = true;
  collision = false;
  beginning_stage = false;
  int_y = 500; 
  y = 50;
  title_cb_var = false;
}


void timer_cb(void* d) {
  int a = 1, t = 3;
  if(!title) {
  int_y += int_v*t + a*t*t;
  int_v += a*t;
  }
  if(!collision) {
    //collision = collision_occured();
    if(collision)
      vibes_short_pulse();
  }
  y = int_y / 10;
  v = int_v / 10; 
  if(y >= 141) {
    y = 141;
    if(!title_cb_var) {
      title_cb_var = true;
      app_timer_register(1000, title_cb, NULL);
    }
  }
  if(!title && !collision) {
  if(tube_x1 < 10 + 7 && !unscore) {
    score++;
    unscore = true;
  }}

  if(!collision) {
  ground_x-=2;
  tube_x1-=2;
  tube_x2-=2;
  }
  if(tube_x1 < -20) {
    unscore = false;
    tube_x1 = tube_x2;
    tube_y1 = tube_y2;

    tube_x2 = 144;
    tube_y2 = 15 + rand() % 65;
  }
  if(ground_x < -11)
    ground_x = 0;
  layer_mark_dirty(layer);
  app_timer_register(50, timer_cb, NULL);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  layer = layer_create(bounds);
  //layer_set_update_proc(layer, update_cb);
  layer_add_child(window_layer, layer);


  //app_timer_register(50, timer_cb, NULL);
  game_init();
  game_start(layer);
}

static void window_unload(Window *window) {
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  light_enable(true);
  window_set_fullscreen(window, true);
  window_stack_push(window, animated);

  srand(time(NULL));
  tube_x1 = 100000;
  tube_x2 = 100000;
  title = true;
  if( persist_exists(42) ) {
    best_score = persist_read_int(42);
  }
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
