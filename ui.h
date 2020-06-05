#pragma once

#define SCORE_COLOR 15

typedef struct cell
{
    int x, y;
} CELL;

typedef struct screenInfo
{
	CELL startPoint;
	CELL endPoint;
	int width;
	int height;
}SCREEN;

/* hide/show cursor */
void cursor(int visible);

/* change text/background color */
void textcolor(int x);

/* returns the console screen width in columns */
int getWidth();

/* returns the console screen width in rows */
int getHeight();

/* saves related values in structure screen */
void createScreen(SCREEN* screen);

/* returns the total number of color supported */
int getMaxColorValue();

/* clear one line from 'clearpointCell' by 'length'*/
void clearLine(CELL clearPointCell, int length);

/* clear the game space */
void clearGameScreen(SCREEN screen);

/* display current score */
void drawScore(int score);

/* draw title, score zone, instructions */
void drawUI(SCREEN screen);
