#pragma once

#define	MAXLEN	2000	/* maximum snake length */
#define	CHEAD	'o'
#define	CBODY	'o'
#define	CFRUIT	'#' 

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
	CELL	body[MAXLEN];
	DIR	dir;
	int		length;
	int		score;
} SNAKE; 