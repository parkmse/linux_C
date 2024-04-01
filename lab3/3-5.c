#include <stdio.h>
int main()
{
	int x, i;
	for (x = 2; x <= 200; x++) // x는 2부터 200까지 증가하면서
	{
		for (i = 2; i <= x/2; i++) // x의 약수를 구함.
		{
			if ((x % i) == 0){ // x가 i로 나누어 떨어지면 i는 x의 약수임
				break;
			}
		}
		if ( i > x /2) // x가 소수이면 출력
		{
			printf("%d ", x);
		}
	}
	printf("\n");
	return 0;
}
