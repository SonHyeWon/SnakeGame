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

int getmaxcolor() {
	return 16;
}

void clrscr()
{
	system("cls");
}

void writesat(int x, int y, int c, const char * s) {
	gotoxy(x, y);
	textcolor(c);
	puts(s);
}