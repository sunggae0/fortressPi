#include <stdio.h>
#include <bcm2835.h>
#include "render.h"
#include <stdbool.h>
#include <unistd.h>
#include "emoji.h"

#define JOY_UP      17
#define JOY_DOWN    22
#define JOY_LEFT    27
#define JOY_RIGHT   23
#define BTN_5	    5

uint16_t screen[240][240] = {0x0000,};

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
			 if (i>=0 && i<240 && j>=0 && j<240) screen[i][j] = 0xFFFF;
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
    
    ballFlag = false;

    
    st7789_init();
	while(1){
	clear();
	render_put(20,7,&emoji_bitmap);
	render_screen();
}
}
