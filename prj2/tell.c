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

void init_terminal();
void print_menu(WINDOW*, int);
void handle_menu(WINDOW*, const char*);
void search_tel(const char*, char*);
void add_tel(const char*, struct TelBook*);
void delete_tel(const char*, const char*);
void print_list(const char*);
int compare(const void*, const void*);

char* choices[] = {
    "Search - Find entries by a content.",
    "Add - Create a new entry with name, phone number, and memo.",
    "Delete - Remove an entry by content.",
    "List - Sort and display all entries.",
    "Exit"
};

int n_choices = sizeof(choices) / sizeof(char*);

void init_terminal() {
    initscr();
    clear();
    noecho();
    cbreak();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
}

void print_menu(WINDOW* menu_win, int highlight)
{
    int x, y, i;
    int Mx, My;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 0, 1, "Select One");
    for (i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}

void handle_menu(WINDOW* menu_win, const char *filename) {
    int highlight = 1;
    int choice = 0;
    int c;

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
            mvprintw(24, 0, "The pressed key is: '%c'", c);
            refresh();
            break;
        }
        print_menu(menu_win, highlight);
        if (choice != 0) {
            char search_term[30];
            struct TelBook new_book;
            switch (choice) {
                case 1:
                    echo();
                    mvprintw(24, 0, "Enter search term: ");
                    getstr(search_term);
                    noecho(); // disable echoing of input again
                    search_tel(filename, search_term);
                    break;
                case 2:
                    echo(); // enable echoing of input
                    mvprintw(24, 0, "Enter new entry (name:phone:memo): ");
                    getstr(search_term);
                    char* name = strtok(search_term, ":");
                    char* phone = strtok(NULL, ":");
                    char* memo = strtok(NULL, ":");

                    if (name && phone && memo) {
                        strcpy(new_book.name, strtok(search_term, ":"));
                        strcpy(new_book.phone, strtok(NULL, ":"));
                        strcpy(new_book.memo, strtok(NULL, ":"));
                        add_tel(filename, &new_book);
                    }
                    else {
                        printw("Invalid input.\n");
                    }
                    noecho();
                    break;
                case 3:
                    echo(); // enable echoing of input
                    mvprintw(24, 0, "Enter entry to delete (name or phone or memo): ");
                    getstr(search_term);
                    delete_tel(filename, search_term);
                    noecho();
                    break;
                case 4:
                    print_list(filename);
                    break;
		case 5:
		    endwin();
		    exit(0);
		    break;
                }
                choice = 0;
                wclear(menu_win);
                print_menu(menu_win, highlight);
            }
        }
 }

void search_tel(const char* filename, char* contents)
{
    FILE* file = fopen(filename, "r");
    int i = 0;

    if (file == NULL) {
        printw("You can't open file.\n");
        return;
    }

    struct TelBook book;
    char line[MAX_ENTRY];
    while (fgets(line, sizeof(line), file)) {
        strcpy(book.name, strtok(line, ":"));
        strcpy(book.phone, strtok(NULL, ":"));
        strcpy(book.memo, strtok(NULL, ":"));

        if (strstr(book.name, contents) != NULL || strstr(book.phone, contents) != NULL || strstr(book.memo, contents) != NULL) {
            printw("%d %s %s %s\n", i + 1, book.name, book.phone, book.memo);
            i++;
        }
    }

    fclose(file);

    if (i > 0)
        printw("match found.\n");
    else
        printw("no match found.\n");
}

void add_tel(const char* filename, struct TelBook* book)
{
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printw("You can't open file.\n");
        return;
    }

    fprintf(file, "%s:%s:%s\n", book->name, book->phone, book->memo);
    fclose(file);
}

void delete_tel(const char* filename, const char* contents) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printw("You can't open file.\n");
        return;
    }

    char line[MAX_ENTRY];
    int i = 0, j = 0;
    int* d = NULL;
    struct TelBook book[MAX_ENTRY];
    while (fgets(line, sizeof(line), file)) {
        strcpy(book[i].name, strtok(line, ":"));
        strcpy(book[i].phone, strtok(NULL, ":"));
        strcpy(book[i].memo, strtok(NULL, ":"));

        if (strstr(book[i].name, contents) != NULL || strstr(book[i].phone, contents) != NULL || strstr(book[i].memo, contents) != NULL) {
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

    if (k <= 0 || k > j) {
        printw("No range. can't remove.\n");
        for (i = 0; i < num; i++)
            fprintf(file, "%s:%s:%s\n", book[i].name, book[i].phone, book[i].memo);
    }
    else {
        printw("removed.\n");
        for (i = 0; i < num; i++) {
            if (i == d[k - 1])
                continue;
            else
                fprintf(file, "%s:%s:%s\n", book[i].name, book[i].phone, book[i].memo);
        }
    }
    free(d);
    fclose(file);
}

void print_list(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printw("You can't open file.\n");
        return;
    }

    int i = 0;
    char line[MAX_ENTRY];
    struct TelBook book[MAX_ENTRY];
    while (fgets(line, sizeof(line), file)) {
        strcpy(book[i].name, strtok(line, ":"));
        strcpy(book[i].phone, strtok(NULL, ":"));
        strcpy(book[i].memo, strtok(NULL, ":"));
        i++;
    }

    int num = i;
    qsort(book, i, sizeof(struct TelBook), compare);

    for (i = 0; i < num; i++) {
        printw("%d %s %s %s\n", i + 1, book[i].name, book[i].phone, book[i].memo);
    }

    fclose(file);
}

int compare(const void* a, const void* b) {
    struct TelBook* bookA = (struct TelBook*)a;
    struct TelBook* bookB = (struct TelBook*)b;

    return strcmp(bookA->name, bookB->name);
}

int main() {
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

    const char* filename = "data.txt";

    mvprintw(0, 0, "Welcome to the TelBook Program with ncurses.\n");
    mvprintw(1, 0, "Please, select an operation from the menu:\n");
    mvprintw(2, 0, "1. Search - Find entries by a content.\n");
    mvprintw(3, 0, "2. Add - Create a new entry with name, phone number, and memo.\n");
    mvprintw(4, 0, "3. Delete - Remove an entry by content.\n");
    mvprintw(5, 0, "4. List - Sort and display all entries.\n");
    refresh();

    handle_menu(menu_win, filename);

    mvprintw(My - 1, 0, "Press any Key for Exit screen");
    getch();
    endwin();
    return 0;
}
