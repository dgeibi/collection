#include <cstdlib>
#include <cstdio>
#include "../vendor/miniunit.h"

#ifndef POLISHNOTATION_H
# define POLISHNOTATION_H

# define OPERATOR 0
# define NUMBER 1
# define VARIABLE 2

typedef char TElemType;

typedef struct BiTNode {
  int             type;
  char            data;
  int             value;
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void   PostOrderTraverse(BiTree T,
                         void (*Visit)(TElemType));
void   InOrderTraverse(BiTree T,
                       void (*Visit)(TElemType));
void   DestroyBiTree(BiTree& T);
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
Status    BiTreeEmpty(BiTree T);
void      CreateBiTree(BiTree  & T,
                       TElemType ch);

# define ClearBiTree DestroyBiTree;

// 判断前缀表示式的语法是否合理
Status isSyntaxReasonable(BiTree E);

// 以字符序列的形式输入语法正确的前缀表示式并构造表达式
BiTree ReadExpr(char const *str);

// 判断结点位置是否合理
Status isProper(BiTree p);

Status PreOrderSearch(BiTree  & T,
                      Status ( *test)(BiTree),
                      int       type,
                      TElemType data,
                      int       value);

// 用带括弧的中缀表示式输出表达式 E，适当添加括号
void WriteExpr(BiTree E);

// 对变量 V 的赋值(V = c)
// 变量的初值为 0 (实际使用字母表示)
Status Assign(BiTree E,
              char   V,
              char   c);

// 对算术表达式 E 求值
double Value(BiTree E);

// 构造一个新的复合表达式，(E1)P(E2)，(P E1 E1)
BiTree CompoundExpr(char   P,
                    BiTree E1,
                    BiTree E2);

// 求表达式 E 对变量 V 的导数
BiTree Diff(BiTree E,
            char   V);

// 合并表达式 E 中所有常数运算。例如,
// 对表达式 E = (2 + 3 - a) * (b + 3 * 4)进行合并常数的操作后, 求得 E = (5 - a) * (b + 12)
BiTree MergeConst(BiTree E);

void   InOrderPrint(BiTree p);

#endif // ifndef POLISHNOTATION_H
