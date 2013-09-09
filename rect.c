//MONTEK SINGH
#include <stdlib.h>
#include <debugging.h>
#include "list.h"
#include "myLib.h"
#include <stdio.h>

typedef struct
{
	int r; // or y
	int c; // or x
	int dr;
	int dc;
	int width;
	int height;
	int color;
} Rectangle;

enum {REDIDX, GREENIDX, BLUEIDX, CYANIDX, MAGENTAIDX, YELLOWIDX, WHITEIDX, LTGRAYIDX, BLACKIDX};

void clear(void);
void update(void);
void draw(void);
Rectangle* create_rect(void);
void draw_rect(void* rect);
void update_rects(void* rect);
void free_rectangle(void* data);


/* Initialize any global variables here */
Rectangle cursor;
list* llist;

const int dels[] = {-3, -2, -1, 1, 2, 3};
int numdels;


/* Note you will have to define additional functions to implement the functionality in the assignment*/

int main(void){
	/* SET UP REG_DISPCNT */
	REG_DISPCTL = MODE4 | BG2_ENABLE;
	u16 colors[] = {RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE};
	int numcolors = sizeof(colors)/sizeof(colors[0]);
	for(int i=0; i<numcolors; i++)
	{
		PALETTE[i] = colors[i];
	}

	/* INITIALIZE OR SET UP ANY VARIABLES YOU WANT */
	cursor.r = 80;
	cursor.c = 120;
	cursor.dr = 80;
	cursor.dc = 120;
	cursor.width = 3;
	cursor.height = 3;
	cursor.color = REDIDX;
	

	numdels = 6;
	
	llist = create_list();
	
	while(1){
		/* You shouldn't need to change this part implement the game functionality in the three functions I have defined below */
		
		
		waitForVblank();
		clear();
		update();
		draw();
	}
	
}

/* You should clear any objects drawn in the previous frame here */
void clear(void){
	fillScreen4(BLACKIDX);
	
}

/* You should handle any key input in this function and update the game state */
void update(void){
	
	if(KEY_DOWN_NOW(BUTTON_UP)){
		cursor.r--;
		if(cursor.r < 0){
			cursor.r = 0;
		}
	}
	if(KEY_DOWN_NOW(BUTTON_DOWN)){
		cursor.r++;
		if(cursor.r > 120){
			cursor.r = 120;
		}
			
	}
	if(KEY_DOWN_NOW(BUTTON_LEFT)){
		cursor.c--;
		if(cursor.c < 0){
			cursor.c = 0;
		}
			
	}
	if(KEY_DOWN_NOW(BUTTON_RIGHT)){
		cursor.c++;
		if(cursor.c > 240){
			cursor.c = 240;
		}
	}
	if(KEY_DOWN_NOW(BUTTON_A)){
		push_front(llist, create_rect());
	}
	if(KEY_DOWN_NOW(BUTTON_B)){
		remove_front(llist, free_rectangle);
	}
	
	if(KEY_DOWN_NOW(BUTTON_START)){
		empty_list(llist, free_rectangle);
	}

	traverse(llist, update_rects);
}
/* You should draw all of your objects here */
void draw(void){
	//draw curosr
	drawRect4(cursor.r, cursor.c, cursor.height, cursor.width, cursor.color);
	//draw rects
	traverse(llist, draw_rect);
	
	FlipPage();
}

Rectangle* create_rect(void){
	
	Rectangle* rect = malloc(sizeof(Rectangle));
	if(rect == NULL){
		printf("Malloc Error\n");
		return 0;
	}
	rect->r = cursor.r;
	rect->c = cursor.c;
	rect->dr = dels[rand()%numdels];	
	rect->dc = dels[rand()%numdels];	
	rect->height = 5;
	rect->width = 5;
	rect->color = rand()%8;
	
	return rect;
}

void draw_rect(void* rect){
	drawRect4( ((Rectangle*)rect)->r, ((Rectangle*)rect)->c, ((Rectangle*)rect)->height, ((Rectangle*)rect)->width, ((Rectangle*)rect)->color );
	
}

void update_rects(void* rect){
	((Rectangle*)rect)->r += ((Rectangle*)rect)->dr;
	((Rectangle*)rect)->c += ((Rectangle*)rect)->dc;
	if( ((Rectangle*)rect)->r > 160-((Rectangle*)rect)->height || ((Rectangle*)rect)->r < 0){
		((Rectangle*)rect)->dr = -((Rectangle*)rect)->dr;
	}
	if( ((Rectangle*)rect)->c > 240-((Rectangle*)rect)->width || ((Rectangle*)rect)->c < 0){
		((Rectangle*)rect)->dc = -((Rectangle*)rect)->dc;
	}
}

void free_rectangle(void* data){
	// free structure.
	free(data);
}

