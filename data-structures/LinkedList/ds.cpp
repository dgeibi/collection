#include "ds.h"
#include <cstdlib>

LinkList MakeNode_L(ElemType e) {
    LinkList p;
    p=(LinkList) malloc(sizeof(LNode));
    if (p!=NULL) {
        p->data = e;
        p->next = NULL;
    }
    return p;
}

Status InsertAfter_L(LNode *p,LNode *q) {
    if (NULL == p || NULL == q) {
        return ERROR;
    }
    q->next = p->next;
    p->next = q;
    return OK;
}

/* 将 a 移动到 b 后面 */
Status MoveAfter_L(LinkList a, LinkList b) {
    if(b == NULL) return ERROR;
    LinkList cur = b->next;
    while (cur!=NULL) {
        if(cur->next == a) break;
        cur = cur->next;
    }
    if(cur == NULL) return ERROR;
    cur->next = a->next;
    a->next = b->next;
    b->next = a;
    return OK;
}

Status InitList_L (LinkList &L) {
    if (NULL == ( L = (LNode *)malloc(sizeof(LNode)))) {
        return ERROR;
    }
    L->next=NULL;
    return OK;
}

Status CreateList_L(LinkList &L, int n, ElemType *A) {
    LNode *p,*q;
    if(ERROR == InitList_L(L)) return ERROR;
    p = L;
    for (int i = 0; i < n; i++) {
        q = MakeNode_L(A[i]);
        InsertAfter_L(p,q);
        p = q;
    }
    return OK;
}

void ListTraverse_L(LinkList L, Status (*visit) (ElemType e)){
    LinkList c = L->next;
    while (c != NULL) {
        visit(c->data);
        c = c->next;
    }
}
