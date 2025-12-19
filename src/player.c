#include "player.h"
#include "render.h"
#include <stdbool.h>

extern bool input[6];

void player_init(Player* p, uint16_t angle, uint16_t power, uint16_t state) {
    p->angle = angle;
    p->power = power;
    p->state = state;
    p->x = 10;
    p->y = 200;
}

void player_handle_input(Player* p, int key) {
    // 예: WASD 이동
    if (input[0]) p->angle = (p->angle+2+30)%30;
    if (input[1]) p->angle = (p->angle-2+30)%30;
    if (input[2]) p->power -= (p->angle+2+20)%20;
    if (input[3]) p->power += (p->angle-2+20)%20;
}

void player_update(Player* p) {
    // 지금은 입력에서 바로 위치가 바뀌므로 update는 비어있어도 됩니다.
    // 나중에: 무적 시간, 애니메이션 프레임, 상태이상 등은 여기서 처리.
    (void)p;
}

void player_render(const Player* p) {
    render_draw_rectangle(p->x, p->y, 30, 30);
}
