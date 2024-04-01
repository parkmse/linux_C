#include <ncurses.h>
#include <string.h> 

int main(void)
{

	char mesg[]="Just a string";
	int row,col;

	initscr();
	getmaxyx(stdscr,row,col); /* get the number of rows and columns */
	mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);

	/* print the message at the center of the screen */
	
	mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
	printw("Try resizing your window(if possible) and then run this program again");
	refresh();
	getch();
	endwin();
	
	return 0;
}

