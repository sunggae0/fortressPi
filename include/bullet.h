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

typedef struct {
    Bullet list[MAX_BULLETS];
    int count;
} BulletManager;

void bullets_init(BulletManager* bm);
void bullets_fire(BulletManager* bm, uint16_t x, uint16_t y, uint16_t angle, uint16_t power, uint16_t state);
void bullets_update_all(BulletManager* bm);
void bullets_render_all(const BulletManager* bm);
