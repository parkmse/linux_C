#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXWORD 100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufpos = 0;

// 입력 버퍼 관리 함수
int getch(void) {
    return (bufpos > 0) ? buf[--bufpos] : getchar(); // 버퍼가 비었으면 표준 입력, 안비었으면 버퍼로부터 문자 가져옴
}

//추출한 단어를 이진 트리에 추가
void ungetch(int c) {
    if (bufpos < BUFSIZE) // 버퍼가 가득 안차있으면 입력된 문자를 버퍼에 넣음
        buf[bufpos++] = c;
    else
        printf("ungetch: too many characters\n");
}

// 입력에서 단어를 가져오는 함수
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while(isspace(c = getch()))
		;
	if(c != EOF)
		*w++ = c;
	if(!isalpha(c)){
		*w = '\0';
		return c;
	}
	for(; --lim > 0; w++)
		if(!isalnum(*w = getch())){
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

struct tnode {
    char *word;
    int count;
    struct tnode *left; // 왼쪽 자식 노드
    struct tnode *right; // 오른쪽 자식 노드
};

struct tnode *talloc(void)
{
        return (struct tnode *) malloc(sizeof(struct tnode));
}

// 문자열을 복사해서 새 동적 메모리를 반환
char *my_strdup(char *s)
{
        char *p;
        p = (char *) malloc(strlen(s) + 1);
        if(p != NULL)
                strcpy(p, s);
        return p;
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) { // 추가하려는 단어와 현재 노드의 단어가 같으면 카운트 증가
        p->count++;
    } else if (cond < 0) { // 현재 노드의 단어보다 알파벳순으로 앞서면
        p->left = addtree(p->left, w); // 왼쪽 노드에 추가
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

// 이진 트리를 알파벳 순서로 출력
void treeprint(struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s: %d\n", p->word, p->count);
        treeprint(p->right);
    }
}

int main() {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
	    if(isalpha(word[0])) // 읽어온 문자가 알파벳 문자면 트리에 추가
	    root = addtree(root, word);
    }
    treeprint(root);

    return 0;
}
