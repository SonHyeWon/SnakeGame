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
	SNAKE	snake = { {{0, 4}, {0, 5}}, down, 2, 0 };
	FRUIT	fruit;
	SCREEN screen;
	int	i;
	char	inputValue = '\0', score[32];
	bool	quit = false, checkInput = false;

	createScreen(&screen);
	createFruit(screen, &fruit);

	cursor(0);							/* hide the cursor back */
	srand(time(NULL));					/* initialize random generator */

	do {
		writesat(0, 0, 15, "   ____          __      ");
		writesat(0, 1, 15, "  / __/__  ___ _/ /_____ ");
		writesat(0, 2, 7, " _\\ \\/ _ \\/ _ `/  '_/ -_)");
		writesat(0, 3, 8, "/___/_//_/\\_,_/_/\\_\\\\__/ ");

		/* display score */
		writesat(30, 2, 15, "SCORE:");
		sprintf(score, "%d", snake.score);
		writesat(37, 2, 7, score);

		/* instructions */
		writesat(30, 3, 11, "WASD: Move  Q: Quit");

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

		/* update the head's coordinates */
		switch (snake.dir) {
		case up: snake.body[0].y--; break;
		case down: snake.body[0].y++; break;
			/* x always a multiple of 2, since it was inited at 0 */
		case left: snake.body[0].x -= 2; break;
		case right: snake.body[0].x += 2; break;
		}

		/* wrap the snake at screen boundaries */
		if (snake.body[0].y < 4)      snake.body[0].y = screen.height - 2;
		if (snake.body[0].y > screen.height - 1) snake.body[0].y = 4;
		if (snake.body[0].x < 0)      snake.body[0].x = screen.width - 2;
		if (snake.body[0].x > screen.width - 1) snake.body[0].x = 0;

		/* snake eats fruits? */
		if (snake.body[0].x == fruit.pos.x && snake.body[0].y == fruit.pos.y) {
			snake.length++;		/* it grows */
			snake.score++;		/* and update the score */
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
