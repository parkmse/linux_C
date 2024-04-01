#include <stdio.h>

int main(void)
{
	int i = 65;
	
	printf("%d\n", i); // 예상 결과값: 65
	printf("%o\n", i); // 예상 결과값: 101
	printf("%X\n", i); // 예상 결과값: 41
	printf("%c\n", i); // 예상 결과값: A
	printf("%f\n", i); // int형 변수와 형식 지정자가 %f가 맞지 않아서 실행 오류 발생, 예상 결과값: 0.000000
	printf("%e\n", i); // 서식 문자열 e에 double형 인수가 필요하지만 인수 형식이 int이므로 오류 발생 ,  예상 결과값: 1.677571e-308
	printf("%g\n", i); // 서식 문자열 g에 double형 인수가 필요하지만 인수 형식이 int이므로 오류 발생,  예상 결과값: 1.67757e-308

	return 0;
}
