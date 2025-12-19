#pragma once

#include <stdbool.h>
#include "bullet.h"


void bullet_init(Bullet* b, uint16_t x, uint16_t y, uint16_t angle, uint16_t power, uint16_t state) {
    b->alive = 1;
    b->x = x;
    b->y = y;
    b->angle = power;
    b->power = state? 5:10;
    b->tick = 0;
}


void bullet_update(Bullet* b) {
    if (!b->alive) return;
    if (b->y > 240 || b->x > 240) {
        b->alive = 0;
        return;
    }
    b->tick++;
    b->x += 5;
    b->y = 200 - b->angle*b->tick + b->tick*b->tick;
}

void bullet_render(const Bullet* b) {
    if (b->alive) render_draw_rectangle(b->x, b->y, 5, 5);
}


