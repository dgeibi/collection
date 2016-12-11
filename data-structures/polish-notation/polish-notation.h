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
  int              type;  // ���ͣ�OPERATOR/ CONST/ VARIABLE
  char             data;  // �ַ����ݣ�����/��������ַ�
  int              value; // ֵ������/������ֵ
  struct ExprNode *lchild, *rchild;
} ExprNode, *Expression;

// �ͷű��ʽ
void DestroyExpression(Expression& E);

// �ж��Ƿ�Ϊ type ��ԭ��
bool IsAtom(int         type,
            char const *str);

// �ж� ch �Ƿ��� type
bool Is(int  type,
        char ch);

// �жϸ�ĸ��������������ȼ��Ƿ���ӽ������ȼ���
bool IsHigher(Expression parent,
              Expression child);

// �жϱ��ʽ�Ƿ����
bool       IsReasonable(Expression E);

// �����ʽ����Ϊ����
void       ToConst(Expression E);

// ���Ʊ��ʽ
Expression Copy(Expression E);

// ��������½���λ�ã����� IsReasonable �жϱ��ʽ�Ƿ���Բ���/��Ҫ�еݹ�
// ��� E Ϊ NULL ����룬������ true
// δ�����򷵻� false
bool PreOrderFind(Expression& E,
                  int         type,
                  char        data,
                  int         value);

// ���ַ���������ʽ������﷨���󣬷��� NULL
// ������ַ���
//    �������+-*/^
//    ������0-9
//    ������a-zA-Z
//    �ָ������ո񣨿�ѡ��
Expression ReadExpr(char const *str);

// WriteExpr ��ʵ��
void       WriteEx(Expression p);

// �ô���������׺��ʾʽ������ʽ E���������
void       WriteExpr(Expression E);

// �Ա��� V �ĸ�ֵ(V = c)
// �����ĳ�ֵΪ 0 (ʵ��ʹ����ĸ��ʾ)
void Assign(Expression E,
            char       V,
            int        num);

// ���������ʽ E ��ֵ
int        Value(Expression E);

// ����һ���µĸ��ϱ��ʽ��(E1)P(E2)��(P E1 E1)
Expression CompoundExpr(char       P,
                        Expression E1,
                        Expression E2);

// �ϲ����ʽ E �����г������㡣����,
// �Ա��ʽ E = (2 + 3 - a) * (b + 3 * 4)���кϲ������Ĳ�����, ��� E = (5 - a) * (b + 12)
void       MergeConst(Expression& E);

// ��ƫ������ֻ֧���ݺ�����
Expression Diff(Expression e,
                char       V);


#endif // ifndef POLISHNOTATION_H
