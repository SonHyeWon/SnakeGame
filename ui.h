#pragma once

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

/* display a string at position (x,y) using color c */
void writesat(int x, int y, int c, const char * s);

/* clear one line from 'clearpointCell' by 'length'*/
void clearLine(CELL clearPointCell, int length);

/* clear the game space */
void clearGameScreen(SCREEN screen);
