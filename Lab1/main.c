#include "add.h"
#include <stdio.h>

int main(void)
{
	int a = 5;
	int b = 4;
	
	printf("%d + %d = %d\n", a, b, add(a, b));
    return 0;
}
