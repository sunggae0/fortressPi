#define MAX_BULLETS 64

typedef struct {
    int alive;
    int x, y;
    int vx, vy;
} Bullet;

typedef struct {
    Bullet list[MAX_BULLETS];
    int count;
} BulletManager;

void bullets_init(BulletManager* bm);
void bullets_fire(BulletManager* bm, int x, int y, int vx, int vy);
void bullets_update_all(BulletManager* bm);
void bullets_render_all(const BulletManager* bm);
