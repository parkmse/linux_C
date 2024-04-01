#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	for(int i = 0; i < 4; i++){ //4번 반복하여 난수 생성, 출력
		printf("%3d",rand()%10); //0부터 9까지의 난수 생성
	}
	printf("\n");

	return 0;
}	
