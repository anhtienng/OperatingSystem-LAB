#include <stdio.h>
#include <stdlib.h>

void *aligned_malloc(unsigned int size, unsigned int align){
    void *p1 ,*p2;
    // Malloc
    p1 =(void *) malloc(size + align + sizeof(void*)) ;
    if (p1 == NULL || size == 0 )
        return NULL;
    // Memory alignment
    size_t addr = (size_t) p1 + align + sizeof(void*);
    p2 = (void *) (addr - (addr % align));
    // Store address returned by malloc right before p2
    *((size_t *) p2-1) = (size_t) p1;
    return p2;
}

void aligned_free(void *ptr){
    free((void *)(*((size_t *) ptr-1)));
}
 
