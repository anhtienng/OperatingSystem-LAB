#include <stdio.h>
#include "ex1.h"

int main()
{
    unsigned int align;
    printf("Align: ");
    scanf("%u", &align);
    char* a = (char*)aligned_malloc(50,align);
    printf("Address: %p\n",a);
    aligned_free(a);
    return 0;
}
