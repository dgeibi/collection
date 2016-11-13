#include "ll.h"

Status func(LinkList L) {
  LinkList p = L->next;

  if (p == NULL) return ERROR;

  LinkList c = p->next, tmp;

  while (c != NULL) {
    tmp = c->next;

    if (c->data < p->data) {
      MoveAfter_L(c, L);
    }
    c = tmp;
  }
  return OK;
}

Status printit(ElemType e) {
  printf("%d ", e);
}

int main(int argc, char const *argv[]) {
  LinkList L;
  ElemType elem[10] = { 45, 4, 5, 67, 33, 22, 33, 22, 455, 33 };

  CreateList_L(L, 10, elem);
  ListTraverse_L(L, printit);
  func(L);
  putchar('\n');
  ListTraverse_L(L, printit);
  return 0;
}
