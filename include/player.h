#ifndef PLAYER_H
#define PLAYER_H

#include <unistd.h>
#include "render.h"

typedef struct {
    uint16_t angle;
    uint16_t power;

    uint16_t state;
    
} Player;

void player_init(Player* p, uint16_t angle, uint16_t power, uint16_t state);
void player_handle_input(Player* p, int key);
void player_update(Player* p);
void player_render(const Player* p);

#endif
