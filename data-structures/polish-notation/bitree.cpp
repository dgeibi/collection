#include "../vendor/miniunit.h"

Status DeleteChild(BiTree& p,
                   int     LR);
Status InsertChild(BiTree p,
                   int    LR,
                   BiTree c);

TElemType RightChild(BiTree    T,
                     TElemType e);
TElemType LeftChild(BiTree    T,
                    TElemType e);
int       BiTreeDepth(BiTree T);
bool      BiTreeEmpty(BiTree T);
void      CreateBiTree(BiTree  & T,
                       TElemType ch);

#define ClearBiTree DestroyBiTree;

void CreateBiTree(BiTree& T, TElemType ch) {
  T = (BiTree)malloc(sizeof(BiTNode));

  if (!T) exit(OVERFLOW);
  T->data = ch;
}

bool BiTreeEmpty(BiTree T) {
  if (T) return false;
  else return true;
}

int BiTreeDepth(BiTree T) {
  int i, j;

  if (T == NULL) return 0;

  if (T->lchild) i = BiTreeDepth(T->lchild);

  if (T->rchild) j = BiTreeDepth(T->rchild);
  return i > j ? i + 1 : j + 1;
}

Status InsertChild(BiTree p, int LR, BiTree c) {
  if (p) {
    if (LR == 0) {
      c->rchild = p->lchild;
      p->lchild = c;
    }
    else {
      c->rchild = p->rchild;
      p->rchild = c;
    }
    return OK;
  }
  return ERROR;
}

Status DeleteChild(BiTree p, int LR) {
  if (p) {
    if (LR == 0) {
      ClearBiTree(p->lchild);
    }
    else {
      ClearBiTree(p->rchild);
    }
    return OK;
  }
  else return ERROR;
}
