#include "bitree.h"

void CreateBiTree(BiTree& T, TElemType ch)
{
  T = (BiTree)malloc(sizeof(BiTNode));

  if (!T) exit(OVERFLOW);
  T->data = ch;
}

Status BiTreeEmpty(BiTree T)
{
  if (T) return FALSE;
  else return TRUE;
}

int BiTreeDepth(BiTree T)
{
  int i, j;

  if (T == NULL) return 0;

  if (T->lchild) i = BiTreeDepth(T->lchild);

  if (T->rchild) j = BiTreeDepth(T->rchild);
  return i > j ? i + 1 : j + 1;
}

TElemType LeftChild(BiTree T, TElemType e)
{
  BiTree a;

  if (T)
  {
    a = Point(T, e);

    if (a && a->lchild) return a->lchild->data;
  }
  return NULL;
}

TElemType RightChild(BiTree T, TElemType e)
{
  BiTree a;

  if (T)
  {
    a = Point(T, e);

    if (a && a->rchild) return a->rchild->data;
  }
  return NULL;
}

TElemType LeftSibling(BiTree T, TElemType e)
{
  TElemType a;
  BiTree    p;

  if (T)
  {
    a = Parent(T, e);

    if (a != NULL)
    {
      p = Point(T, a);

      if (p->lchild && p->rchild && (p->rchild->data == e)) return p->lchild->data;
    }
  }
  return NULL;
}

TElemType RightSibling(BiTree T, TElemType e)
{
  TElemType a;
  BiTree    p;

  if (T)
  {
    a = Parent(T, e);

    if (a != NULL)
    {
      p = Point(T, a);

      if (p->lchild && p->rchild && (p->lchild->data == e)) return p->rchild->data;
    }
  }
  return NULL;
}

Status InsertChild(BiTree p, int LR, BiTree c)
{
  if (p)
  {
    if (LR == 0)
    {
      c->rchild = p->lchild;
      p->lchild = c;
    }
    else
    {
      c->rchild = p->rchild;
      p->rchild = c;
    }
    return OK;
  }
  return ERROR;
}

Status DeleteChild(BiTree& p, int LR)
{
  if (p)
  {
    if (LR == 0) ClearBiTree(p->lchild);
    else ClearBiTree(p->rchild);
    return OK;
  }
  return ERROR;
}

void DestroyBiTree(BiTree& T) {
  if (T)
  {
    if (T->lchild) ClearBiTree(T->lchild);

    if (T->rchild)
    {
      ClearBiTree(T->rchild);
    }
    free(T);
  }
}

void InOrderTraverse(BiTree T, void (*Visit)(TElemType))
{
  if (T)
  {
    InOrderTraverse(T->lchild, Visit);
    Visit(T->data);
    InOrderTraverse(T->rchlid, Visit);
  }
}

void PostOrderTraverse(BiTree T, void (*Visit)(TElemType))
{
  if (T)
  {
    PostOrderTraverse(T->lchild, Visit);
    PostOrderTraverse(T->rchild, Visit);
    Visit(T->data);
  }
}
