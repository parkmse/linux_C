#include <stdio.h>

int i = 10; // 전역변수 i선언, 초기화

void f(void)
{
	int i = 1; // 지역변수 i 선언, 초기화
	printf("i in f() is %d\n", i++);
}

void s(void)
{
	static int i = 100; // 정적변수 i선언, 초기화
	printf("i in s() is %d\n", i++);
}

int main(void)
{
	for ( int j = 0; j < 3; ++j){ 
		printf("i in main() is %d\n", i++); // 전역 변수 i 출력
		f(); // 함수 f 호출
		s(); // s 호출
	}
	return 0;
}
