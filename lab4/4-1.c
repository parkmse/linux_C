#include <stdio.h>

int max(int i, int j, int k)
{
	int max_value = i;

	if (j>max_value)
	{
		max_value = j; //j가 max보다 크면 max값에 j 대입
	}
	if (k>max_value)
	{
		max_value = k; //k가 max보다 크면 max값에 k 대입
	}

	return max_value;
}

int min(int i, int j, int k)
{
	int min_value = i;

	if(j<min_value){
		min_value = j; // j가 min보다 작으면 min값에 j대입
	}
	if(k<min_value){
		min_value = k; // k가 min보다 작으면 min값에 k대입
	}

	return min_value;

}

int main(void)
{
	int i = 10;
	int j = 20;
	int k = -30;

	printf("Min value is %d\n", min(i,j,k));
	printf("Max value is %d\n", max(i,j,k));

	return 0;
}

