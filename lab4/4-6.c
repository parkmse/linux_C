#include <stdio.h>

void qsort(double v[], int left, int right)
{
	int i, last;
	void swap(double v[], int i, int j);

	if (left >= right) // 정렬한 원소의 갯수가 1 이하면 종료
		return;
	swap(v, left, (left + right)/2); // 가운데 원소를 기준으로 분할
	last = left;
	for ( i = left + 1; i <= right; i++)
		if (v[i] < v[left])
			swap (v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last); // 분할된 두 부분 배열에 대한 qsort함수 호출
	qsort(v, last+1, right);

}

void swap(double v[], int i, int j) // 원소의 위치를 바꾸는 swap()함수 정의
{
	double temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#define ELEMENTS 10

int main(void) {
	double array[] = {1.1, 9.9, 2.2, 8.8, 3.3, 7.7, 4.4, 6.6, 5.5, 0.0};

	for ( int i = 0; i<ELEMENTS; i++) // 정렬 전
		printf("%5.1lf", array[i]);
	printf("\n");

	qsort(array, 0, 9); // qsort함수를 사용하여 배열 정렬
	
	for ( int i = 0; i<ELEMENTS; i++) // 정렬 후 
		printf("%5.1lf", array[i]);
	printf("\n");
	return 0;
}
