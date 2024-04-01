#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // isdigit 함수를 사용하기 위해 ctype 헤더파일 선언

#define MAX 100 // 전화번호부에 저장할 수 있는 최대 항목 수

// phoneBook 구조체 선언
typedef struct {
	char name[30];
	char phone[20];
	char memo[40];
} PhoneBook; // 각 phonebook에는 이름, 전화번호, 메모 순서대로 포함


PhoneBook list[MAX]; // phonebook 항목들을 저장하는 list배열
int n = 0; // n은 현재 저장된 전화번호부 항목의 수를 추적하는 변수


// data.txt파일에서 전화번호부 데이터를 로드하는 함수
void loadPhoneBook() {
	FILE* file = fopen("data.txt", "r"); // data.txt파일을 r 모드로 열고
	if (file == NULL) { // 파일이 안열리면 오류 메시지 출력, 함수 종료
		printf("File could not be opened.\n");
		return;
	}

	char line[MAX]; // 한 줄을 읽기 위한 임시 문자열 변수
	// 한 줄씩 읽어서 분석
	while (fgets(line, sizeof(line), file)) {
		char *name = strtok(line, ":"); // strok함수를 사용해서 줄을 ':'문자로 분리
		char *phone = strtok(NULL, ":"); 
		char *memo = strtok(NULL, ":");

        if (name && phone && memo) { // 모든 필드가 존재하면
		char* newline = strchr(memo, '\n'); // memo 필드의 줄바꿈 문자를 찾고
		if (newline) *newline = '\0'; // 줄바꿈 문자 있으면 null로 교체
		
		// phonebook 항목 생성
		strcpy(list[n].name, name);
            	strcpy(list[n].phone, phone);
            	strcpy(list[n].memo, memo);
            n++; // 전화번호부 항목 수 증가
        }
    }

    fclose(file);		
}

// 현재 전화번호부의 내용을 data.txt파일에 저장하는 함수
void savePhoneBook() {
	FILE* file = fopen("data.txt", "w"); // 파일을 쓰기 모드로 열고
	if (file == NULL) { // 안열리면 오류 메시지 출력
		printf("File could not be opened.\n");
		exit(1);
	}

	// 전화번호부의 모든 항목을 파일에 쓰고
	for (int i = 0; i < n; i++) {
		fprintf(file, "%s:%s:%s\n", list[i].name, list[i].phone, list[i].memo);
	}

	fclose(file); // 파일을 닫는다.
}


// 전화번호부에서 키워드를 검색하는 함수
int searchPhoneBook(char* keyword) {
	int found = 0; // 키워드를 찾은 항목의 수를 저장하는 변수 found
	int isDigitFound = 0;
	
	for (int i = 0; i < strlen(keyword); i++) { // 키워드에 숫자가 있는지 확인
        if (isdigit(keyword[i])) { // 해당 문자가 0부터 9까지의 숫자인지 확인하기 위해 isdigit함수 사용
            isDigitFound = 1;
            break;
        }
    }
    if (isDigitFound) { // 숫자가 있으면 전화번호, 메모에서 검색
        for (int i = 0; i < n; i++) {
		// 전화번호, 메모에서 찾으면 해당 항목 출력
		if (strstr(list[i].phone, keyword) != NULL || strstr(list[i].phone, keyword) != NULL || strstr(list[i].memo, keyword) != NULL) {
			printf("%d %s %s %s\n", i , list[i].name, list[i].phone, list[i].memo);
                found++;
		}
	}
    }
    if(found > 0)
	    printf("match found.\n");
    return found; // 찾은 항목 수 반환
}

