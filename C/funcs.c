#include <stdio.h>
#include "funcs.h"

void GetInteger()
{
    int a;
    printf("Please input an integer value: ");
    scanf("%d", &a);
    printf("You entered: %d\n", a);
    return;
}