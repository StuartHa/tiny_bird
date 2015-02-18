#include <pebble.h>
#include "title.h"

static GBitmap *s_bird;
static GBitmap *s_ground;
static char s_score_text[20];

void title_draw(GContext* ctx, int *score) {
  if (!s_bird || !s_ground) {
    s_bird = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_20_DEG);
    s_ground = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND);
  }

  graphics_context_set_text_color(ctx, GColorBlack);

  graphics_draw_text(ctx, "Tiny Bird", fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK), (GRect) {.origin = {0,0}, .size = {144, 40}}, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  graphics_draw_text(ctx, "PRESS UP", fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), (GRect) {.origin = {0,95}, .size = {144, 40}}, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);

  graphics_draw_bitmap_in_rect(ctx, s_bird, (GRect) {.origin = {10, 50}, .size = {30, 19}});
  graphics_draw_bitmap_in_rect(ctx, s_ground, (GRect) {.origin = {0, 158}, .size = {170, 10}});

  if(score) {
    snprintf(s_score_text, 20, "Best: %i", *score);
    graphics_draw_text(ctx, s_score_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), (GRect) {.origin = {0,125}, .size = {144, 40}}, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  }
}