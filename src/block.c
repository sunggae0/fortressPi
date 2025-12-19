#include <unistd.h>
#include "render.h"
#include "block.h"

Block blocks[9] = {
    {350,250,true},
    {320,280,true}, {350,280,true}, {380,280,true},
    {290,310,true}, {320,310,true}, {350,310,true}, {380,310,true}, {410,310,true}
}


void block_render(Block* b) {
    for (int i=0; i<9; i++){
        if (blocks[i].alive){
            render_draw_rectangle(blocks[i].x, blocks[i].y, 20, 20);
        }
    }
}

void block_collider(Bullet* bullet) {
    for (int i=0; i<9; i++){
        if (blocks[i].alive){
            if (bullet->x >= blocks[i].x && bullet->x <= blocks[i].x + 20 &&
                bullet->y >= blocks[i].y && bullet->y <= blocks[i].y + 20) {
                blocks[i].alive = false;
                bullet->alive = false;
            }
        }
    }
}
