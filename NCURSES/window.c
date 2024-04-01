#include <ncurses.h>

int main(void)
{
	int height, width, start_y, start_x;
	WINDOW* my_win;

	initscr();

	height = 10;
	width = 20;
	start_y = start_x = 10;

	my_win = newwin(height, width, start_y, start_x);
	refresh();

	//box(my_win, ACS_VLINE , ACS_HLINE);
	box(my_win,0,0);
	mvwprintw(my_win,1,1, "this is my box");
	
	//wborder(my_win, '|', '|', '-', '-', '+', '+', '+', '+');
	//wprintw(my_win, "this is my box");
	wrefresh(my_win);

	box(my_win, ' ', ' ');
	wrefresh(my_win);
	
	getch();
	endwin();

	return 0;
}
