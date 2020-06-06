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
	SCREEN  screen;
	int	score = 0;
	char	inputValue = '\0';
	bool	quit = false, checkInput = false;

	/* initiate strunctures */
	createScreen(&screen);
	createFruit(screen, &fruit);
	createSnake(screen, &snake);

	cursor(0);							/* hide the cursor back */
	srand(time(NULL));					/* initialize random generator */

	drawUI(screen);

	do {
		/* draw score next to score zone */
		drawScore(score);

		/* check and receive keyboard input */
		checkInput = isKeyInput(&inputValue);
		if (checkInput)
		{
			switch (inputValue)
			{
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

		/* move snake's head and body */
		moveSnake(&snake);

		/* wrap the snake at screen boundaries */
		if(quit == false) 
		{
			quit = isCollideBoundary(snake.body[0], &screen);
		}

		/* snake collides with itself? */
		if (quit == false)
		{
			quit = isCollideBody(&snake);
		}

		/* snake eats fruits? */
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
