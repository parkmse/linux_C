#include <stdio.h>

int main(void)
{
	struct node {
		int len;
		char* str;
	};

	struct node a[] = {5, "hello", 10, "world"};
       // 첫번째 구조체: len->5 & str은 hello를 가리킴.
       // 두번째 구조체: len->10 & str은 world를 가리킴.
	struct node *p = a;

	printf("a[0].len is %d\n", a[0].len);
	printf("p->len is %d\n", p->len);
	printf("p->str is %s\n", p->str);
	printf("*p++->str is %c\n", *p++->str);
	printf("p->len is %d\n", p->len);
	printf("p->str is %s\n", p->str);

	return 0;
}

