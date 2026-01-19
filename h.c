#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void movements() {
	// Starting NCURSES.
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	refresh();

	// Calculating X and Y Cordinates.
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);;
	char character[] = "H";

	int y = 5;
	int x = (max_x - strlen(character)) / 2;

	int ch;
	while (1) {
		clear();
		mvprintw(0, 0, "Cordinates:\nX = %d\nY = %d", x, y);
		mvprintw(y, x, "%s", character);	

		ch = getch();

		// Controls.
		switch (ch) {
			case KEY_UP: y--; break;
			case KEY_DOWN: y++; break;
			case KEY_LEFT: x--; break;
			case KEY_RIGHT: x++; break;
		}

		// Wrap-Around Movements with no fancy maths.
		if (y < 0) y = max_y - 1;
		if (y >= max_y) y = 0;

		int max_pos_x = max_x - strlen(character);

		if (max_pos_x < 0) max_pos_x = 0;

		if (x < 0)
			x = max_pos_x;
		else if (x > max_pos_x)
			x = 0;

		// When user type 'q' it's breaking and stop the program.
		if (ch == 'q') {
			curs_set(1);
			endwin();
			break;
		}
	}
}

int main() {
  movements();
	return 0;
}
