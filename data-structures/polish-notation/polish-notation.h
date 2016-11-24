#include <cstdlib>
#include <cstdio>
#include "../vendor/miniunit.h"
#include <cmath>

#ifndef POLISHNOTATION_H
# define POLISHNOTATION_H

# define OPERATOR 0
# define NUMBER 1
# define VARIABLE 2

typedef char TElemType;

typedef struct BiTNode {
  int             type;  // 类型：OPERATOR/ NUMBER/ VARIABLE
  char            data;  // 字符数据：变量/运算符的字符
  int             value; // 值：运算符/数字的值
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void   PostOrderTraverse(BiTree T,
                         void (*Visit)(BiTree));
void   InOrderTraverse(BiTree T,
                       void (*Visit)(BiTree));
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

// 由字符串构造表达式，如果语法有误，可能返回 NULL
BiTree ReadExpr(char const *str);


// 判断树 p 是否适合插入新的结点
// 树为空，适合
// 类型为运算符，适合
Status isProper(BiTree p);

// 先序查找新结点的位置，根据 test 函数判断位置是否合理，如果合理则插入新结点，并返回 OK
// 找不到适当的位置返回 ERROR
Status PreOrderSearch(BiTree & T,
                      Status (*test)(BiTree),
                      int      type,
                      char     data,
                      int      value);

// 用带括弧的中缀表示式输出表达式 E，添加括号
void WriteExpr(BiTree E);

// WriteExpr 的实现
void InOrderWrite(BiTree p);

// 对变量 V 的赋值(V = c)
// 变量的初值为 0 (实际使用字母表示)
void Assign(BiTree E,
            char   V,
            int    num);

// 对算术表达式 E 求值
int    Value(BiTree E);

// 构造一个新的复合表达式，(E1)P(E2)，(P E1 E1)
BiTree CompoundExpr(char   P,
                    BiTree E1,
                    BiTree E2);

// 求表达式 E 对变量 V 的导数
BiTree Diff(BiTree E,
            char   V);

// 合并表达式 E 中所有常数运算。例如,
// 对表达式 E = (2 + 3 - a) * (b + 3 * 4)进行合并常数的操作后, 求得 E = (5 - a) * (b + 12)
void   MergeConst(BiTree E);

// 判断父母结点的运算符的优先级是否比子结点的优先级高
Status isHigher(BiTree parent,
                BiTree child);

// 判断是否为原子
// 只含有运算符不是原子
// 变量不是原子
Status isAtom(char const *str);

Status isVariable(char ch); // 是变量
Status isNumber(char ch);   // 是数字
Status isOperator(char ch); // 是运算符


#endif // ifndef POLISHNOTATION_H
