#include <stdio.h>

#define IN 1
#define OUT 0

int main()
{
	int c, nl, nw, nc, state; // ex) i love you -> nl:3개(word)

	state = OUT;
	nl = nw = nc = 0;
	while ((c=getchar()) != EOF){
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t') // 빈칸 방지 코드
			state = OUT; // c가 빈칸이거나 \n이거나 tab인 경우 state를 
		// out으로 변경
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("line 갯수:%d word 갯수: %d 캐릭터 갯수:%d\n", nl, nw, nc);
}
