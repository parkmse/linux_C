#include <stdio.h>

int main(void)
{
	int a[][3] = {{1,2,3},
		     {4,5,6},
 		     {7,8,9}};
	int *pa[] = {a[0], a[1], a[2]}; // 포인터 배열 pa, a의 행 각각을 가리킴
	int *p = a[0]; // a[0][i]를 가리킴

	int i;
	for( i = 0; i<3; i++)
		printf("%d %d %d\n", a[i][2-i], *a[i], *(*(a+i)+i));  // a의 대각선 요소, 첫 번째 열의 첫 번째 요소, 대각선에 위치한 요소를 출력
	putchar('\n');

	for( i = 0; i<3; i++)
		printf("%d %d\n", *pa[i], p[i]); // 포인터 배열 p, 포인터 p가 가리키는 배열 a 요소 출력
	putchar('\n');

	return 0;
}

