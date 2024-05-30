#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
        int i;
        double sum = 0;
        double average = 0;

        for(i = 1; i < argc; i++)
                sum += atoi(argv[i]);

        average = sum / (argc-1);

        printf("sum: %lf\n", sum);
        printf("average: %lf\n", average);
        return 0;
}

