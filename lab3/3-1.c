#include <stdio.h>

int main(void)
{
	int a,b,diff;

	printf("첫번째 정수: ");
	scanf("%d",&a);

	printf("두번째 정수: ");
	scanf("%d",&b);
	
	if(a>b){ // a가 b보다 큰 경우
		diff = a-b; //a-b의 값을 diff에 저장
		printf("%d와 %d의 차는 %d\n", a,b,diff);
	}
	else{ // 그 이외의 경우
		diff = b-a;
		printf("%d와 %d의 차는 %d\n",b,a,diff); // 큰 수에서 작은 수를 빼도록 설정
	}
	return 0;
}
