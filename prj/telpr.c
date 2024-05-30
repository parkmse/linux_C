#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[30];
    char phone[20];
    char memo[40];
} PhoneBook;

PhoneBook list[MAX];
int n = 0;

void loadPhoneBook() {
    FILE* file = fopen("data.txt", "r");

    while (fscanf(file, "%[^:]:%[^:]:%[^\n]\n", list[n].name, list[n].phone, list[n].memo) != EOF) {
        n++;
        list = realloc(list, (n + 1) * sizeof(PhoneBook));
    }
    fclose(file);
}

void savePhoneBook() {
    FILE* file = fopen("data.txt", "w");

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s:%s:%s\n", list[i].name, list[i].phone, list[i].memo);
    }
    fclose(file);
}

void addPhoneBook(char* name, char* phone, char* memo) {
    list = realloc(list, (n + 1) * sizeof(PhoneBook));
    strcpy(list[n].name, name);
    strcpy(list[n].phone, phone);
    strcpy(list[n].memo, memo);
    n++;
    savePhoneBook();
}

void searchPhoneBook(char* name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(list[i].name, name) == 0) {
            printf("Name: %s, Phone: %s, Memo: %s\n", list[i].name, list[i].phone, list[i].memo);
            return;
        }
    }
    printf("No such name found.\n");
}

void deletePhoneBook(char* name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(list[i].name, name) == 0) {
            for (int j = i; j < n - 1; j++) {
                list[j] = list[j + 1];
            }
            n--;
            list = realloc(list, n * sizeof(PhoneBook));
            savePhoneBook();
            printf("Deleted successfully.\n");
            return;
        }
    }
    printf("No such name found.\n");
}

int comparePhoneBookEntries(const void* a, const void* b) {
    const PhoneBook* entryA = (const PhoneBook*)a;
    const PhoneBook* entryB = (const PhoneBook*)b;
    return strcmp(entryA->name, entryB->name);
}

void listBook() {
    // Make a copy of the list to sort, so we don't modify the original list
    PhoneBook* sortedList = (PhoneBook*) malloc(sizeof(PhoneBook) * n);
    memcpy(sortedList, list, sizeof(PhoneBook) * n);

    // Sort the copy
    qsort(sortedList, n, sizeof(PhoneBook), comparePhoneBookEntries);

    // Print the sorted list
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Phone: %s, Memo: %s\n", sortedList[i].name, sortedList[i].phone, sortedList[i].memo);
    }

    // Free the sorted list
    free(sortedList);
}

int main(int argc, char* argv[]) {
	
	list = (PhoneBook*) malloc(sizeof(PhoneBook) * MAX);

    if (argc == 1) {
        printf("Usage: ./<program_name> <command> [arguments]\n");
        printf("Commands:\n");
        printf("add <name> <phone> <memo>: Add a new phone book entry\n");
        printf("search <name>: Search for a phone book entry by name\n");
        printf("delete <name>: Delete a phone book entry by name\n");
        printf("print: Print all phone book entries\n");
        free(list);
        return 1;
    }
    loadPhoneBook();

    if (strcmp(argv[1], "-a") == 0) {
        if (argc != 5) {
            printf("Usage: add <name> <phone> <memo>\n");
            return 1;
        }
        addPhoneBook(argv[2], argv[3], argv[4]);
    }
    else if (strcmp(argv[1], "search") == 0) {
        if (argc != 3) {
            printf("Usage: search <name>\n");
            return 1;
        }
        searchPhoneBook(argv[2]);
    }
    else if (strcmp(argv[1], "-d") == 0) {
        if (argc != 3) {
            printf("Usage: delete <name>\n");
            return 1;
        }
        deletePhoneBook(argv[2]);
    }
    else if (strcmp(argv[1], "-l") == 0) {
        listBook();
    }
    else {
        printf("Invalid command. Please use one of the following: add, search, delete, print.\n");
    }

    free(list);
    return 0;
}
   

