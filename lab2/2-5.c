#include <stdio.h>
#include <limits.h>

int main()
{
	printf("ungsiged char's min = 0\t\t unsigned char's max = %d\n", UCHAR_MAX); // unsigned char는 부호가 없는 8비트 정수형 데이터 타입, 0 이상의 값을 가지기 때문에 최솟값은 0
	printf("signed char's min = %d\t signed char's max = %d\n", SCHAR_MIN, SCHAR_MAX);

	printf("unsigned short's min = 0\t unsigned short's max = %d\n", USHRT_MAX); // unsigned short도 마찬가지로 부호가 없으므로 최솟값은 0임.
	printf("signed short's min = %d\t signed short's max = %d\n", SHRT_MIN, SHRT_MAX);

	printf("unsigned int's min = 0\t\t unsigned int's max = %u\n", UINT_MAX); // 부호 있는 정수 signed int의 출력에 사용되는 %d 형식 지정자와 다르기 때문에 unsigned int의 최댓값을 출력할 때 %u 형식 지정자 사용
	printf("signed int's min = %d\t signed int's max = %d\n", INT_MIN, INT_MAX);

	printf("unsigned long's min = 0\t\t unsigned long's max = %lu\n", ULONG_MAX); // 위와 동일한 이유로 unsigned long 에는 %lu 형식 지정자 사용
	printf("signed long's min = %ld\t signed long's max = %ld\n", LONG_MIN, LONG_MAX); // signed long (int)와 int64는 모두 정수형 데이터 타입이지만, 시스템에 따라 다른 크기와 범위를 가질 수 있음. int64는 64비트 정수형 데이터 타입으로 출력의 범위가 -9223372036854775808 ~ 9223372036854775807로 나오는 것으로 판단. 

	return 0;
}

