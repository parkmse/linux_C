#include <stdio.h>

void cd(int x,int y); /// 함수 선언

int main()
{
	int x, y;
	scanf("%d %d", &x, &y);

	cd(x,y); // 함수 호출

	return 0;
}

void cd(int x, int y) // 공약수를 출력하는 함수 정의
{
	int count = 0;

	for( int i = 1; i<=x&&i<=y; i++) // i는 1부터, x와 y보다 작을때까지 증가
	{
		if(x % i == 0 && y % i ==0) // x,y와 i를 나눈 나머지가 둘 다 0이면
		{
			printf("%d ",i); // i 출력
		}
	}
	printf("\n");
}
