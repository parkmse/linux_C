#include <stdio.h>
#include <math.h> // math.h 함수 사용

int main(void)
{
	double x, y; 
	for (x = 1.0; x <= 10.0; x++) // 1부터 10까지 x값 증가
	{
		y = sqrt(x); // 제곱근을 구해주는 sqrt함수 사용하여 x의 제곱근을 변수 y에 저장
		printf("SQRT( %.1lf) = %.5lf\n", x, y); 
	}
	return 0;
}
