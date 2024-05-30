#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *p, const void *q)
{
	return(strcmp((char **)p, (char **)q));
}

int main(void)
{
        char s[][10] = {"banana","apple","orange","carrot","tomato"};

        int num = sizeof(s) / sizeof(s[0]);
	printf("%d\n", num);
        int i;

        for (i = 0; i < num; i++)
                printf("%s ", a[i]);
        printf("\n");

        qsort(a, num, sizeof(char*), compare);

        for (i = 0; i < num; i++)
                printf("%s ", a[i]);
        printf("\n");

        char **found;
        char *key = "orange";
        if ((found =(char *)bsearch(&key, s, num, sizeof(s[0]), compare)) != NULL)
                printf("Found key is %s.\n", found);
        else
                printf("There is no %s in List.\n", key);

        int key = 5;
        if ((found =(char **) bsearch(&key, s, num, sizeof(s[0]), compare)) != NULL)
                printf("Found key is %s.\n.", found);
        else
                printf("There is no %d in List.\n", key);

        return 0;
}