// 전화번호부에 새 항목 추가
void addPhoneBookEntry(char* name, char* phone, char* memo) {
	printf("%s %s %s\n", name, phone, memo);
	printf("add? [Y/N]: ");
	char response[3];
	fgets(response, sizeof(response), stdin);

	// 사용자의 입력에 따른 동작 결정
	if (response[0] == '\n') {
		printf("Invalid input.\n"); // 입력이 enter이면
		exit(0); // 함수 종료
	}
	else if (response[0] != 'Y' && response[0] != 'y') {
		printf("Invalid input.\n");
		exit(0);
	}

	if (response[0] == 'Y' || response[0] == 'y') { // y또는 Y이면 
		if(n < MAX) {
			strcpy(list[n].name, name);
			strcpy(list[n].phone, phone);
			strcpy(list[n].memo, memo);
			n++;
			savePhoneBook(); // 변경 사항을 파일에 저장
		} else { // 전화번호부가 가득 찬 경우
			printf("Phone book is full. Can't add new entry.\n");
		}
	}
}

// 전화번호부에서 항목을 삭제하는 함수
void deletePhoneBookEntry(char* name) {
	int foundIndexes[MAX];
	int found = 0;

	// 전화번호부를 순회하면서 삭제할 항목 검색
	for (int i = 0; i < n; i++) {
		if (strstr(list[i].name, name) != NULL || strstr(list[i].phone, name) != NULL || strstr(list[i].memo, name) != NULL) {
			printf("%d %s %s %s\n", found+1 , list[i].name, list[i].phone, list[i].memo);
			foundIndexes[found] = i; // 삭제할 항목의 인덱스를 배열에 저장
			found++;
		}
	}	
	if (found > 0) { // 삭제할 항목이 있을때
		printf("Which one? ");
		char input[100];
		fgets(input, sizeof(input), stdin); // fgets함수로 사용자의 전체 줄 입력을 받기
		input[strcspn(input, "\n")] = 0;

		if(strlen(input) == 0) { // strlen함수로 사용자의 입력이 비었는지 확인
			printf("Invalid index.\n");
			exit(0);
		}
		
		int index = atoi(input); //atoi함수로 입력값을 정수로 변환
		
		if(index <= 0 || index > found) {
			printf("Invalid index.\n");
			return;
		}
		// 선택된 항목 삭제
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

// 비교 함수
int compare(const void* a, const void* b) {
    return strcmp(((PhoneBook*)a)->name, ((PhoneBook*)b)->name);
}

// 전화번호부를 이름으로 정렬하고 출력하는 함수
void listBook() {
    // qsort를 사용하여 전화번호부를 이름으로 정렬
    qsort(list, n, sizeof(PhoneBook), compare);

    // 정렬된 전화번호부 출력
    for (int i = 0; i < n; i++) {
        printf("%d %s %s %s\n", i+1, list[i].name, list[i].phone, list[i].memo);
    }
}

// 프로그램 사용법을 알려주는 함수
void printUsage() {
	printf("Usage: tel [-adl] words\n");
	printf("Options:\n");
	printf("  -a name phone memo  Add new entry\n");
	printf("  -d name            Delete an entry\n");
	printf("  -l                 List all entries\n");
	printf("  word               Search for an entry\n");
}

int main(int argc, char* argv[]) {
	loadPhoneBook(); // 전화번호부 데이터 파일 로드

	if (argc < 2) {
		printUsage();
		return 0;
	}

	if (strcmp(argv[1], "-a") == 0) { // option a
		if (argc != 5) {
			printUsage(); // 잘못된 인수 개수인 경우 사용법 출력
			return 0;
		}
		addPhoneBookEntry(argv[2], argv[3], argv[4]);
	}
	else if (strcmp(argv[1], "-d") == 0) { // option d
		if (argc != 3) {
			printUsage();
			return 0;
		}
		deletePhoneBookEntry(argv[2]);
	}
	else if (strcmp(argv[1], "-l") == 0) { // option l
		if (argc != 2) {
			printUsage();
			return 0;
		}
		listBook();
	}
	else { // 키워드로 항목 검색
		if(!searchPhoneBook(argv[1])) { // 검색 결과가 없으면
			printf("no match found.\n"); // 일치 항목 없다는 표시 출력
		}
	}
	return 0;
}

