#include "funcs.h"
#include <stdio.h> 

int main() {
   GetInteger();

#ifdef _WIN32 
    printf("Hit any key + Enter to close. ");
    int c;
    scanf("%d", &c); 
#endif 
 
    return 0;
}
