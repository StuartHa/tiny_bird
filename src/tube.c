#include "tube.h"

void tube_draw(tube_t *tube, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_fill_rect(ctx, (GRect) {.origin = {tube->x, 158 - tube->y}, .size = {25, tube->y}}, 0, GCornerNone);
  graphics_fill_rect(ctx, (GRect) {.origin = {tube->x - 2, 158 - tube->y - 10}, .size = {29, 10}}, 0, GCornerNone);

  graphics_fill_rect(ctx, (GRect) {.origin = {tube->x, 0}, .size = {25, 158 - tube->y - 20 - 55}}, 0, GCornerNone);
  graphics_fill_rect(ctx, (GRect) {.origin = {tube->x - 2, 158 - tube->y - 20 - 55}, .size = {29, 10}}, 0, GCornerNone);

//
//  graphics_fill_rect(ctx, (GRect) {.origin = {tube_x2, 158 - tube_y2}, .size = {25, tube_y2}}, 0, GCornerNone);
//  graphics_fill_rect(ctx, (GRect) {.origin = {tube_x2 - 2, 158 - tube_y2 - 10}, .size = {29, 10}}, 0, GCornerNone);
//
//  graphics_fill_rect(ctx, (GRect) {.origin = {tube_x2, 0}, .size = {25, 158 - tube_y2 - 20 - 55}}, 0, GCornerNone);
//  graphics_fill_rect(ctx, (GRect) {.origin = {tube_x2 - 2, 158 - tube_y2 - 20 - 55}, .size = {29, 10}}, 0, GCornerNone);
}

// TODO: This delta_x won't work for different delta_t
void tube_update_state(tube_t *tube, int delta_t) {
  int delta_x = delta_t * 2 / 3;
  tube->x -= delta_x;
}

tube_t *tube_create(int x, int y) {
  tube_t *new_tube = malloc(sizeof(tube_t));
  new_tube->x = x;
  new_tube->y = y;

  return new_tube;
}

void tube_delete(tube_t *tube) {
  free(tube);
}

