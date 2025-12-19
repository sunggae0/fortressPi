#pragma once

#include <unistd.h>
#include "render.h"
#include "stdbool.h"
#include "bullet.h"

typedef struct {
    uint16_t x;
    uint16_t y;
    bool alive;
} Block;

extern Block blocks[9];

void block_render(Block* b);
void block_collider(Bullet* bullet);