#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRY 200

// 이름, 전화번호, 메모를 한번에 관리할 구조체 TelBook 정의
struct TelBook {
	char name[30];
	char phone[20];
	char memo[40];
};
// 전화번호부 메뉴 선택칸에 사용할 문자열 배열 설정
char *choices[] = {
		"Search",
		"Add",
		"Delete",
		"List",
		"Exit"
};

// 검색, 추가, 삭제, 리스트 출력 함수 선언
void search_tel(const char *filename, char *contents);
void add_tel(const char *filename, struct TelBook *book);
void delete_tel(const char *filename,  const char *contents);
void print_list(const char *filename );
int compare(const void *a, const void *b);

// choice의 문자 별 사이즈 설정,  메뉴판을 띄우는 함수 설정
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main()
{	
	WINDOW *menu_win;	// 메뉴판 윈도우 정의
	int highlight = 1;	// 변수 설정
	int choice = 0;
	int c;
	
	initscr();		// 스크린을 시작하기 위해 초기 설정
	clear();		
	noecho();	
	cbreak();
	start_color();					// 색을 입히기 위해 start_color
	init_pair(1, COLOR_GREEN, COLOR_BLACK);		// pair을 정의해 초록글자와 빨간글자를 사용할 수 있게 정의
	init_pair(2, COLOR_RED, COLOR_BLACK);
	int Mx, My;
	getmaxyx(stdscr, My, Mx);

	menu_win = newwin(9, Mx-5, 6, 0);		// 메뉴판의 크기 설정
	keypad(menu_win, TRUE);				// keypad를 통해 입력받는 설정
	printw("TelBook Program of ncurses.\n");		// 전화번호부의 각 요소별 사용 방법 
	printw("1. search : input (contents) \n");
	printw("2. add : input (name) (phone) (memo)\n");
	printw("3. delete : input (contents) \n");
	printw("4. list : sort data and print \n");
	refresh();					
	print_menu(menu_win, highlight);		// 다음으로 print_menu를 시행
	while(1)
	{
		c = wgetch(menu_win);			// 메뉴판을 방향키로 아래위로 움직이며 현재 선택할 위치에 highlight를 설정
		switch(c)
		{
			case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else
					++highlight;
				break;
			case 10 :
				choice = highlight;
				break;
			default :			// 만약 키보드 up down키가 아니면 아스키코드값과 누른 문자 보임
				mvprintw(15, 0, "Character pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)		// 선택되었다면 반복을 끝내고 작업을 들어감                   
                        break;  		
	}
	mvprintw(16, 0, "You chose choice %d with choice string %s\n", choice, choices[choice-1]);
	clrtoeol();
	refresh();		// 메뉴에서 선택된 요소를 시행한다.	
	
	if ( choice == 1){				// 1번 choice이면 search 실행
                char contents[10];
                move(17,0);
                attron(COLOR_PAIR(1) | A_BOLD);		// COLOR 및 BOLD로 시각화
                printw("Which string? :");	
                attroff(COLOR_PAIR(1));
                getstr(contents);			// getstr로 string을 입력받음
                mvprintw(17, 20, "%s", contents);	// 입력 받은 뒤 입력한 글자 화면에 보이도록 설정
                attroff(A_BOLD);
                search_tel("data.txt", contents);	// search 함수 실행
        }
	else if ( choice == 2 ){			// 2번 choice이면 add 실행
		// book 동적 할당
		struct TelBook *book = malloc(sizeof(struct TelBook));		
		char ch;
		
		attron(COLOR_PAIR(1) | A_BOLD);
		mvprintw(17, 0, "Enter names, phone, memo in order");
		attroff(COLOR_PAIR(1) | A_BOLD);

		// 전화번호부에 추가할 내용을 입력받은 뒤 확인할 수 있도록 출력 후 refresh까지 시행
		mvprintw(18,0,"name: "); getstr(book->name); mvprintw(18, 10,"%s", book->name); refresh();
		mvprintw(19,0,"phone :"); getstr(book->phone); mvprintw(19, 10,"%s", book->phone); refresh();
		mvprintw(20,0,"memo : "); getstr(book->memo); mvprintw(20, 10, "%s", book->memo); refresh();
		
		// 추가할 것인지 확인
		mvprintw(21, 0, "%s %s %s\n", book->name, book->phone, book->memo);
		refresh();
		attron(COLOR_PAIR(1) | A_BOLD);		// color 및 bold 설정
		mvprintw(22, 0, "add? [Y/N]: ");	
		refresh();
		attroff(COLOR_PAIR(1));
		ch = getchar();				// data에 추가를 할 것인지 말 것인지 정함
		mvprintw(22, 13, "%c", ch);
		attroff(A_BOLD);
		
		attron(COLOR_PAIR(2) | A_BOLD);
		if(ch == 'Y' || ch == 'y'){			// Y 및 Y 입력시 add_tel시행하고, 다른 key 입력시 fail.
			mvprintw(23,0,"Add Succeed.\n");
			add_tel("data.txt", book);
		}
		else
			mvprintw(23,0,"Add failed.\n");
		attroff(COLOR_PAIR(2) | A_BOLD);
	}
	else if ( choice == 3 ){		// 3번 choice이면 delete 시행
		char contents[10];		
		attron(COLOR_PAIR(1) | A_BOLD);		// color 및 bold 설정
		mvprintw(17,0, "Which string ?:");	
		attroff(COLOR_PAIR(1));			
		getstr(contents);			
		mvprintw(17,20, "%s", contents);	// 삭제하고자 하는 문자열 입력받은 뒤 출력
		attroff(A_BOLD);
		delete_tel("data.txt",contents  );	// delete 시행
	}
	else if ( choice == 4 ){		// 4번 choice이면 sort and list 출력
		print_list("data.txt");		// print_list 시행
	}

	mvprintw(My-1, 0, "Press any Key for Exit screen");	// 아무 키나 입력시 나가진다는 사실 보임
	getch();		// 전화번호부를 통한 작업 내용을 보이고 아무 키나 입력시 screen을 종료한다.
	endwin();
	return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;
	int Mx, My;
	x = 2;		// box안 print할 위치를 변수로 선언
	y = 2;
	box(menu_win, 0, 0);	//menu_win box 생성
	mvwprintw(menu_win,0,1,"Select One");
	for(i=0 ; i < n_choices; ++i)
	{
		if(highlight == i+1)		// highlight가 choice 메뉴 번호에 맞으면 
		{
			wattron(menu_win, A_REVERSE);			// 반전시킴
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else				// 다른 메뉴들은 반전되지 않음
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);	// menu_win을 볼수 있게 설정
}
// 찾기 함수. filename과 찾을 요소를 입력받음
void search_tel(const char *filename,  char *contents)
{
	// fopen을 통해 data.txt를 불러온다. read모드
        FILE *file = fopen(filename, "r");
        int i = 0;	
	// 없는 파일이면 찾기 x
        if ( file == NULL ){
                mvprintw(18,0,"You can't open file.\n");
             	return ;
        }
	
	// TelBook과 파일을 한줄씩 읽어올 line배열 선언
	struct TelBook book;
        char line[MAX_ENTRY];
	// 한 줄씩 읽어와서 name, phone, memo를 구분자로 나누어서 받아온다.
        while (fgets(line, sizeof(line), file)) {
                strcpy(book.name, strtok(line, ":"));
                strcpy(book.phone , strtok(NULL, ":"));
        	strcpy(book.memo, strtok(NULL,":"));	
		
		// name, phone, memo중에서 찾는 요소를 포함하고 있는 부분이 있다면 화면에 출력한다.
                if (strstr(book.name, contents) != NULL || strstr(book.phone, contents) != NULL || strstr(book.memo, contents) != NULL) {
		// 읽어온 라인 순서대로 1, 2, 3순서로 받기 위해 i변수 선언
                mvprintw(i+18,0,"%d %s %s %s", i+1, book.name, book.phone, book.memo);		
		i++;
                }
        }
	// file 닫기
        fclose(file);
        
	// 찾은 라인이 있다면 추가로 match found 출력 , Color 및 Bold 설정으로 시각화
	attron(COLOR_PAIR(2) | A_BOLD);	
	if( i > 0)
                mvprintw(i+18,0,"match found.\n");
        else
                mvprintw(i+18,0,"no match found.\n");
	attroff(COLOR_PAIR(2) | A_BOLD);
}
// 전화번호부에 목록을 추가하는 함수, filename과 TelBook을 받는다.
void add_tel(const char *filename, struct TelBook *book)
{
        FILE *file = fopen(filename, "a");
        if (file == NULL) {
                mvprintw(18, 0,"You can't open file.\n");
                return ;
        }
	// add함수를 실행하기 전 에 argv를 활용하여 미리 구조체를 선언해두었다. file에 추가로 쓰기 위해 fprintf함수를 사용.
        fprintf(file, "%s:%s:%s\n", book->name, book->phone, book->memo);

        fclose(file);
}
// 전화번호부에서 목록을 제거하는 함수, filename과 제거할 요소를 포함하고있는 부분을 입력받음
void delete_tel(const char *filename, const char *contents) {
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
                mvprintw(18, 0,"You can't open file.\n");
                return ;
        }
	// line배열으로 한 줄씩 입력받는다.
	// d[]배열을 사용하여 삭제할 line이 txt원본의 몇 번째 줄에 있는지 기록한다.
        char line[MAX_ENTRY];
        int i= 0,j = 0;
	int *d = NULL;
	// 삭제할 줄을 제거하고 처음부터 입력하기 위해 data를 순서대로 book에 저장한다.
	struct TelBook book[MAX_ENTRY];
        while(fgets(line, sizeof(line), file)){
                strcpy(book[i].name, strtok(line, ":"));
                strcpy(book[i].phone , strtok(NULL, ":"));
                strcpy(book[i].memo , strtok(NULL, ":"));
		
		// search와 마찬가지로 찾는다. 3번째 줄에서 처음 삭제 대상 요소가 발견된다면 d[0] = 3이 된다.
                if(strstr(book[i].name, contents) != NULL || strstr(book[i].phone, contents) != NULL || strstr(book[i].memo, contents) != NULL){
	                mvprintw(j+18,0,"%d %s %s %s\n", j + 1, book[i].name, book[i].phone, book[i].memo);
			d = realloc(d, (j + 1) * sizeof(int));
			d[j] = i;
			j++;
		}
		i++;
        }
 	// 다시 줄만큼 출력하기 위해 num변수 저장
	int num = i;
	
	fclose(file);

	// 파일을 닫은 뒤 w쓰기모드로 다시 연다.
	file = fopen(filename, "w");
	
	int k;

	// Color 및 Bold 설정 후 번호를 입력받아 찾은 라인 중 몇 번째 라인을 지울 것인지 선택
	attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(j+18,0,"which one? : ");
	attroff(COLOR_PAIR(1));
        scanw("%d", &k);
	mvprintw(j+18, 13, "%d", k);
	attroff(A_BOLD);
	
	// remove 상태에 대해 Color 및 Bold 설정. file을 w모드로 열었으니 다시 순서대로 입력하는 과정 포함.
	attron(COLOR_PAIR(2) | A_BOLD);
	if ( k <= 0 || k > j ){
		mvprintw(j+19,0, "No range. can't remove.\n");
		for( i=0; i<num; i++ )
                        fprintf(file, "%s:%s:%s", book[i].name, book[i].phone, book[i].memo);
	}
	else {
	// d[k-1]으로 삭제 대상 줄이 원 본의 몇 번째 줄인지 알 수 있다. 그 줄을 제외하고 다시 입력.
		mvprintw(j+19,0,"removed.\n");
        	for( i=0; i<num; i++ ){
			if( i == d[k-1])
				continue;
			else
				fprintf(file, "%s:%s:%s", book[i].name, book[i].phone, book[i].memo);
		}
	}
	attroff(COLOR_PAIR(2)|A_BOLD);
	free(d);
        fclose(file);
}
// qsort를 사용하기 위해 compare함수 제작. name을 기준으로 비교한다.
int compare(const void *a, const void *b) {
    const struct TelBook *A = (const struct TelBook *)a;
    const struct TelBook *B = (const struct TelBook *)b;
    return strcmp(A->name, B->name);
}
// 정렬된 list를 출력하는 함수. filename을 인수로 받음
void print_list(const char *filename) {
        FILE *file = fopen(filename, "r");
        if ( file == NULL ) {
                mvprintw(18,0,"You can't open file.\n");
                return ;
        }
	// delete와 마찬가지로 book을 선언하여 line별로 저장한다.
        int i = 0;
        char line[MAX_ENTRY];
	struct TelBook book[MAX_ENTRY];
        while (fgets(line, sizeof(line), file)) {
                strcpy(book[i].name,strtok(line,":"));
                strcpy(book[i].phone,strtok(NULL,":"));
                strcpy(book[i].memo,strtok(NULL,":"));
                i++;
        }
	// 입력된 만큼 출력하기 위해 num에 저장
	int num = i;
	// qsort를 사용하여 name별로 정렬한다.
	qsort(book , i, sizeof(struct TelBook), compare);
        
	// 출력
	attron(COLOR_PAIR(1) | A_BOLD);
	mvprintw(18, 0, "Sorted List on TelBook");
	attroff(COLOR_PAIR(1) | A_BOLD);
        for (i = 0; i < num; i++) {
        mvprintw(i+19,0,"%d %s %s %s\n", i + 1, book[i].name, book[i].phone, book[i].memo);
        }

    fclose(file);
}
