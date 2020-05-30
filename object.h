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