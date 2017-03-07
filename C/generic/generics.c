/* generics.c */
#include "generics.h"
#include <stdlib.h>

void *max(void *data[], int num, cmp_t cmp)
{
     int i;
     void *temp = data[0];
     for(i=1; i<num; i++) {
	  if(cmp(temp, data[i])<0)
	       temp = data[i];
     }
     return temp;
}

void** getPlist(void * head, int num, size_t size) {
    void** plist = malloc(num*size);
    for(int i=0;i<num; i+=1) {
        plist[i] = head+i*(size);
    }
    return plist;
}
