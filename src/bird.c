#include <pebble.h>
#include "bird.h"

static void s_init(void);

static GBitmap* s_pos_20_deg;
static GBitmap* s_pos_10_deg;
static GBitmap* s_pos_0_deg;
static GBitmap* s_neg_pos_10_deg;
static GBitmap* s_neg_pos_20_deg;
static GBitmap* s_neg_30_deg;
static GBitmap* s_neg_50_deg;
static GBitmap* s_neg_70_deg;
static GBitmap* s_neg_90_deg;

void bird_draw(bird_t *bird, GContext *ctx) {
  if (!s_pos_20_deg) {
    s_init();
  }
  int y = bird->y_mp / 10;
  
  if(bird->v_mp < -6){
    graphics_draw_bitmap_in_rect(ctx, s_pos_20_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
  }
  else if(bird->v_mp < 0) {
    graphics_draw_bitmap_in_rect(ctx, s_pos_10_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
  }
  else if(bird->v_mp < 6) {
    graphics_draw_bitmap_in_rect(ctx, s_pos_0_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
  }
  else if(bird->v_mp <  13) {
    graphics_draw_bitmap_in_rect(ctx, s_neg_pos_10_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
  }
  else if(bird->v_mp < 17) {
    graphics_draw_bitmap_in_rect(ctx, s_neg_pos_20_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
  }
  else if(bird->v_mp < 22) {
    graphics_draw_bitmap_in_rect(ctx, s_neg_30_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
  }
  else if(bird->v_mp < 27) {
    graphics_draw_bitmap_in_rect(ctx, s_neg_50_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
  }
  else if(bird->v_mp < 32) {
    graphics_draw_bitmap_in_rect(ctx, s_neg_70_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
  }
  else {
    graphics_draw_bitmap_in_rect(ctx, s_neg_90_deg, (GRect) {.origin = {10, y}, .size = {30, 19}});
  }
}

void bird_update_state(bird_t *bird, int delta_t) {
  int y = bird->y_mp / 10;

  if(y >= 141) {
    bird->y_mp = 141 * 10;
  } else {
    int y_accel_mp = 1;
    bird->y_mp += bird->v_mp * delta_t + y_accel_mp * delta_t * delta_t;
    bird->v_mp += y_accel_mp * delta_t;
  }


}

void bird_flap(bird_t *bird) {
  bird->v_mp = -26;
}

bird_t *bird_create(int x, int y, int v) {
  bird_t *new_bird = malloc(sizeof(bird_t));
  new_bird->x_mp = x * 10;
  new_bird->y_mp = y * 10;
  new_bird->v_mp = v * 10;

  return new_bird;
}

void bird_delete(bird_t *bird) {
  free(bird);
}

static void s_init(void) {
  s_pos_20_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_20_DEG);
  s_pos_10_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_10_DEG);
  s_pos_0_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_0_DEG);
  s_neg_pos_10_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_10_DEG);
  s_neg_pos_20_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_20_DEG);
  s_neg_30_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_30_DEG);
  s_neg_50_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_50_DEG);
  s_neg_70_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_70_DEG);
  s_neg_90_deg = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEG_90_DEG);
}