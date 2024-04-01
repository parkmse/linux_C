#include <stdio.h>

void shellsort(int v[], int n)
{
	int gap, i, j, temp;
	
	for( gap = n/2; gap > 0; gap /= 2) // gap을 배열 크기의 절반으로 설정, 1/2씩 줄어들면서 삽입 정렬 수행
		for(i= gap; i< n; i++) //각 gap별 삽입 정렬 수행
			for ( j = i-gap; j>=0 && v[j]>v[j+gap]; j-=gap) //gap 간격으로부터 양쪽에 있는 값 삽입 정렬 수행
			{
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp; // 두개의 수를 비교, 두 수 교환
			}
}

int main(void)
{
	int s[] = {12, 73, 4, 51, 22, 71, 2, 68, 100, 35};
	int i;
	int m = sizeof(s)/sizeof(int); // 배열 크기 계산.

	for(i = 0; i < m; i++)
		printf("%4d", s[i]); // 베열 내용 출력
	putchar('\n');

	shellsort(s,m); // shell정렬 수행
	for( i = 0 ; i < m; i++)
		printf("%4d", s[i]); // 정렬된 배열 내용 출력
	putchar('\n');

	return 0;
}

