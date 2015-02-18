#include <pebble.h>
#include "game.h"

static Window *window;
static Layer *layer;

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, game_up_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  layer = layer_create(bounds);
  layer_add_child(window_layer, layer);

  game_init();
  game_start(layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load
  });
  const bool animated = true;
  window_set_fullscreen(window, true);
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
