// 화씨 섭씨 변환 프로그램
#include <stdio.h>

int main()
{
	double fahr, celsius; // 소숫점 6자리까지는 float형 변수 사용 가능하나 double형 사용
	int lower, upper, step;

	lower = 0; // 최저값
	upper = 200; // 최고값
	step = 20; // step size

	printf("fahrenheit\t celsius\n"); // 일정한 크기의 blank를 위해 \t 사용

	fahr = lower;
	while (fahr <= upper){
		celsius = (5.0/9.0) * (fahr-32.0); // 화씨온도->섭씨온도
		printf("%3.6lf \t %3.6lf\n", fahr, celsius); //정수는 3자리, 소숫점 아래는 6자리까지 표현하기 위해 double형식 지정자 lf 앞에 3.6을 표현함  
		fahr = fahr + step;
	}
}
