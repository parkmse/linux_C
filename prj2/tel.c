#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRY 200

// 이름, 전화번호, 메모를 관리할 구조체 정의
struct TelBook {
    char name[30];
    char phone[20];
    char memo[40];
};

//serch, add, delete, print 출력 함수 선언
void search_tel(const char *filename, char *contents);
void add_tel(const char *filename, struct TelBook *book);
void delete_tel(const char *filename, const char *contents);
void print_list(const char *filename);
int compare(const void*a, const void *b);

// 사용자가 선택할 수 있는 메뉴 옵션들을 문자열 배열로 선언
char *choices[] = { 
			"Search",
			"Add",
			"Delete",
			"List",
			"Exit",
		  };

int n_choices = sizeof(choices) / sizeof(char *); // 메뉴에 있는 선택지의 갯수 계산

void print_menu(WINDOW *menu_win, int highlight); // 메뉴 출력 함수 미리 선언

int main()
{
    WINDOW *menu_win; // 메뉴를 출력할 윈도우 객체
    int highlight = 1; // 현재 하이라이트된 메뉴 항목을 추적
    int choice = 0; // 사용자가 선택한 메뉴 항목 번호
    int c; // 사용자의 키보드 입력을 임시 저장하는 변수

    initscr(); // ncurses모드 시작
    clear();
    noecho(); // 사용자 입력 키 화면 표시 x
    cbreak(); // 입력 버퍼 무시, 사용자 입력을 즉시 프로그램에 전달

    // 색상 초기화
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // 쌍1: 초록색
    init_pair(2, COLOR_BLUE, COLOR_BLACK);  // 쌍2: 파란색

    int Mx, My;
    getmaxyx(stdscr, My, Mx); // 현재 화면의 크기를 가져옴

    //새 윈도우를 만들고 이를 menu_win에 할당
    menu_win = newwin(9, Mx - 5, 6, 0);

    //menu_win에서 키보드 입력을 가져올 수 있게 설정
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Welcome to the TelBook Program with ncurses.\n");
    mvprintw(1, 0, "Please, select an operation from the menu:\n");
    mvprintw(2, 0, "1. Search - Find entries by a content.\n");
    mvprintw(3, 0, "2. Add - Create a new entry with name, phone number, and memo.\n");
    mvprintw(4, 0, "3. Delete - Remove an entry by content.\n");
    mvprintw(5, 0, "4. List - Sort and display all entries.\n");
    refresh();

    print_menu(menu_win, highlight); // 초기 메뉴 화면

    while (1) {
        c = wgetch(menu_win); // 키보드 입력을 가져옴
        switch (c) {
        case KEY_UP: // 사용자가 위쪽 화살표를 눌렀을때
            if (highlight == 1) // 첫 옵션이 하이라이트 되어있으면 
                highlight = n_choices; // 마지막 옵션을 하이라이트
            else
                --highlight; // 그렇지 않다면 하이라이트를 위로 옮김
            break;
        case KEY_DOWN:
            if (highlight == n_choices)
                highlight = 1; // 마지막 옵션이 하이라이트 되어있으면 첫번째 옵션을 하이라이트
            else
                ++highlight; // 그렇지 않으면 하이라이트를 아래로
            break;
        case 10:
            choice = highlight; // 사용자가 enter 키를 눌렀을때
            break;
        default:
            mvprintw(15, 0, "The pressed key is: '%c'", c);
            refresh();
            break;
        }
	// 하이라이트 위치가 바꼈을 수도 있으므로 메뉴 다시 출력
        print_menu(menu_win, highlight); 
        if (choice != 0) // 선택 완료시 루프 종료
            break;
    }
 // 사용자가 선택한 메뉴 항목을 화면에 출력
    mvprintw(16, 0, "You chose choice %d with choice string %s\n", choice, choices[choice-1]);
    clrtoeol();
    refresh();
    
    //선택된 메뉴 항목에 따라 각각 다른 작업을 수행
    if (choice == 1){
        char searchT[10]; // search 메뉴 선택시
	move(17,0);
        attron(COLOR_PAIR(1) | A_BOLD);
        printw("Enter the string you want to search: ");
        attroff(COLOR_PAIR(1));
	getstr(searchT);
	mvprintw(18,20, "Searching for entries with '%s'", searchT);
        attroff(A_BOLD);
       	search_tel("data.txt", searchT);
    } 
    else if (choice == 2) { // add 메뉴 선택시
        struct TelBook book;
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(17, 0, "Enter name: ");
        getstr(book.name);
        mvprintw(18, 0, "Enter phone: ");
        getstr(book.phone);
        mvprintw(19, 0, "Enter memo: ");
        getstr(book.memo);
        mvprintw(21, 0, "Name: %s", book.name);
        mvprintw(22, 0, "Phone: %s", book.phone);
        mvprintw(23, 0, "Memo: %s", book.memo);

        mvprintw(25, 0, "Are you sure you want to add this entry? (y/n): ");
        char answer[3];
        getstr(answer);
        attroff(A_BOLD);

        if (answer[0] == 'y' || answer[0] == 'Y') {
            add_tel("data.txt", &book);
            mvprintw(26, 0, "Added success");
        }
        else {
            mvprintw(26, 0, "canceled");
        }
        attroff(A_BOLD);
    }
    else if (choice == 3) { // delete 메뉴 선택시
        char name[10];
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(17, 0, "Enter name to delete: ");
        attroff(COLOR_PAIR(1));
	getstr(name);
	mvprintw(17,20, "%s", name);
	attroff(A_BOLD);
        delete_tel("data.txt", name);
    }
    else if (choice == 4) { // list 메뉴 선택시
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(17, 0, "List of TelBook entries:\n");
        attroff(A_BOLD);
        print_list("data.txt");
        mvprintw(27, 0, "List operation completed.");
    }

    mvprintw(My-1, 0, "Press any Key for Exit screen");
    getch();
    endwin();
    return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;
    int Mx, My;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    mvwprintw(menu_win,0,1,"Select One");
    for(i=0 ; i < n_choices; ++i) {
        if(highlight == i+1) { // 현재 하이라이트 된 옵션인 경우
            wattron(menu_win, A_REVERSE); // 해당 메뉴의 반전된 색상을 적용하여 강조
            mvwprintw(menu_win, y, x, "%s", choices[i]); // 메뉴 옵션 문자열 출력
            wattroff(menu_win, A_REVERSE); //색상 반전 off
        } else // 하이라이트 되지 않은 옵션은 일반 색으로 출력
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y; //다음줄로 이동
    }
    wrefresh(menu_win); // 메뉴 윈도우를 화면에 출력
}
// search 함수이고 filename과 찾을 요소 입력받음
void search_tel(const char *filename, char *contents)
{
    FILE *file = fopen(filename, "r"); // fopen함수로 텍스트 불러오고 read 모드 실행

    if ( file == NULL ){
        printw("You can't open file.\n"); // file이 없으면 출력
        return ;
    }

    struct TelBook book;
    char line[MAX_ENTRY];
    int i = 0;

    // fgets 함수를 사용하여 파일에서 한 줄을 읽음.
    // 각 줄은 :으로 구분
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ":"); 
        if (token == NULL) break; // 읽어들일 내용 없으면 루프 종료
        strcpy(book.name, token); // 첫번째 토큰(이름)을 book.name에 복사

        token = strtok(NULL, ":");
        if (token == NULL) break;
        strcpy(book.phone, token);

        token = strtok(NULL, ":");
        if (token == NULL) break;
        strcpy(book.memo, token);
	
	// name, phone, memo 중 찾는 요소가 data.txt에 있으면 화면에 출력
        if (strstr(book.name, contents) != NULL || strstr(book.phone, contents) != NULL || strstr(book.memo, contents) != NULL)
        {
            mvprintw(i + 18, 0, "%d %s %s %s", i + 1, book.name, book.phone, book.memo); // 검색 결과가 있을 시 화면에 출력
            i++;
        }
    }
    fclose(file); // file close

    attron(COLOR_PAIR(2) | A_BOLD); // 찾은 라인이 있으면
    if( i > 0)
        printw("match found.\n"); // match found.
    else
        printw("no match found.\n"); // 그렇지 않으면 no match found
    attroff(COLOR_PAIR(2) | A_BOLD);
}

