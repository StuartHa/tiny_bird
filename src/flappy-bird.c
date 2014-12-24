#include <pebble.h>

static Window *window;
static Layer *layer;

GBitmap* pos_20_deg; 
GBitmap* pos_10_deg;
GBitmap* pos_0_deg;
GBitmap* neg_pos_10_deg;
GBitmap* neg_pos_20_deg;
GBitmap* neg_30_deg;
GBitmap* neg_50_deg;
GBitmap* neg_70_deg;
GBitmap* neg_90_deg;
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

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  button_click_handler();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  button_click_handler();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  button_click_handler();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

void update_cb(Layer* layer, GContext* ctx) {
    
  if(title) {
    if( score > best_score) {
      best_score = score;
      persist_write_int(42, best_score);
    }
    score = 0;

    graphics_context_set_text_color(ctx, GColorBlack);
    graphics_draw_text(ctx, "Tiny Bird", fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK), (GRect) {.origin = {0,0}, .size = {144, 40}}, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
    graphics_draw_bitmap_in_rect(ctx, pos_20_deg, (GRect) {.origin = {10, 50}, .size = {30, 19}});


    graphics_draw_text(ctx, "PRESS ANY BUTTON", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), (GRect) {.origin = {0,70}, .size = {144, 40}}, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  
    graphics_draw_bitmap_in_rect(ctx, ground, (GRect) {.origin = {0, 158}, .size = {170, 10}});
    if(best_score > 0) {
      snprintf(best_score_str, 20, "Best: %i", best_score);
    graphics_draw_text(ctx, best_score_str, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), (GRect) {.origin = {0,125}, .size = {144, 40}}, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
    }
  } else {

    if(int_v < -6){
      graphics_draw_bitmap_in_rect(ctx, pos_20_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
    }
    else if(int_v < 0) {
      graphics_draw_bitmap_in_rect(ctx, pos_10_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
     }
    else if(int_v < 6) {
      graphics_draw_bitmap_in_rect(ctx, pos_0_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
      }
    else if(int_v <  13) {
      graphics_draw_bitmap_in_rect(ctx, neg_pos_10_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
    }
    else if(int_v < 17) {
      graphics_draw_bitmap_in_rect(ctx, neg_pos_20_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
    }
    else if(int_v < 22) {
      graphics_draw_bitmap_in_rect(ctx, neg_30_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
    }
    else if(int_v < 27) {
      graphics_draw_bitmap_in_rect(ctx, neg_50_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
    }
    else if(int_v < 32) {
      graphics_draw_bitmap_in_rect(ctx, neg_70_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
    }
    else {
      graphics_draw_bitmap_in_rect(ctx, neg_90_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
    }

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

bool collision_occured(void) {
  if(y >= 141)
    return true;
  if(beginning_stage || title)
    return false;
  if(tube_x1 < 10 + 19 && tube_x1 > 10 && y >= 158 - tube_y1)
    return true;  
  if(tube_x1 < 10 + 19 && tube_x1 > 10 && y < 158 - tube_y1 - 20 - 55)
    return true;
  if(tube_x1 - 2 < 10 + 19 && tube_x1 +25 + 2 > 10 + 19 && y < 158 - tube_y1 && y >= 158 - tube_y1 - 10)
    return true;  

  if(tube_x1 - 2 < 10 + 19 && tube_x1 + 25 + 2 > 10 + 19 && y + 18 < 158 - tube_y1 && y  + 18>= 158 - tube_y1 - 10)
    return true;  

  if(tube_x1 - 2 < 10 + 19 && tube_x1 +25 +2 > 10 + 19 && y <= 158 - tube_y1 - 10 - 55 && y > 158 - tube_y1 - 10 - 55 - 10)
    return true;  


  return false;
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
    collision = collision_occured();
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
  layer_set_update_proc(layer, update_cb);
  layer_add_child(window_layer, layer);
  y = 50;
  int_y = 500;
  app_timer_register(50, timer_cb, NULL);
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
  pos_20_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_20_DEG);
  pos_10_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_10_DEG);
  pos_0_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_0_DEG);
  neg_pos_10_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_10_DEG);
  neg_pos_20_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_20_DEG);
  neg_30_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_30_DEG);
  neg_50_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_50_DEG);
  neg_70_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_70_DEG);
  neg_90_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_90_DEG);
  ground = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND);
  srand(time(NULL));
  tube_x1 = 100000;
  tube_x2 = 100000;
  title = true;
  if( persist_exists(42)) {
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
