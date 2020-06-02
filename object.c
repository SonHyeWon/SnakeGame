#include <stdio.h>
#include <windows.h>
#include "object.h"
#include "ui.h"
#include <stdbool.h>

void gotoxy(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void writecat(int x, int y, int c, const char ch) {
	gotoxy(x, y);
	textcolor(c);
	putchar(ch);
}

void hline(int x, int y, int w, int c) {
	int i;
	writecat(x, y, c, '+');
	writecat(x + w, y, c, '+');
	for (i = 1; i < w; i++)
		writecat(x + i, y, c, '-');
}

void frame(int x, int y, int w, int h, int c) {
	int i;
	writecat(x, y, c, '+');
	writecat(x + w - 1, y, c, '+');
	writecat(x, y + h - 1, c, '+');
	writecat(x + w - 1, y + h - 1, c, '+');
	for (i = 1; i < w - 1; i++) {
		writecat(x + i, y, c, '-');
		writecat(x + i, y + h - 1, c, '-');
	}
	for (i = 1; i < h - 1; i++) {
		writecat(x, y + i, c, '|');
		writecat(x + w - 1, y + i, c, '|');
	}
}

void box(int x, int y, int w, int h, int c) {
	int i, j;
	frame(x, y, w, h, c);
	for (i = 1; i < w - 1; i++)
		for (j = 1; j < h - 1; j++)
			writecat(x + i, y + j, c, ' ');
}

void dialog(int x, int y, int w, int h, int c, const char * title) {
	int tx = (w - strlen(title)) >> 1;
	box(x, y, w, h, c);
	if (strlen(title))
		writesat(x + tx, y, c, title);
}

bool rightMax(int a, int b)
{
	return (a < b);
}
bool isSameValue(int leftValue, int rightValue)
{
	return (leftValue == rightValue);
}
bool isSamePosition(CELL* leftPos, CELL* rightPos)
{
	return (isSameValue(leftPos->x, rightPos->x) && isSameValue(leftPos->y, rightPos->y));
}
bool isCollideBoundary(CELL snakePos, SCREEN* screen)
{
	if (rightMax(snakePos.y, screen->startPoint.y))
	{
		return true;
	}
	else if (rightMax(screen->endPoint.y, snakePos.y))
	{
		return true;
	}
	else if (rightMax(snakePos.x, screen->startPoint.x))
	{
		return true;
	}
	else if (rightMax(screen->endPoint.x, snakePos.x))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isCollideBody(SNAKE* snake)
{
	int i = 0;
	for (i = 1; i < snake->length; i++)
	{
		if (isSamePosition(&snake->body[0], &snake->body[i]))
		{
			return true;
		}
	}
	return false;
}

bool isKeyInput(char* inputValue)
{
	if (_kbhit())
	{
		*inputValue = toupper(_getch());
		return true;
	}
	return false;
}

void changeDirUp(SNAKE* snake)
{
	if (snake->dir != down)
	{
		snake->dir = up;
	}
}

void changeDirDown(SNAKE* snake)
{
	if (snake->dir != up)
	{
		snake->dir = down;
	}
}

void changeDirLeft(SNAKE* snake)
{
	if (snake->dir != right)
	{
		snake->dir = left;
	}
}

void changeDirRight(SNAKE* snake)
{
	if (snake->dir != left)
	{
		snake->dir = right;
	}
}

void moveSnake(SNAKE *snake)
{
	UpdateBody(snake);
}

void UpdateBody(SNAKE *snake) 
{
	int i;
	for (i = snake->length - 1; i > 0; i--) {
		snake->body[i] = snake->body[i - 1];
	}
}
