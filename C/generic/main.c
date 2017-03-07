/* main.c */
// http://akaedu.github.io/book/ch24s05.html
#include <stdio.h>
#include <stdlib.h>
#include "generics.h"

typedef struct {
     const char *name;
     int score;
} student_t;

int cmp_student(void *a, void *b)
{
     if(((student_t *)a)->score > ((student_t *)b)->score)
	  return 1;
     else if(((student_t *)a)->score == ((student_t *)b)->score)
	  return 0;
     else
	  return -1;
}

int main(void)
{
     student_t list[] = {{"Tom", 68}, {"Jerry", 72},
		       {"Moby", 60}, {"Kirby", 89}, {"Paul",100}};
     int length = sizeof(list)/sizeof(student_t);
    //  replace student_t *plist[4] = {&list[0], &list[1], &list[2], &list[3]};
     student_t **plist =(student_t **) getPlist(list, length,sizeof(student_t));
     student_t *pmax = max((void **)plist, length, cmp_student);
     printf("%s gets the highest score %d\n", pmax->name, pmax->score);
     return 0;
}
