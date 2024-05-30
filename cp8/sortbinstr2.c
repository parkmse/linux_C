#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *p, const void *q)
{
    const char *i = *(const char **)p;
    const char *j = *(const char **)q;

    return strcmp(i, j);
}

int main(void)
{
    const char *a[] = {"banana", "apple", "orange", "carrot", "tomato"};

    int num = sizeof(a) / sizeof(char*);
    int i;

    for (i = 0; i < num; i++)
        printf("%s ", a[i]);
    printf("\n");

    qsort(a, num, sizeof(char*), compare);

    for (i = 0; i < num; i++)
        printf("%s ", a[i]);
    printf("\n");

    const char **found;
    const char *key = "orange";
    if ((found = bsearch(&key, a, num, sizeof(char*), compare)) != NULL)
        printf("Found key is %s.\n", *found);
    else
        printf("There is no %s in List.\n", key);

    key = "oop";
    if ((found = bsearch(&key, a, num, sizeof(char*), compare)) != NULL)
        printf("Found key is %s\n.", *found);
    else
        printf("There is no %s in List.\n", key);

    return 0;
}

