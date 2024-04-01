#include <stdio.h>
#define NUM int
#define OUT printf
#define PI 3.14
#define SQ(X) ((X)*(X))

NUM main()
{
	NUM a,b,c;
	a = (NUM)PI; // PI값을 NUM인 int로 형변환
	b = 25;
	c = a + b;
	OUT("Result %d\n", SQ(c)); //정의된 OUT으로 출력
	return 0;
}
