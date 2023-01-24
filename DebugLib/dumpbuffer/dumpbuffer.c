#include <stdio.h>
#include <stdlib.h>

void dumpbuffer(const void * p, const int size){
    unsigned char uc;
    const unsigned char * ucp = (const unsigned char *)p;
    int i;
    for (i=0; i<size; i++){
        uc = *ucp++;
        printf("%02x ", uc);
    }
    printf("\n");
}
