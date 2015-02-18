#include "ground.h"

static GBitmap *s_ground;

static void s_init(void);

void ground_draw(ground_t *ground, GContext *ctx) {
  if (!s_ground) {
    s_init();
  }

  graphics_draw_bitmap_in_rect(ctx, s_ground, (GRect) {.origin = {ground->x, ground->y}, .size = {170, 10}});
}

//TODO: calculate using delta_t
void ground_update_state(ground_t *ground, int delta_t) {
  ground->x -= 2;
}

ground_t *ground_create(int x, int y) {
  ground_t *new_ground = malloc(sizeof(ground_t));
  new_ground->x = x;
  new_ground->y = y;

  return new_ground;
}

void ground_delete(ground_t *ground) {
  free(ground);
}

static void s_init(void) {
  s_ground = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GROUND);

}