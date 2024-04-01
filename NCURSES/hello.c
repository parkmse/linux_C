#include <ncurses.h>

int main(void)
{
	initscr();
	mvprintw(10,0,"Hello NCURSES World !!!");
	refresh(); 
	getch();
	endwin(); 
	
	return 0;
}

