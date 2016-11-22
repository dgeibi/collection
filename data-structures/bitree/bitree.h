#include "../vendor/miniunit.h"
#include <cstdlib>
#include <cstdio>

#ifdef BITREE_H
# define BITREE_H

typedef struct BiTNode {
  TElemType       data;
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void      PostOrderTraverse(BiTree T,
                            void (*Visit)(TElemType));
void      InOrderTraverse(BiTree T,
                          void (*Visit)(TElemType));
void      DestroyBiTree(BiTree& T);
Status    DeleteChild(BiTree& p,
                      int     LR);
Status    InsertChild(BiTree p,
                      int    LR,
                      BiTree c);
TElemType RightSibling(BiTree    T,
                       TElemType e);
TElemType LeftSibling(BiTree    T,
                      TElemType e);
TElemType RightChild(BiTree    T,
                     TElemType e);
TElemType LeftChild(BiTree    T,
                    TElemType e);
int       BiTreeDepth(BiTree T);
Status    BiTreeEmpty(BiTree T);
void      CreateBiTree(BiTree  & T,
                       TElemType ch);

# define ClearBiTree DestroyBiTree;

#endif // !BITREE_H
