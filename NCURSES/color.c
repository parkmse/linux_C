#include <ncurses.h>
int main(void)
{
	initscr();
	if (!has_colors()) {
		printw("Terminal dose not support color.");
		getch();
		return -1;
	}
	printw("Normal Text.");

	start_color();
	init_color(COLOR_RED, 1000, 0, 0);
	init_pair(1, COLOR_RED, COLOR_WHITE);

	move(2, 10);
	attron(COLOR_PAIR(1));
	printw("Colred Text.");
	attroff(COLOR_PAIR(1));

	refresh();
	getch();

	endwin();

	return 0;
}

