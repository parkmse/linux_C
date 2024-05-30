#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRY 200

struct TelBook {
    char name[30];
    char phone[20];
    char memo[40];
};

void search_tel(const char *filename, char *contents);
void add_tel(const char *filename, struct TelBook *book);
void delete_tel(const char *filename, const char *contents);
void print_list(const char *filename);
int compare(const void*a, const void *b);

char *choices[] = { 
			"Search",
			"Add",
			"Delete",
			"List",
			"Exit",
		  };

int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight);

int main()
{
    WINDOW* menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
    init_pair(2, COLOR_BLUE, COLOR_BLACK); 

    int Mx, My;
    getmaxyx(stdscr, My, Mx);

    menu_win = newwin(9, Mx - 5, 6, 0);
    keypad(menu_win, TRUE);

    mvprintw(0, 0, "Welcome to the TelBook Program with ncurses.\n");
    mvprintw(1, 0, "Please, select an operation from the menu:\n");
    mvprintw(2, 0, "1. Search - Find entries by a content.\n");
    mvprintw(3, 0, "2. Add - Create a new entry with name, phone number, and memo.\n");
    mvprintw(4, 0, "3. Delete - Remove an entry by content.\n");
    mvprintw(5, 0, "4. List - Sort and display all entries.\n");
    refresh();

    print_menu(menu_win, highlight);

    while (1) {
        c = wgetch(menu_win);
        switch (c) {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_choices)
                highlight = 1;
            else
                ++highlight;
            break;
        case 10:
            choice = highlight;
            break;
        default:
            mvprintw(15, 0, "The pressed key is: '%c'", c);
            refresh();
            break;
        }
        print_menu(menu_win, highlight);
        if (choice != 0)
            break;
    }
 
    mvprintw(16, 0, "You chose choice %d with choice string %s\n", choice, choices[choice-1]);
    clrtoeol();
    refresh();

    if (choice == 1){
        char searchT[10];
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(17,0, "Please enter the string you want to search: ");
        attroff(COLOR_PAIR(1));
        getstr(searchT);
        mvprintw(18, 0, "Searching for entries with '%s'", searchT);
        search_tel("data.txt", searchT);
        attron(COLOR_PAIR(2) | A_BOLD);
        mvprintw(19, 0, "Search Completed.");
        attroff(COLOR_PAIR(2) | A_BOLD);

    } 
    else if (choice == 2) {
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
            mvprintw(26, 0, "Added successfully");
        }
        else {
            mvprintw(26, 0, "canceled");
        }
        attroff(A_BOLD);
    }
    else if (choice == 3) {
        char name[10];
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(17, 0, "Enter name to delete: ");
        getstr(name);
        attroff(A_BOLD);
        delete_tel("data.txt", name);
        mvprintw(18, 0, "Delete completed.");
    }
    else if (choice == 4) {
        attron(COLOR_PAIR(1) | A_BOLD);
        mvprintw(17, 0, "List of TelBook entries: ");
        attroff(A_BOLD);
        print_list("data.txt");
        mvprintw(18, 0, "List operation completed.");
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
        if(highlight == i+1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}
void search_tel(const char *filename, char *contents)
{
    FILE *file = fopen(filename, "r");
    int i = 0;

    if ( file == NULL ){
        printw("You can't open file.\n");
        return ;
    }

    struct TelBook book;
    char line[MAX_ENTRY];
    while (fgets(line, sizeof(line), file)) {
        strcpy(book.name, strtok(line, ":"));
        strcpy(book.phone , strtok(NULL, ":"));
        strcpy(book.memo, strtok(NULL, ":"));

        if (strstr(book.name, contents) != NULL || strstr(book.phone, contents) != NULL || strstr(book.memo, contents) != NULL) {
        printw("%d %s %s %s", i+1, book.name, book.phone, book.memo);		
        i++;
        }
    }

    fclose(file);
    
    if( i > 0)
        printw("match found.\n");
    else
        printw("no match found.\n");
}

void add_tel(const char *filename, struct TelBook *book)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printw("You can't open file.\n");
        return ;
    }

    fprintf(file, "%s:%s:%s\n", book->name, book->phone, book->memo);
    fclose(file);
}

void delete_tel(const char *filename, const char *contents) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printw("You can't open file.\n");
        return ;
    }

    char line[MAX_ENTRY];
    int i= 0,j = 0;
    int *d = NULL;
    struct TelBook book[MAX_ENTRY];
    while(fgets(line, sizeof(line), file)){
        strcpy(book[i].name, strtok(line, ":"));
        strcpy(book[i].phone , strtok(NULL, ":"));
        strcpy(book[i].memo , strtok(NULL, ":"));

        if(strstr(book[i].name, contents) != NULL || strstr(book[i].phone, contents) != NULL || strstr(book[i].memo, contents) != NULL){
            printw("%d %s %s %s\n", j + 1, book[i].name, book[i].phone, book[i].memo);
            d = realloc(d, (j + 1) * sizeof(int));
            d[j] = i;
            j++;
        }
        i++;
    }
    int num = i;
    
    fclose(file);

    file = fopen(filename, "w");
    
    int k;
    printw("which one? : ");
    char k_str[10];
    getstr(k_str);
    k = atoi(k_str);

    if ( k <= 0 || k > j ){
        printw("No range. can't remove.\n");
        for( i=0; i<num; i++ )
            fprintf(file, "%s:%s:%s", book[i].name, book[i].phone, book[i].memo);
    }
    else {
        printw("removed.\n");
        for( i=0; i<num; i++ ){
            if( i == d[k-1])
                continue;
            else
                fprintf(file, "%s:%s:%s", book[i].name, book[i].phone, book[i].memo);
        }
    }
    free(d);
    fclose(file);
}

void print_list(const char *filename) {
    FILE *file = fopen(filename, "r");
    if ( file == NULL ) {
        printw("You can't open file.\n");
        return ;
    }

    int i = 0;
    char line[MAX_ENTRY];
    struct TelBook book[MAX_ENTRY];
    while (fgets(line, sizeof(line), file)) {
        strcpy(book[i].name,strtok(line,":"));
        strcpy(book[i].phone,strtok(NULL,":"));
        strcpy(book[i].memo,strtok(NULL,":"));
        i++;
    }

    int num = i;
    qsort(book , i, sizeof(struct TelBook), compare);
        
    for (i = 0; i < num; i++) {
    printw("%d %s %s %s\n", i + 1, book[i].name, book[i].phone, book[i].memo);
    }

    fclose(file);
}

int compare(const void *a, const void *b) {
    struct TelBook *bookA = (struct TelBook *) a;
    struct TelBook *bookB = (struct TelBook *) b;

    return strcmp(bookA->name, bookB->name);
}