// 전화번호 정보를 파일에 추가해주는 함수
void add_tel(const char *filename, struct TelBook *book)
{
    FILE *file = fopen(filename, "a"); 
    if (file == NULL) {
        printw("You can't open file.\n");
        return ;
    }

    // fprintf 함수를 사용하여 파일에 전화번호 정보를 추가, book은 TelBook 구조체 포인터로, 전화번호 정보를 담고 있음
    // 각 정보는 ":" 문자로 구분되어 작성
    fprintf(file, "%s:%s:%s\n", book->name, book->phone, book->memo);
    fclose(file);
}

// 전화번호부 목록 제거 함수, 제거할 요소를 포함하는 부분을 입력받음.
void delete_tel(const char *filename, const char *contents) {
    FILE *file = fopen(filename, "r");
   // 파일 열기 실패시 메시지 출력, 함수 종료
    if (file == NULL) {
        mvprintw(18,0,"You can't open file.\n");
        return ;
    }

    char line[MAX_ENTRY]; // 파일에서 읽은 각 줄을 저장할 문자열
    int i= 0,j = 0; //i는 파일에서 읽은 줄의 수,j는 삭제할 항목 수
    int *d = NULL; // 삭제할 항목의 인덱스를 저장하는 동적 배열
    struct TelBook book[MAX_ENTRY];  // 전화번호부 엔트리를 저장할 구조체 배열
    while(fgets(line, sizeof(line), file)){

	// ':'을 기준으로 문자열을 분할하여 각 토큰을 가져옴
        // 각각의 토큰은 전화번호부 엔트리의 이름, 전화번호, 메모를 나타냄.
        char* token = strtok(line, ":");
        if (token == NULL) break;
        strcpy(book[i].name, token);

        token = strtok(NULL, ":");
        if (token == NULL) break;
        strcpy(book[i].phone, token);

        token = strtok(NULL, ":");
        if (token == NULL) break;
        strcpy(book[i].memo, token);

	// 각 엔트리가 사용자가 제거하려는 항목과 일치하는지 확인
        // 일치하는 경우, 그 엔트리의 인덱스를 'd' 배열에 저장하고, 해당 엔트리를 화면에 출력
        if(strstr(book[i].name, contents) != NULL || strstr(book[i].phone, contents) != NULL || strstr(book[i].memo, contents) != NULL){
            mvprintw(j+18,0,"%d %s %s %s\n", j + 1, book[i].name, book[i].phone, book[i].memo);
            int *temp_d = realloc(d, (j + 1) * sizeof(int));  // 'd' 배열을 재할당하여 새 인덱스를 저장할 공간을 만듦
            if (temp_d == NULL) {
                printw("Memory allocation failed. Exiting.\n");
                free(d); 
                return; 
            }
	    // 재할당한 메모리를 'd'에 연결하고, 새 인덱스를 저장
            d = temp_d;
            d[j] = i;
            j++;
        }
        i++;
    }
    int num = i; // 엔트리 수 저장 변수
    
    fclose(file);
    file = fopen(filename, "w"); // 파일 닫고 쓰기 모드로 다시 열어줌

    // 제대로 안열렸으면 error 메시지 출력
    if (file == NULL) {
    printw("Could not open file for writing.\n");
    free(d);
    return;
}

    int k;

    // 사용자에게 삭제할 항목의 번호를 선택하도록 요청
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(j+18,0,"choose the number: ");
    attroff(COLOR_PAIR(1));
    scanw("%d", &k);
    // 사용자의 입력이 유효한 범위에 있는지 확인
    // 범위를 벗어나면, 파일에 모든 엔트리를 다시 쓰고, 그렇지 않다면, 선택된 엔트리를 제외하고 모든 엔트리를 다시 작성
    attron(COLOR_PAIR(2) | A_BOLD);
    if ( k <= 0 || k > j ){
        mvprintw(j+19,0,"No range.\n");
        for( i=0; i<num; i++ )
            fprintf(file, "%s:%s:%s", book[i].name, book[i].phone, book[i].memo);
    }
    else {
        mvprintw(j+19,0,"removed success.\n");
        for( i=0; i<num; i++ ){
            if( i == d[k-1]) // 선택된 엔트리는 건너뛰고
                continue;
            else // 그 이외의 것은 파일에 작성
                fprintf(file, "%s:%s:%s", book[i].name, book[i].phone, book[i].memo);
        }
    }
    attroff(COLOR_PAIR(2)|A_BOLD);
    // 동적 할당한 메모리 해제
    free(d);
    //file close
    fclose(file);
}

