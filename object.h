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

bool rightMax(int a, int b);

bool isSameValue(int leftValue, int rightValue);

bool isSamePosition(CELL* leftPos, CELL* rightPos);
/* check the collision between the snake's head and the boundaries */
bool isCollideBoundary(CELL snakePos, SCREEN* screen);
/* check the collision between the snake's head and the snake's body */
bool isCollideBody(SNAKE* snake);

/* check the collision between the snake's head and the fruit */
void isCollideFruit(SNAKE* snake, FRUIT* fruit, SCREEN screen, int* score);

/* check if there is keyboard input */
bool isKeyInput(char* inputValue);

/* check if snake's direction is up */
bool isDirUp(SNAKE* snake);

/* check if snake's direction is down */
bool isDirDown(SNAKE* snake);

/* check if snake's direction is left */
bool isDirLeft(SNAKE* snake);

/* check if snake's direction is right */
bool isDirRight(SNAKE* snake);

/* check if snake's direction is up or down */
bool isDirUpOrDown(SNAKE* snake);

/* check if snake's direction is left or right */
bool isDirLeftOrRight(SNAKE* snake);

/* change snake's direction to up */
void changeDirUp(SNAKE* snake);

/* change snake's direction to down */
void changeDirDown(SNAKE* snake);

/* change snake's direction to left */
void changeDirLeft(SNAKE* snake);

/* change snake's direction to right */
void changeDirRight(SNAKE* snake);

/* update the snake head and body */
void moveSnake(SNAKE *snake);

/* update the snake body based on its head */
void updateBody(SNAKE *snake);

/* update position of snake's head */
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

