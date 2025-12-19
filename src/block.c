#include <unistd.h>
#include "render.h"
#include "block.h"

Block blocks[9] = {
    {175,125,true},
    {160,140,true}, {175,140,true}, {190,140,true},
    {145,155,true}, {160,155,true}, {175,155,true}, {190,155,true}, {205,155,true}
};


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
