#include <pebble.h>
#include "bird.h"
#include "title.h"
#include "tube.h"
#include "ground.h"
#include "score.h"

#define SCORE_PERSIST_KEY (42)

static bird_t *s_bird;
static ground_t *s_ground;
static tube_t *s_tube1;
static tube_t *s_tube2;

static int s_best_score;
static int s_current_score;

static bool s_on_title_screen;
static bool s_in_beginning_stage;
static bool s_collision_occurred;

static Layer *s_game_layer;
static AppTimer *s_game_over_time;
static AppTimer *s_beginning_stage_time;

static void s_exit_no_tube_stage(void *data);
static bool s_has_collision_occured(void);
static void s_go_to_title_screen(void *data);
static void s_reset_game_state(void);

void game_init(void) {
  s_reset_game_state();
  srand(time(NULL));

  if(persist_exists(SCORE_PERSIST_KEY)) {
    s_best_score = persist_read_int(SCORE_PERSIST_KEY);
  }
}

void game_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (s_on_title_screen) {
    s_on_title_screen = false;
    s_in_beginning_stage = true;

    s_beginning_stage_time = app_timer_register(4000, s_exit_no_tube_stage, NULL);
  } else {
    if (!s_collision_occurred) {
      bird_flap(s_bird);
    }
  }
}

void game_render(Layer *layer, GContext *ctx) {
  if (s_on_title_screen) {
    title_draw(ctx, &s_best_score);
  } else {
    bird_draw(s_bird, ctx);
    if (!s_in_beginning_stage) {
      tube_draw(s_tube1, ctx);
      tube_draw(s_tube2, ctx);
    }
    score_draw(ctx, 100, 7, s_current_score);
  }
  ground_draw(s_ground, ctx);
}

void game_state_update(void *data) {
  int delta_t = (int)data;

  if (!s_on_title_screen) {
    bird_update_state(s_bird, delta_t);

    if(s_bird->y_mp == 141 * 10 && !s_game_over_time) {
      s_game_over_time = app_timer_register(1000, s_go_to_title_screen, NULL);
    }
    if (!s_collision_occurred) {
      ground_update_state(s_ground, delta_t);

      if (!s_in_beginning_stage) {
        int tube1_old_x = s_tube1->x;
        tube_update_state(s_tube1, delta_t);
        tube_update_state(s_tube2, delta_t);

        if (s_tube1->x < 17 && tube1_old_x > 17) {
          s_current_score++;
        }

        if (s_tube1->x < -20) {
          tube_delete(s_tube1);
          s_tube1 = s_tube2;
          s_tube2 = tube_create(144, 15 + rand() % 65);
        }
      }

      if (s_has_collision_occured()) {
        vibes_short_pulse();
        s_collision_occurred = true;
      }
    }
    if (s_ground->x < -11) {
      s_ground->x = 0;
    }
  }

  app_timer_register(50, game_state_update, data);
  layer_mark_dirty(s_game_layer);
}

void game_start(Layer *game_layer) {
  s_game_layer = game_layer;

  layer_set_update_proc(s_game_layer, game_render);

  int *time_step = (int *)3;
  app_timer_register(50, game_state_update, time_step);
}

static bool s_has_collision_occured(void) {
  int y = s_bird->y_mp / 10;
  if(y >= 141)
    return true;
  if(s_in_beginning_stage || s_on_title_screen)
    return false;
  if(s_tube1->x < 10 + 19 && s_tube1->x > 10 && y >= 158 - s_tube1->y)
    return true;
  if(s_tube1->x < 10 + 19 && s_tube1->x > 10 && y < 158 - s_tube1->y - 20 - 55)
    return true;
  if(s_tube1->x - 2 < 10 + 19 && s_tube1->x +25 + 2 > 10 + 19 && y < 158 - s_tube1->y && y >= 158 - s_tube1->y - 10)
    return true;
  if(s_tube1->x - 2 < 10 + 19 && s_tube1->x + 25 + 2 > 10 + 19 && y + 18 < 158 - s_tube1->y && y  + 18>= 158 - s_tube1->y - 10)
    return true;
  if(s_tube1->x - 2 < 10 + 19 && s_tube1->x +25 +2 > 10 + 19 && y <= 158 - s_tube1->y - 10 - 55 && y > 158 - s_tube1->y - 10 - 55 - 10)
    return true;

  return false;
}

static void s_exit_no_tube_stage(void *data) {
  s_in_beginning_stage = false;
  s_tube1 = tube_create(144, 15 + rand() % 65);
  s_tube2 = tube_create(230, 15 + rand() % 65);
}

static void s_go_to_title_screen(void *data) {
  if (s_current_score > s_best_score) {
    s_best_score = s_current_score;
    persist_write_int(SCORE_PERSIST_KEY, s_best_score);
  }

  s_reset_game_state();
}

static void s_reset_game_state(void) {
  s_on_title_screen = true;
  s_collision_occurred = false;
  s_game_over_time = NULL;
  s_current_score = 0;

  bird_delete(s_bird);
  ground_delete(s_ground);
  if (!s_in_beginning_stage) {
    tube_delete(s_tube1);
    tube_delete(s_tube2);
  }

  app_timer_cancel(s_beginning_stage_time);

  s_bird = bird_create(10, 50, 0);
  s_ground = ground_create(0, 158);

  s_in_beginning_stage = false;
}