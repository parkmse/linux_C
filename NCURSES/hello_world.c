#include <ncurses.h> //stdio쓰는 함수 없음
#include <unistd.h>

int main(void)
{
	initscr();
	printw("Hello NCURSES World !!!"); // printw -> ncurses함수
	refresh(); // 변화가 실제로 반영되려면 refresh 해야함.
	getch();
	endwin(); // memory free
	
	return 0;
}

