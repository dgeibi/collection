#include "../vendor/miniunit.h"
#include <cstdlib>
#include <cstdio>

#ifndef LINKEDLIST_H
# define LINKEDLIST_H

typedef struct LNode {
  ElemType      data;
  struct LNode *next;
} LNode, *LinkList;

LinkList MakeNode_L(ElemType e);

Status   InsertAfter_L(LNode *p,
                       LNode *q);

Status   MoveAfter_L(LinkList a,
                     LinkList b);

Status   InitList_L(LinkList& L);

Status   CreateList_L(LinkList& L,
                      int       n,
                      ElemType *A);

void ListTraverse_L(LinkList L,
                    Status (*visit)(ElemType e));
#endif /* ifndef LINKEDLIST_H */
