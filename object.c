#include <stdio.h>
#include <windows.h>
#include "object.h"
#include "ui.h"

void gotoxy(int x, int y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x, y};
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
	writecat(x+w, y, c, '+');
	for (i = 1; i < w; i++)
		writecat(x+i, y, c, '-');	
}

void frame(int x, int y, int w, int h, int c) {
	int i;
	writecat(x    , y    , c, '+');
	writecat(x+w-1, y    , c, '+');	
	writecat(x    , y+h-1, c, '+');	
	writecat(x+w-1, y+h-1, c, '+');	
	for (i = 1; i < w-1; i++) {
		writecat(x+i, y, c, '-');
		writecat(x+i, y+h-1, c, '-');
	}
	for (i = 1; i < h-1; i++) {
		writecat(x  , y+i, c, '|');
		writecat(x+w-1, y+i, c, '|');
	}
}

void box(int x, int y, int w, int h, int c) {
	int i, j;
	frame(x, y, w, h, c);
	for (i = 1; i < w-1; i++)
	for (j = 1; j < h-1; j++)
		writecat(x+i, y+j, c, ' ');
}

void dialog(int x, int y, int w, int h, int c, const char * title) {
	int tx = (w - strlen(title)) >> 1;
	box(x, y, w, h, c);
	if (strlen(title))
		writesat(x+tx, y, c, title);
}

