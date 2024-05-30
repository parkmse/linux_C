# include <stdio.h>

int main(void)
{
	int fahr, celsius;
	int lower, upper, step;

	lower = -15;
	upper = 40;
	step = 5;
	
	celsius = lower;
	while(celsius <= upper) {
		fahr = 9 * celsius / 5 + 32;
		printf("%d\t%d\n", celsius ,fahr);
		celsius += step;
	}

}	
