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

int searchPhoneBookByName(char* name) {
	int found = 0;
	for (int i = 0; i < n; i++) {
		if (strstr(list[i].name, name) != NULL) {
			printf("%d. Name: %s, Phone: %s, Memo: %s\n", i + 1, list[i].name, list[i].phone, list[i].memo);
			found++;
		}
	}
	return found;
}

void addPhoneBookEntry(char* name, char* phone, char* memo) {
	strcpy(list[n].name, name);
	strcpy(list[n].phone, phone);
	strcpy(list[n].memo, memo);
	n++;
	savePhoneBook();
}

void deletePhoneBookEntry(int index) {
	if (index >= 0 && index < n) {
		for (int j = index; j < n - 1; j++) {
			list[j] = list[j + 1];
		}
		n--;
		savePhoneBook();
		printf("Deleted successfully.\n");
	}
	else {
		printf("Invalid index.\n");
	}
}

int comparePhoneBookEntries(const void* a, const void* b) {
	const PhoneBook* entryA = (const PhoneBook*)a;
	const PhoneBook* entryB = (const PhoneBook*)b;
	return strcmp(entryA->name, entryB->name);
}

void listBook() {
	qsort(list, n, sizeof(PhoneBook), comparePhoneBookEntries);

	for (int i = 0; i < n; i++) {
		printf("Name: %s, Phone: %s, Memo: %s\n", list[i].name, list[i].phone, list[i].memo);
	}
}

int main(int argc, char* argv[]) {
	loadPhoneBook();

	if (argc < 2) {
		printf("Usage: tel [-adl] words\n");
		return 0;
	}

	char* command = argv[1];
	if (strcmp(command, "-a") == 0) {
		if (argc != 5) {
			printf("Usage: tel -a name phone memo\n");
			return 0;
		}
		addPhoneBookEntry(argv[2], argv[3], argv[4]);
	}
	else if (strcmp(command, "-d") == 0) {
		if (argc != 3) {
			printf("Usage: tel -d name\n");
			return 0;
		}
		int found = searchPhoneBookByName(argv[2]);
		if (found > 0) {
			printf("Which one? ");
			int index;
			scanf("%d", &index);
			deletePhoneBookEntry(index - 1);
		}
		else {
			printf("No such name found.\n");
		}
	}
	else if (strcmp(command, "-l") == 0) {
		if (argc != 2) {
			printf("Usage: tel -l\n");
			return 0;
		}
		listBook();
	}
	else {
		if (argc != 2) {
			printf("Usage: tel name\n");
			return 0;
		}
		int found = searchPhoneBookByName(argv[1]);
		if (found == 0) {
			printf("No such name found.\n");
		}
	}
	return 0;
}

