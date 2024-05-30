#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
	char name[30];
	char phone[20];
	char memo[40];
} PhoneBook;

PhoneBook list[MAX];
void addPhoneBookEntry(char* name, char* phone, char* memo);
int n = 0;

void loadPhoneBook() {
	FILE* file = fopen("data.txt", "r");
	if (file == NULL) {
		printf("Could not open file. The program will continue without loading data.\n");
		return;
	}
	char line[MAX];
	while (fgets(line, MAX, file) != NULL) {
		char* name = strtok(line, ":");
		char* phone = strtok(NULL, ":");
		char* memo = strtok(NULL, ":");
	       
		name[strcspn(name, " \n")] = '\0';
		phone[strcspn(phone, " \n")] = '\0';
	       	memo[strcspn(memo, " \n")] = '\0';

		addPhoneBookEntry(name, phone, memo);
    }

    fclose(file);

}

void savePhoneBook() {
	FILE* file = fopen("data.txt", "w");
	if (file == NULL) {
		printf("Could not open file. Changes will not be saved.\n");
		return;
	}

	for (int i = 0; i < n; i++)
       //	{ fprintf(file, "%s:%s:%s\n", list[i].name, list[i].phone, list[i].memo);
	 //      	if (i < n-1) { fprintf(file, "\n");
	//	}
	{
		if (i<n-1){
			fprintf(file, "%s:%s:%s\n", list[i].name, list[i].phone, list[i].memo);}
		else{
			fprintf(file, "%s:%s:%s", list[i].name, list[i].phone, list[i].memo);}
		}	

	fclose(file);
}

int searchPhoneBook(char* keyword) {
	int found = 0;
	for (int i = 0; i < n; i++) {
		if (strstr(list[i].name, keyword) != NULL || strstr(list[i].phone, keyword) != NULL || strstr(list[i].memo, keyword) != NULL) {
			printf("%d %s %s %s\n", found , list[i].name, list[i].phone, list[i].memo);
			found++;
		}
	}

	if (found >0)
		printf("match found.\n");
	
	return found;
}

void addPhoneBookEntry(char* name, char* phone, char* memo) {
	printf("%s %s %s\n", name, phone, memo);
	printf("add? [Y/N]: ");
	char response;
	scanf(" %c", &response);
	if (response == 'Y' || response == 'y') {
		if(n < MAX) {
			strcpy(list[n].name, name);
			strcpy(list[n].phone, phone);
			strcpy(list[n].memo, memo);
			n++;
			savePhoneBook();
		} else {
			printf("Phone book is full. Can't add new entry.\n");
		}
	}
}

void deletePhoneBookEntry(char* name) {
	int foundIndexes[MAX];
	int found = 0;
	//int found = searchPhoneBook(name);
	for (int i = 0; i < n; i++) {
		if (strstr(list[i].name, name) != NULL || strstr(list[i].phone, name) != NULL || strstr(list[i].memo, name) != NULL) {
			printf("%d %s %s %s\n", found+1 , list[i].name, list[i].phone, list[i].memo);
			foundIndexes[found] = i;
			found++;
		}
	}	
	if (found > 0) {
		printf("Which one? ");
		int index;
		scanf("%d", &index);
		if(index <= 0 || index > found) {
			printf("Invalid index.\n");
			return;
		}
		for (int j = foundIndexes[index - 1]; j < n - 1; j++) {
			list[j] = list[j + 1];
		}
		n--;
		savePhoneBook();
		printf("Deleted successfully.\n");
	}
	else {
		printf("No such name found.\n");
	}
}

void listBook() {
	for (int i = 0; i < n; i++) {
		printf("%s %s %s\n", list[i].name, list[i].phone, list[i].memo);
	}
}
void printUsage() {
	printf("Usage: tel [-adl] words\n");
	printf("Options:\n");
	printf("  -a name phone memo  Add new entry\n");
	printf("  -d name            Delete an entry\n");
	printf("  -l                 List all entries\n");
	printf("  word               Search for an entry\n");
}

int main(int argc, char* argv[]) {
	loadPhoneBook();

	if (argc < 2) {
		printUsage();
		return 0;
	}

	if (strcmp(argv[1], "-a") == 0) {
		if (argc != 5) {
			printUsage();
			return 0;
		}
		addPhoneBookEntry(argv[2], argv[3], argv[4]);
	}
	else if (strcmp(argv[1], "-d") == 0) {
		if (argc != 3) {
			printUsage();
			return 0;
		}
		deletePhoneBookEntry(argv[2]);
	}
	else if (strcmp(argv[1], "-l") == 0) {
		if (argc != 2) {
			printUsage();
			return 0;
		}
		listBook();
	}
	else {
		if(!searchPhoneBook(argv[1])) {
			printf("no match found.\n");
		}
	}
	return 0;
}

