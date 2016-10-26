#define ERROR -1
#define OK 1
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

typedef int Status;
typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

LinkList MakeNode_L(ElemType e);
Status InsertAfter_L(LNode *p,LNode *q);
Status MoveAfter_L(LinkList a, LinkList b);
Status InitList_L (LinkList &L);
Status CreateList_L(LinkList &L, int n, ElemType *A);
void ListTraverse_L(LinkList L, Status (*visit) (ElemType e));
