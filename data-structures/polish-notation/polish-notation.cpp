#include "polish-notation.h"
#include "../bitree/bitree.h"
#include "../bitree/bitree.cpp"

// 判断结点位置是否合理
int isProper(BiTree p) {
  switch (p->ch) {
  case '+':
  case '-':
  case '*':
  case '/':
  case '^':

    if (p->lchild == NULL) {
      return 1; // 左子树为空
    } else if (p->rchlid == NULL) {
      return 2; // 右子树为空
    } else {
      return 0; // 左右子树不为空
    }
    break;

  default:
    return 0; // 不符合条件
  }
}

Status PreOrderSearch(BiTree T, Status (*test)(BiTree), TElemType ch) {
  BiTree p;

  if (T == NULL)
  {
    return ERROR;
  }
  int state = test(T);

  if (state > 0)
  {
    p = (BiTree)malloc(sizeof(BiTNode));

    if (p == NULL) {
      exit(OVERFLOW);
    }
    p->data   = ch;
    p->lchild = NULL;
    p->rchild = NULL;

    if (state == 1) T->lchild = p; else T->rchild = p;
    return OK;
  } else if (OK  == PreOrderSearch(T->lchild, test, ch)) return OK;
  else return PreOrderSearch(T->lchild, test, ch);
}

// 以字符序列的形式输入语法正确的前缀表示式并构造表达式
BiTree ReadExpr(char *str) {
  BiTree T, p;

  CreateBiTree(T, str[0]);
  char ch;

  for (size_t i = 1; ch = str[i]; i++) {
    if ((ch <= 'Z') && (ch >= 'A') || (ch >= 'a') && (ch <= 'z') || (ch >= '0') &&
        (ch <= '9') || (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') ||
        (ch == '^')) {
      if (ERROR == PreOrderSearch(T, isProper, ch)) {
        return NULL;
      }
    } else {
      return NULL;
    }
  }
}
