#include <stdio.h>
#include <string.h>

//문자열 길이 반환 함수
int mystrlen(char *s){
	int n;

	for(n=0;*s != '\0'; s++) // null이 있을 때 까지 문자열 길이 계산
		n++; //null이 아니면 n증가

	return n;
}

int main(void)
{
	char *s[] = {"This is lab5", "Easy C Programming", "Have fun"}; // 문자열을 포인터 배열로 선언.


	int n = (int)(sizeof(s)/sizeof(char *));

	// 각각 strlen, mystrlen 함수를 사용하여 문자열 길이 출력
	printf("with strlen()\n"); 
	for( int i = 0; i<n; i++)
		printf("%s %d\n", *(s+i), (int)strlen(s[i]));
	putchar('\n');

	printf("with mystrlen()\n");
	for(int i = 0; i < n; i++)
		printf("%s %d\n", *(s+i), (int)strlen(s[i]));
	putchar('\n');


	return 0;
}
