#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31 , 30, 31},
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31 , 30, 31},
};

int day_of_year(int year, int month, int day)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0; // 윤년 판단
	for (i = 1; i < month; i++)
		day += daytab[leap][i]; // 몇번째 날인지 계산
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0; // 윤년 판단
	for (i = 1; yearday>daytab[leap][i]; i++)
		yearday -= daytab[leap][i]; // 월 일 계산
	*pmonth = i;
	*pday = yearday;
}

int main(void)
{
	printf("2022년 5월 5일은 %d번째 날\n", day_of_year(2022,5,5)); // 2022년 5월 5일
	printf("2014년 5월 5일은 %d번째 날\n", day_of_year(2014,5,5)); // 2014년 5월 5일

	int pmonth,pday;

	month_day(2022,200,&pmonth,&pday); // 2022년 200일째
	printf("2022년 200일째는 %d월 %d일\n", pmonth, pday);
	month_day(2000,300,&pmonth,&pday); // 2000년 300일째
	printf("2000년 300일째는 %d월 %d일\n", pmonth, pday);

	return 0;
}



