#include <stdio.h>

int main()
{
	int asci, count = 0;

	for(asci = 33; asci<=126; asci ++)
	{
		if(asci < 100) // 100보다 작은 경우 decimal값 앞 한칸 띄고 출력
		{
			printf(" %d %X %c ", asci, asci, asci);
		}
		else // 그렇지 않은 경우 띄지 않고 출력
		{
			printf("%d %X %c ", asci, asci, asci);
		}
		count++; // count 변수를 이용해 문자가 출력될 때마다 count를 증가,
		if((count % 6) == 0){ // 6개의 문자가 출력될 때 마다
			printf("\n"); // 줄바꿈 출력
		}
				
	}
	printf("\n");
	return 0;
}
