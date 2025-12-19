#include <stdio.h>
#include <bcm2835.h>
#include "render.h"
#include <stdbool.h>
#include <unistd.h>
#include "player.h"
#include "bullet.h"


#define JOY_UP      17
#define JOY_DOWN    22
#define JOY_LEFT    27
#define JOY_RIGHT   23
#define BTN_5	    5
#define BTN_6	    6

uint16_t screen[240][240] = {0};
bool input[6] = {false, false, false, false, false, false};

int x = 125;
int y = 125;
int r = 5;

bool ballFlag = false;
int ballTime = 0;
int g = 10;
int ball_y = 150;
int ball_x=0;

void clear(){
	for (int i=0; i<240; i++){
		for (int j=0; j<240; j++) screen[i][j] = 0xCDFF;
	}
}

void setPixel(int x, int y){
    if (x>=0 && x<240 && y>=0 && y<240) screen[y][x] = 0xFFFF;
}

void draw(uint16_t x, uint16_t y, bitmap img){
	uint16_t idx = 0;
	for (uint16_t i=y; i<y+img.height; i++){
		for (uint16_t j=x; j<x+img.width; j++){
			if (i<240 && j<240) screen[i][j] = img.bitmap[idx];
			idx++;
		}
	}
}

void drawSquare(int x, int y, int size){
    for (int i=y; i<y+size; i++){
		for (int j=x; j<x+size; j++){
			 if (i>=0 && i<240 && j>=0 && j<240) screen[i][j] = 0x0000;
		 }
     }
 }

void drawCircle(int cx, int cy, int r){
    int x=r;
    int y=0;
    int d = 1-r;
    
    while (x >= y){
	setPixel(cx + x, cy + y);
	setPixel(cx - x, cy + y);
	setPixel(cx + x, cy - y);
	setPixel(cx - x, cy - y);
	
	setPixel(cy + y, cx + x);
	setPixel(cy - y, cx + x);
	setPixel(cy + y, cx - x);
	setPixel(cy - y, cx - x);
	
	y++;
	
	if (d < 0) d += 2*y + 1;
	else{
	    x--;
	    d += 2*(y-x) + 1;
	}
    }
}


int main(void){

	if (!bcm2835_init()) {
        printf("bcm2835_init failed. Are you running as root?\n");
        return 1;
    }
    
    bcm2835_gpio_fsel(TFT_DC, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(TFT_RST, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(26, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_set(26);
    
    //joystick GPIO Setting: 
    bcm2835_gpio_fsel(JOY_UP, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(JOY_UP, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(JOY_DOWN, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(JOY_DOWN, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(JOY_LEFT, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(JOY_LEFT, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(JOY_RIGHT, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(JOY_RIGHT, BCM2835_GPIO_PUD_UP);
    
    bcm2835_gpio_fsel(BTN_5, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BTN_5, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(BTN_6, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BTN_6, BCM2835_GPIO_PUD_UP);

    ballFlag = false;

    Player player;
	Bullet bullet;

	player_init(&player, 45, 10, 0);
    st7789_init();
	while(1){
		input[0]=!bcm2835_gpio_lev(JOY_UP);
		input[1]=!bcm2835_gpio_lev(JOY_DOWN);
		input[2]=!bcm2835_gpio_lev(JOY_LEFT);
		input[3]=!bcm2835_gpio_lev(JOY_RIGHT);
		input[4]=!bcm2835_gpio_lev(BTN_5);
		input[5]=!bcm2835_gpio_lev(BTN_6);

		clear();

		

		if (input[4]){
			bullet_init(&bullet, player.x, player.y, player.angle, player.power, player.state);
		}

		player_update(&player);
		player_handle_input(&player, 0);

		player_render(&player);
		bullet_update(&bullet);
		bullet_render(&bullet);

		render_draw_rectangle(player.x+30, player.y-30, 3, player.power*3);
		
		render_screen();
	}
}
