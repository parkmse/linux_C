#include <stdio.h>
#include <string.h>

#define SIZE 100 	// 계산 문자들이 들어갈 배열
#define BUFSIZE 100 	// getch함수를 만들기 위해서

char buf[BUFSIZE];
int bufp = 0;

int getch(void)		//입력 버퍼 오류 방지 getch함수 정의
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) // getch로 가져온 문자 다시 입력 버퍼에 넣어줌
{
	if (bufp >= BUFSIZE)
		printf("ungetch : too many characters\n");
	else
		buf[bufp++] = c;
}

double result(double x, double y, char op) // 결과값 반환 함수
{
	double res = 0.0; // double 값 초기화.

	if (op == '+')
		res = x + y;

	else if (op == '-')
		res = x - y;

	else if (op == '*')
		res = x * y;

	else if (op == '/')
		res = y == 0 ? 0 : x / y;       // 분모 0 방지

	else if (op == '%')
		res = y == 0 ? 0 : ((int)x % (int)y);  // 정수형으로 나누기 위함.

	else
		res = 0;      // 입력받은 연산자가 아닐 시 0

	return res; // 결과값 반환

}


int main(void)
{
	char c, op;
	double x = 0.0, y = 0.0, k = 0.1;
	int dp = 0, i = 0, j = 0;

	char calc[SIZE] = { 0 };	// 배열 초기화

	while ((c = getch()) != EOF)	// EOF 입력 될때까지
	{
		if (c == '\n') {		// 줄바꿈(enter) 입력 시 계산
			for (j = 0; calc[j] >= '0' && calc[j] <= '9'; j++) {
				x = x * 10.0 + (calc[j] - '0');				// 첫번째 숫자 입력되는 동안 숫자 계산
			}
			if (calc[j] == '.') {						// 소수점이 들어가면 실수임을 나타냄
				dp = 1;
				for (++j; calc[j] >= '0' && calc[j] <= '9'; j++) { 	// 소수점 이후부터 숫자나오는동안 소수점 계산
					x = x + k * (calc[j] - '0');			// 소수점 이하 추가
					k *= 0.1;
				}
				k = 0.1;	// k 초기화
			}

			op = calc[j];

			for (j++; calc[j] >= '0' && calc[j] <= '9'; j++) {
				y = y * 10.0 + (calc[j] - '0');
			}
			if (calc[j] == '.') {
				dp = 1;
				for (j++; calc[j] >= '0' && calc[j] <= '9'; j++) {
					y = y + k * (calc[j] - '0');
					k *= 0.1;
				}
				k = 0.1;
			}

			if (dp == 1)
				printf("%lf\n", result(x, y, op));			// 결과값 실수형으로 출력
			else
				printf("%d\n", (int)result((int)x, (int)y, op));	// 결과값 정수형으로 출력
			x = y = i = j = dp = 0; 					// 모든 변수 초기화
			op = ' '; 							// 연산자 초기화
			memset(calc, 0, sizeof(calc)); 					// 배열 초기화
		}
		else {
			if (c == ' ' || c == '\t'); 					// ' ' '\t'의 경우 출력 x
			else {
				calc[i] = c;
				i++;
			}
		}
	}
	return 0;
}
