#include "polish-notation.h"
// 判断结点位置是否合理
Status isProper(BiTree p) {
  if (p == NULL) {
    return TRUE;
  }

  if (p->type == OPERATOR)
  {
    return TRUE;
  }
  return FALSE;
}

Status PreOrderSearch(BiTree& T, Status (*test)(BiTree), int type, TElemType data, int value) {
  if (T == NULL)
  {
    T = (BiTNode *)malloc(sizeof(BiTNode));

    if (T == NULL) {
      exit(OVERFLOW);
    }
    T->data   = data;
    T->type   = type;
    T->value  = value;
    T->lchild = NULL;
    T->rchild = NULL;
    return OK;
  } else if (test(T->lchild))
  {
    if (OK == PreOrderSearch(T->lchild, test, type, data, value))
    {
      return OK;
    } else if (test(T->rchild)) {
      return PreOrderSearch(T->rchild, test, type, data, value);
    }
  } else if (test(T->rchild)) {
    return PreOrderSearch(T->rchild, test, type, data, value);
  }
  return ERROR;
}

// 以字符序列的形式输入语法正确的前缀表示式并构造表达式
BiTree ReadExpr(char const *str) {
  BiTree T = NULL;

  char ch;
  int  type;
  int  value = 0;

  int flag = 1;

  for (size_t i = 0; ch = str[i]; i++) {
    if ((ch >= '0') && (ch <= '9'))
    {
      value = value * 10 + (ch - '0');
      flag  = 0;
    } else {
      // 提交数字
      if (flag == 0)
      {
        if (PreOrderSearch(T, isProper, NUMBER, '\0', value) == ERROR)
        {
          return NULL;
        }
        flag  = 1;
        value = 0;
      }

      if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^')) {
        if (PreOrderSearch(T, isProper, OPERATOR, ch, 0) == ERROR)
        {
          return NULL;
        }
      } else if ((ch <= 'Z') && (ch >= 'A') || (ch >= 'a') && (ch <= 'z'))   {
        if (PreOrderSearch(T, isProper, VARIABLE, ch, 0) == ERROR)
        {
          return NULL;
        }
      } else {
        return NULL;
      }
    }
  }
  return T;
}

void InOrderPrint(BiTree p) {
  if (p)
  {
    InOrderPrint(p->lchild);

    switch (p->type)
    {
    case OPERATOR:
    case VARIABLE:
      putchar(p->data);
      break;

    case NUMBER:
      printf("%d", p->value);
      break;
    }
    InOrderPrint(p->rchild);
  }
}
