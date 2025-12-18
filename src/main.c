#include <stdio.h>
#include <bcm2835.h>
#include "st7789.h"
#include <stdbool.h>
#include <unistd.h>

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
		for (int j=0; j<240; j++) screen[i][j] = 0x0000;
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
