#include "score.h"

static char s_score_text[3];

void score_draw(GContext *ctx, int x, int y, int score) {
  graphics_fill_rect(ctx, (GRect) {.origin = {100, 7 }, .size = {35, 25}}, 2, GCornersAll);
  snprintf(s_score_text, 3, "%i", score);
  graphics_draw_text(ctx, s_score_text, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21), (GRect) {.origin = {100,7}, .size = {35,25}}, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
}