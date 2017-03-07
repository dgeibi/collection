/* generics.h */

#ifndef GENERICS_H
#define GENERICS_H
#include <stddef.h>

typedef int (*cmp_t)(void *, void *);
extern void *max(void *data[], int num, cmp_t cmp);
extern void **getPlist(void * head, int num, size_t size);

#endif
