// 10 mp = 1 pixel
typedef struct {
  int x_mp;
  int y_mp;
  int v_mp;
} bird_t;

void bird_draw(bird_t *bird, GContext *ctx);
void bird_flap(bird_t *bird);
void bird_update_state(bird_t *bird, int delta_t);

bird_t *bird_create(int x_mp, int y_mp, int v_mp);
void bird_delete(bird_t *bird);


