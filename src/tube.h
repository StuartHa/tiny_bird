#include <pebble.h>

typedef struct {
  int x;
  int y;
} tube_t;

void tube_draw(tube_t *tube, GContext *ctx);
void tube_update_state(tube_t *tube, int delta_t);
tube_t *tube_create(int x, int y);
void tube_delete(tube_t *tube);