#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

struct SomeStuff {
  int max_y;
  int max_x;
  int ch;
};

void game(char character[1]) {

        struct SomeStuff cordinates;
	// Starting NCURSES.
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	refresh();

	// Calculating X and Y Cordinates.
//	int max_y, max_x;
	getmaxyx(stdscr, cordinates.max_y, cordinates.max_x);

	int y = 5;
	int x = (cordinates.max_x - strlen(character)) / 2;

//	int ch;
	while (1) {
		clear();
		mvprintw(0, 0, "Cordinates:\nX = %d\nY = %d", x, y);
		mvprintw(y, x, "%s", character);	

		cordinates.ch = getch();

		// Controls.
		switch (cordinates.ch) {
			case KEY_UP: y--; break;
			case KEY_DOWN: y++; break;
			case KEY_LEFT: x--; break;
			case KEY_RIGHT: x++; break;
		}

		// Wrap-Around Movements with no fancy maths.
		if (y < 0) y = cordinates.max_y - 1;
		if (y >= cordinates.max_y) y = 0;

		int max_pos_x = cordinates.max_x - strlen(character);

		if (max_pos_x < 0) max_pos_x = 0;

		if (x < 0)
			x = max_pos_x;
		else if (x > max_pos_x)
			x = 0;

		// When user type 'q' it's breaking and stop the program.
		if (cordinates.ch == 'q') {
			curs_set(1);
			endwin();
			exit(0);
		}
	}
}

int main() {
  game("H");
  return 0;
}
