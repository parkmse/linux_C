#include <ncurses.h>

int main(void)
{
	initscr();
	
	printw("A Big string which i didn't care to type fully ");
	mvchgat(0, 1, -1, A_BLINK, 1, NULL);
	
	refresh();
	getch();
	endwin();
	
	return 0;
}
