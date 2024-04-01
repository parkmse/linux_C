#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
// keytab의 크기를 요소 하나의 크기로 나눠 배열에 있는 요소 갯수를 계산
#define NKEYS (sizeof keytab / sizeof keytab[0]) 
#define BUFSIZE 100

char buf[BUFSIZE]; // getch와 ungetch를 위한 버퍼와 버퍼 위치
int bufpos = 0;

int getch(void) {
    return (bufpos > 0) ? buf[--bufpos] : getchar();
}

void ungetch(int c) {
    if (bufpos < BUFSIZE)
        buf[bufpos++] = c;
    else
        printf("ungetch: too many characters\n");
}

struct key {
	char *word;
	int count; // 등장 횟수를 입력받기 위한 변수
}
keytab[] = {"auto", 0, "break", 0, "case", 0, "char", 0, "const", 0, "continue", 0, "default", 0,"do", 0, "double", 0,"else", 0,"enum", 0, "extern", 0," float", 0, "for", 0, "goto", 0, "if", 0,"int", 0,"long", 0,"register",0,"return",0,"short",0,"signed",0,"sizeof",0,"static",0,"struct",0,"switch",0,"typedef",0,"union",0,"unsigned",0,"void",0,"volatile",0,"while",0};

// 입력에서 단어를 읽어들이는 함수
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while(isspace(c = getch())) // 공백 문자를 건너뜀
		;

	if(c != EOF)
		*w++ = c;
	
	if(!isalpha(c)){ // 첫 문자가 알파벳이 아니면 더이상 읽지 않음
		*w = '\0';
		return c;
	}

	for(; --lim > 0; w++){ // 나머지 문자를 읽음
		if(!isalnum(*w = getch())){
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

// 이진 탐색 함수
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low = 0, high = n - 1, mid;

	while(low <= high){
		mid = (low + high) / 2;
		if((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1; // 왼쪽에 위치
		else if(cond > 0)
			low = mid + 1; // 오른쪽에 위치
		else
			return mid;
	}
	return -1;
}

int main(void)
{
	int n;
	char word[MAXWORD];

	// 모든 단어에 대한 키워드 여부를 확인하고
	// 키워드의 등장 횟수를 증가함.
	while(getword(word, MAXWORD) != EOF)
		if(isalpha(word[0]))
			if((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for(n = 0; n < NKEYS; n++)
		if(keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);

	return 0;
}
