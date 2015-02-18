#include <pebble.h>

typedef struct {
  int x;
  int y;
} ground_t;

void ground_draw(ground_t *ground, GContext *ctx);
void ground_update_state(ground_t *ground, int delta_t);
ground_t *ground_create(int x, int y);
void ground_delete(ground_t *ground);