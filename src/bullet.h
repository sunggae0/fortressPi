#define MAX_BULLETS 64

#include <unistd.h>
#include "render.h"

typedef struct {
    uint16_t alive;
    uint16_t x, y;
    uint16_t power;
    uint16_t angle;
    uint16_t tick;
} Bullet;

void bullet_init(Bullet* b, uint16_t x, uint16_t y, uint16_t angle, uint16_t power, uint16_t state);
void bullet_update(Bullet* b);
void bullet_render(const Bullet* b);