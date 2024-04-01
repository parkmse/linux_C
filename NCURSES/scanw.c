#include <ncurses.h>
#include <string.h> 

int main(void)
{
	char mesg[]="Enter a string: ";
	char str[80];
	int row,col;
	
	initscr();
	getmaxyx(stdscr,row,col);
	mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
	
	getstr(str); // getstring
	mvprintw(LINES - 2, 0, "You Entered: %s", str); // print str
	refresh();
	getch();
	endwin();
	
	return 0;
}

