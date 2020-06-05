/* SIMPLE SNAKE GAME */
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>		/* for sprintf() */
#include <windows.h>		/* for Sleep() and other Windows stuffs */
#include "object.h"
#include "ui.h"
#include <stdbool.h>

int main()
{
	SNAKE	snake;
	FRUIT	fruit;
	SCREEN screen;
	int	i, score = 0;
	char	inputValue = '\0';
	bool	quit = false, checkInput = false;

	createScreen(&screen);
	createFruit(screen, &fruit);
	createSnake(screen, &snake);

	cursor(0);							/* hide the cursor back */
	srand(time(NULL));					/* initialize random generator */

	drawUI(screen);

	do {
		/* display score */
		drawScore(score);

		/* keyboard handling */
		checkInput = isKeyInput(&inputValue);
		if (checkInput)
		{
			switch (inputValue) {			/* and process it */
			/* ESC, Q: quit game */
			case 27:
			case 'Q':
				quit = true;
				break;
				/* W: Up, S: Down, A: Left, D: Right */
			case 'W':
				changeDirUp(&snake);
				break;
			case 'S':
				changeDirDown(&snake);
				break;
			case 'A':
				changeDirLeft(&snake);
				break;
			case 'D':
				changeDirRight(&snake);
				break;
			default:
				break;
			}
		}

		moveSnake(&snake);

		if(quit == false)
		{
			quit = isCollideBoundary(snake.body[0], &screen);
		}

		if (quit == false)
		{
			quit = isCollideBody(&snake);
		}

                isCollideFruit(&snake, &fruit, screen, &score);

		/* clear the game space */
		if (quit == false)
		{
			clearGameScreen(screen);
		}

		/* screen painting occurred here */
		drawObjects(snake, fruit, quit);

		Sleep(50);				/* slow down a bit */
	} while (!quit);

	cursor(1);					/* turn the cursor back on */
	gotoxy(0, screen.height-1);
	
	return 0;
}
