#include <stdio.h>

#define IN 1 // 단어 시작 상태
#define OUT 0 // 단어 끝 상태

int main()
{
    int c, state;

    state = OUT; // 단어가 시작되지 않은 상태
    while ((c = getchar()) != EOF) // EOF가 입력될 때 까지 문자를 읽음
    {
        if (c == ' ' || c == '\n' || c == '\t')
       	{
            if (state == IN) // 현재 단어가 끝남
	    {
                putchar('\n'); // 줄바꿈 출력
                state = OUT; // 단어를 끝난 상태로 변경
            }
        }
       	else
       	{
            putchar(c);
            state = IN;
        }
    }
    return 0;
}
