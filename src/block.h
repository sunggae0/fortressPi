#pragma once

#include <unistd.h>
#include "render.h"
#iunclude "stdbool.h"

typedef struct {
    uint16_t x;
    uint16_t y;
    bool alive;
} Block;


void block_render(const Block* b);
void block_collider(Bullet* bullet);