// 전화번호 목록을 파일로부터 읽어와 출력하는 함수
void print_list(const char *filename) {
    FILE *file = fopen(filename, "r");
    if ( file == NULL ) {
        printw("You can't open file.\n");
        return ;
    }

    int i = 0;
    char line[MAX_ENTRY];
    struct TelBook book[MAX_ENTRY];
    // 파일로부터 한 줄씩 읽어와서 전화번호 목록을 저장
    while (fgets(line, sizeof(line), file)) {
        strcpy(book[i].name,strtok(line,":"));
        strcpy(book[i].phone,strtok(NULL,":"));
        strcpy(book[i].memo,strtok(NULL,":"));
        i++;
    }

    int num = i; // 전화번호 목록의 갯수 저장
    qsort(book , i, sizeof(struct TelBook), compare); // qsort 함수를 이용해 전화번호 목록을 이름으로 정렬
        
    for (i = 0; i < num; i++) {
    printw("%d %s %s %s\n", i + 1, book[i].name, book[i].phone, book[i].memo);
    }

    fclose(file);
}
// qsort 함수에 사용되는 비교 함수, 두 전화번호를 이름으로 비교
int compare(const void *a, const void *b) {
    const struct TelBook *bookA = (struct TelBook *) a;
    const struct TelBook *bookB = (struct TelBook *) b;

    return strcmp(bookA->name, bookB->name);
}


