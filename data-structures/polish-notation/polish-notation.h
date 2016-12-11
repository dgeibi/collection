#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include "../vendor/miniunit.h"

#ifndef POLISHNOTATION_H
# define POLISHNOTATION_H

enum type {
  OPERATOR,
  CONST,
  VARIABLE
};

typedef struct ExprNode {
  int              type;  // 类型：OPERATOR/ CONST/ VARIABLE
  char             data;  // 字符数据：变量/运算符的字符
  int              value; // 值：变量/常量的值
  struct ExprNode *lchild, *rchild;
} ExprNode, *Expression;

// 释放表达式
void DestroyExpression(Expression& E);

// 判断是否为 type 类原子
bool IsAtom(int         type,
            char const *str);

// 判断 ch 是否是 type
bool Is(int  type,
        char ch);

// 判断父母结点的运算符的优先级是否比子结点的优先级高
bool IsHigher(Expression parent,
              Expression child);

// 判断表达式是否合理
bool       IsReasonable(Expression E);

// 将表达式重置为常量
void       ToConst(Expression E);

// 复制表达式
Expression Copy(Expression E);

// 先序查找新结点的位置，根据 IsReasonable 判断表达式是否可以插入/需要有递归
// 如果 E 为 NULL 则插入，并返回 true
// 未插入则返回 false
bool PreOrderFind(Expression& E,
                  int         type,
                  char        data,
                  int         value);

// 由字符串构造表达式，如果语法有误，返回 NULL
// 允许的字符：
//    运算符：+-*/^
//    常量：0-9
//    变量：a-zA-Z
//    分隔符：空格（可选）
Expression ReadExpr(char const *str);

// WriteExpr 的实现
void       WriteEx(Expression p);

// 用带括弧的中缀表示式输出表达式 E，添加括号
void       WriteExpr(Expression E);

// 对变量 V 的赋值(V = c)
// 变量的初值为 0 (实际使用字母表示)
void Assign(Expression E,
            char       V,
            int        num);

// 对算术表达式 E 求值
int        Value(Expression E);

// 构造一个新的复合表达式，(E1)P(E2)，(P E1 E1)
Expression CompoundExpr(char       P,
                        Expression E1,
                        Expression E2);

// 合并表达式 E 中所有常量运算。例如,
// 对表达式 E = (2 + 3 - a) * (b + 3 * 4)进行合并常量的操作后, 求得 E = (5 - a) * (b + 12)
void       MergeConst(Expression& E);

// 求偏导数（只支持幂函数）
Expression Diff(Expression e,
                char       V);


#endif // ifndef POLISHNOTATION_H
