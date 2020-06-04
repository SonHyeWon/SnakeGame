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

		/* wrap the snake at screen boundaries */
		if (snake.body[0].y < 4)      snake.body[0].y = screen.height - 2;
		if (snake.body[0].y > screen.height - 1) snake.body[0].y = 4;
		if (snake.body[0].x < 0)      snake.body[0].x = screen.width - 2;
		if (snake.body[0].x > screen.width - 1) snake.body[0].x = 0;

		/* snake eats fruits? */
		if (snake.body[0].x == fruit.pos.x && snake.body[0].y == fruit.pos.y) {
			snake.length++;		/* it grows */
			score++;		/* and update the score */
			/* regenerate a new fruit */
			createFruit(screen, &fruit);
		}

		clearGameScreen(screen);

		/* screen painting occurred here */
		writecat(fruit.pos.x, fruit.pos.y, fruit.color, FRUIT_SHAPE);			/* fruit */
		writecat(snake.body[0].x, snake.body[0].y, 15, HEAD_SHAPE);	/* snake's head */
		/* snake's body */
		for (i = 1; i < snake.length; i++) {
			writecat(snake.body[i].x, snake.body[i].y, 8, BODY_SHAPE);
		}

		Sleep(50);				/* slow down a bit */
	} while (!quit);

	cursor(1);					/* turn the cursor back on */

	return 0;
}
