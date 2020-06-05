#pragma once
#include <stdbool.h>
#include "ui.h"
#define	MAX_LENGTH	1000	/* maximum snake length */
#define	HEAD_SHAPE	'o'
#define	BODY_SHAPE	'o'
#define	FRUIT_SHAPE	'#'
#define	HEAD_COLOR	15
#define	BODY_COLOR	8

/* -- GAME LOGIC -- */
typedef struct fruit
{
	CELL pos;
	int color;
} FRUIT;

typedef enum direction
{
	up, down, left, right
} DIR;

typedef struct snake
{
	CELL	body[MAX_LENGTH];
	DIR	dir;
	int		length;
} SNAKE;

/* move the cursor to position (x,y) */
void gotoxy(int x, int y);

void writecat(int x, int y, int c, const char ch);

bool rightMax(int a, int b);

bool isSameValue(int leftValue, int rightValue);

bool isSamePosition(CELL* leftPos, CELL* rightPos);
/* check the collision between the snake's head and the boundaries */
bool isCollideBoundary(CELL snakePos, SCREEN* screen);
/* check the collision between the snake's head and the snake's body */
bool isCollideBody(SNAKE* snake);

/* check the collision between the snake's head and the fruit */
void isCollideFruit(SNAKE* snake, FRUIT* fruit, SCREEN screen, int* score);

bool isKeyInput(char* inputValue);

bool isDirUp(SNAKE* snake);

bool isDirDown(SNAKE* snake);

bool isDirLeft(SNAKE* snake);

bool isDirRight(SNAKE* snake);

bool isDirUpOrDown(SNAKE* snake);

bool isDirLeftOrRight(SNAKE* snake);

void changeDirUp(SNAKE* snake);

void changeDirDown(SNAKE* snake);

void changeDirLeft(SNAKE* snake);

void changeDirRight(SNAKE* snake);

/* update the snake head and body */
void moveSnake(SNAKE *snake);

/* update the snake body based on its head */
void updateBody(SNAKE *snake);

void updateHead(SNAKE* snake);

/* Check if number is even. Return true for even number */
bool isEven(int number);

/* Initiate and generate structure fruit using screen information */
void createFruit(SCREEN screen, FRUIT* fruit);

/* Initiate and generate structure snake using screen information */
void createSnake(SCREEN screen, SNAKE* snake);

/* draw one single 'character' at desired position 'pos' using 'color'*/
void drawChar(CELL pos, int color, const char ch);

/* draw snake and fruit into screen */
void drawObjects(SNAKE snake, FRUIT fruit);

