#include <stdio.h>

int main(void) {
    char c;
    int i, count = 0;
    for (i = 0; i < 26; i++) {
        c = 'A' + i;
        printf("%c%c ", c, c + 32);
	count ++;
    if ( count % 6 == 0)
    {
	    printf("\n");
    }
}
    printf("\n");
    return 0;
}



