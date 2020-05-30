#pragma once

#define	MAX_LENGTH	1000	/* maximum snake length */
#define	HEAD_SHAPE	'o'
#define	BODY_SHAPE	'o'
#define	FRUIT_SHAPE	'#'

/* -- GAME LOGIC -- */
typedef struct fruit
{
	int x, y, color;
} FRUIT;

typedef struct cell
{
	int x, y;
} CELL;

typedef enum direction
{
	up, down, left, right
} DIR;

typedef struct snake
{
	CELL	body[MAX_LENGTH];
	DIR	dir;
	int		length;
	int		score;
} SNAKE; 

/* move the cursor to position (x,y) */
void gotoxy(int x, int y);

/* display a character at position (x,y) using color c */
void writecat(int x, int y, int c, const char ch);

/* draw a horizontal line of with w at position (x,y), using color c */
void hline(int x, int y, int w, int c);

/* draw a frame of size w x h at position (x,y), using color c */
void frame(int x, int y, int w, int h, int c);

/* draw a box of size w x h at position (x,y), using color c */
void box(int x, int y, int w, int h, int c);

/* same as box but has a title at the top of the box */
void dialog(int x, int y, int w, int h, int c, const char * title);