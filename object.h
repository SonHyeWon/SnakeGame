#pragma once
#include <stdbool.h>
#include "ui.h"
#define	MAX_LENGTH	1000	/* maximum snake length */
#define	HEAD_SHAPE	'o'
#define	BODY_SHAPE	'o'
#define	FRUIT_SHAPE	'#'
#define	HEAD_COLOR	15
#define	BODY_COLOR	8
#define QUIT_COLOR	12

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

bool isCollideBoundary(CELL snakePos, SCREEN* screen);

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

bool isEven(int number);

void createFruit(SCREEN screen, FRUIT* fruit);

void createSnake(SCREEN screen, SNAKE* snake);

/* draw one single 'character' at desired position 'pos' using 'color'*/
void drawChar(CELL pos, int color, const char ch);

/* draw snake and fruit into screen. need to check whether the game ends */
void drawObjects(SNAKE snake, FRUIT fruit, int quit);

