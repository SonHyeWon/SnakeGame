#include <stdio.h>
#include <windows.h>
#include "ui.h"
#pragma once

void cursor(int visible) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, visible };
	SetConsoleCursorInfo(handle, &cursor);
}

void textcolor(int x) {
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}

int getWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int getHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void createScreen(SCREEN* screen)
{
	screen->width = getWidth();
	screen->height = getHeight();

	screen->startPoint.x = 2;
	screen->startPoint.y = 5;

	screen->endPoint.x = screen->width - 2;
	screen->endPoint.y = screen->height - 1;
}

int getMaxColorValue() {
	return 16;
}

void clearLine(CELL clearPointCell, int length)
{
	COORD clearPoint = { clearPointCell.x, clearPointCell.y };
	unsigned long tmp;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), '\0', length, clearPoint, &tmp);
}

void clearGameScreen(SCREEN screen)
{
	int i;
	CELL gameStartPoint = { screen.startPoint.x + 2, screen.startPoint.y + 1 };
	CELL gameEndPoint = { screen.endPoint.x - 2, screen.endPoint.y - 1 };

	for (i = gameStartPoint.y; i < gameEndPoint.y; i++)
	{
		CELL clearPoint = { gameStartPoint.x, i };
		int eraseLength = gameEndPoint.x - gameStartPoint.x; 
		clearLine(clearPoint, eraseLength);
	}
}

void drawScore(int score) 
{
	gotoxy(37, 2);
	textcolor(SCORE_COLOR);
	printf("%d", score);
}

void drawUI(SCREEN screen)
{
	CELL strP = screen.startPoint;
	CELL endP = screen.endPoint;
	int i;
	char ui[4][52] =
	{
		"   ____          __      ",
		"  / __/__  ___ _/ /_____ ",
		" _\\ \\/ _ \\/ _ `/  '_/ -_)   SCORE: ",
		"/___/_//_/\\_,_/_/\\_\\\\__/    WASD: Move  Q: Quit"
	};

	for (i = 0; i < 4; i++)
	{
		printf("%s\n", ui + i);
	}

	textcolor(15);

	for (i = strP.x + 1; i < endP.x - 2; i++)
	{
		gotoxy(i, strP.y);
		printf("%c", '-');
		gotoxy(i, endP.y - 1);
		printf("%c", '-');
	}

	for (i = strP.y + 1; i < endP.y - 1; i++)
	{
		gotoxy(strP.x, i);
		printf("%c", '|');
		gotoxy(endP.x - 2, i);
		printf("%c", '|');
	}

	gotoxy(strP.x, strP.y);
	printf("%c", '+');
	gotoxy(strP.x, endP.y - 1);
	printf("%c", '+');
	gotoxy(endP.x - 2, strP.y);
	printf("%c", '+');
	gotoxy(endP.x - 2, endP.y - 1);
	printf("%c", '+');
}

