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

bool rightMax(int a, int b)
{
	return (a <= b);
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
	else if (rightMax(screen->endPoint.y - 1, snakePos.y))
	{
		return true;
	}
	else if (rightMax(snakePos.x, screen->startPoint.x))
	{
		return true;
	}
	else if (rightMax(screen->endPoint.x - 3, snakePos.x))
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

void isCollideFruit(SNAKE* snake, FRUIT* fruit, SCREEN screen, int* score)
{
	if (isSamePosition(&snake->body[0], &fruit->pos))
	{
		snake->length++;
		(*score)++;
		createFruit(screen, fruit);
	}
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

bool isDirUp(SNAKE* snake)
{
	if (snake->dir == up)
	{
		return true;
	}
	return false;
}

bool isDirDown(SNAKE* snake)
{
	if (snake->dir == down)
	{
		return true;
	}
	return false;
}

bool isDirLeft(SNAKE* snake)
{
	if (snake->dir == left)
	{
		return true;
	}
	return false;
}

bool isDirRight(SNAKE* snake)
{
	if (snake->dir == right)
	{
		return true;
	}
	return false;
}

bool isDirUpOrDown(SNAKE* snake)
{
	return (isDirUp(snake) || isDirDown(snake));
}

bool isDirLeftOrRight(SNAKE* snake)
{
	return (isDirLeft(snake) || isDirRight(snake));
}

void changeDirUp(SNAKE* snake)
{
	if (!isDirUpOrDown(snake))
	{
		snake->dir = up;
	}
}

void changeDirDown(SNAKE* snake)
{
	if (!isDirUpOrDown(snake))
	{
		snake->dir = down;
	}
}

void changeDirLeft(SNAKE* snake)
{
	if (!isDirLeftOrRight(snake))
	{
		snake->dir = left;
	}
}

void changeDirRight(SNAKE* snake)
{
	if (!isDirLeftOrRight(snake))
	{
		snake->dir = right;
	}
}

void moveSnake(SNAKE *snake)
{
	updateBody(snake);
	updateHead(snake);
}

void updateBody(SNAKE *snake)
{
	int i;
	for (i = snake->length - 1; i > 0; i--) {
		snake->body[i] = snake->body[i - 1];
	}
}

void updateHead(SNAKE* snake)
{
	switch (snake->dir)
	{
	case up:
		snake->body[0].y--;
		break;
	case down:
		snake->body[0].y++;
		break;
	case left:
		snake->body[0].x -= 2;
		break;
	case right:
		snake->body[0].x += 2;
		break;
	}
}

bool isEven(int number)
{
	if (number % 2 == 0)
	{
		return true;
	}

	return false;
}

void createFruit(SCREEN screen, FRUIT* fruit)
{
	CELL strP = { screen.startPoint.x + 2, screen.startPoint.y + 1 };
	CELL endP = { screen.endPoint.x - 2, screen.endPoint.y - 1 };
	int maxColorValue;
	int tmpX; //for fruit->x

	tmpX = rand() % (endP.x - strP.x);

	if (!isEven(tmpX))
	{
		tmpX -= 1;
	}

	fruit->pos.x = strP.x + tmpX;
	fruit->pos.y = strP.y + rand() % (endP.y - strP.y);

	maxColorValue = getMaxColorValue();
	fruit->color = 1 + (rand() % (maxColorValue - 1));
}

void createSnake(SCREEN screen, SNAKE* snake)
{
	int centerX = ((screen.endPoint.x + screen.startPoint.x) / 2);
	int centerY = ((screen.endPoint.y + screen.startPoint.y) / 2);
	CELL center = { centerX, centerY };

	snake->body[0] = center;
	center.x -= 2;
	snake->body[1] = center;

	snake->dir = right;
	snake->length = 2;
}

void drawChar(CELL pos, int color, const char character) 
{
	gotoxy(pos.x, pos.y);
	textcolor(color);
	putchar(character);
}

void drawObjects(SNAKE snake, FRUIT fruit, bool quit)
{
	int i;
	if (quit == true) 
	{
		drawChar(snake.body[1], QUIT_COLOR, HEAD_SHAPE);	/* dead snake's head */
		textcolor(TEXT_COLOR);					/* back to normal color */
		return;
	}

	for (i = 1; i < snake.length; i++) {
		drawChar(snake.body[i], BODY_COLOR, BODY_SHAPE);	/* snake's body */
	}
	drawChar(snake.body[0], HEAD_COLOR, HEAD_SHAPE);		/* snake's head */
	drawChar(fruit.pos, fruit.color, FRUIT_SHAPE);			/* fruit */
}

