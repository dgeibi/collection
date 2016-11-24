#include "polish-notation.h"
#include "bitree.cpp"

void MergeConst(BiTree E) {
  if (E) {
    MergeConst(E->lchild);
    MergeConst(E->rchild);

    if ((E->type == OPERATOR) && E->lchild && (E->lchild->type == NUMBER) &&
        E->rchild && (E->rchild->type == NUMBER)) {
      switch (E->data) {
        case '+':
          E->value = E->lchild->value + E->rchild->value;
          break;

        case '-':
          E->value = E->lchild->value - E->rchild->value;
          break;

        case '/':
          E->value = E->lchild->value / E->rchild->value;
          break;

        case '*':
          E->value = E->lchild->value * E->rchild->value;
          break;

        case '^':
          E->value = pow(E->lchild->value, E->rchild->value);
          break;
      }
      E->type = NUMBER;
      E->data = '\0';
      DestroyBiTree(E->lchild);
      DestroyBiTree(E->rchild);
      E->lchild = E->rchild = NULL;
    }
  }
}

Status isProper(BiTree p) {
  // 判断树 p 是否适合插入新的结点
  // 树为空，适合
  // 类型为运算符，适合
  if (p == NULL) {
    return TRUE;
  }

  if (p->type == OPERATOR) {
    return TRUE;
  }
  return FALSE;
}

Status PreOrderSearch(BiTree& T,
                      Status (*test)(BiTree), int type, char data, int value) {
  // 先序查找新结点的位置，根据 test 函数判断位置是否合理，如果合理则插入新结点，并返回 OK
  // 找不到适当的位置返回 ERROR
  if (T == NULL) {
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
  }
  else if (test(T->lchild)) {
    if (OK == PreOrderSearch(T->lchild, test, type, data, value)) {
      return OK;
    }
    else if (test(T->rchild)) {
      return PreOrderSearch(T->rchild, test, type, data, value);
    }
  }
  else if (test(T->rchild)) {
    return PreOrderSearch(T->rchild, test, type, data, value);
  }
  return ERROR;
}

Status isOperator(char ch) {
  // 是运算符
  switch (ch) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
      return TRUE;
  }
  return FALSE;
}

Status isNumber(char ch) {
  // 是数字
  if ((ch >= '0') && (ch <= '9')) {
    return TRUE;
  }
  return FALSE;
}

Status isVariable(char ch) {
  // 是变量
  if ((ch >= 'a') && (ch <= 'z') || (ch >= 'A') && (ch <= 'Z')) {
    return TRUE;
  }
  return FALSE;
}

Status isAtom(char const *str) {
  // 判断是否为原子
  // 只含有运算符不是原子
  // 变量不是原子
  char ch;

  for (size_t i = 0; ch = str[i]; i++)
  {
    if (!(((i == 0) && isOperator(ch) && str[1]) || isNumber(ch))) {
      return FALSE;
    }
  }
  return TRUE;
}

BiTree ReadExpr(char const *str) {
  // 由字符串构造表达式，如果语法有误，可能返回 NULL
  BiTree T = NULL;
  char   ch;
  int    type, value = 0, flag = 0;

  for (size_t i = 0; ch = str[i]; i++) {
    if (isNumber(ch)) {
      value = value * 10 + (ch - '0');

      if (!isNumber(str[i + 1])) { // 下一个字符不是数字
        if (flag == 1) {
          value = -value;          // 是负的原子
        }

        if (PreOrderSearch(T, isProper, NUMBER, '\0', value) == ERROR) {
          return NULL;
        }
        value = 0; // 重置
      }
    }
    else {
      if (isOperator(ch)) {
        if ((i == 0) && isAtom(str)) {
          if (ch == '-') {
            flag = 1; // 是负的原子
          }
        }
        else if (PreOrderSearch(T, isProper, OPERATOR, ch, 0) == ERROR) {
          return NULL;
        }
      }
      else if (isVariable(ch)) {
        if (PreOrderSearch(T, isProper, VARIABLE, ch, 0) == ERROR) {
          return NULL;
        }
      }
      else if (ch == ' ') {
        continue;
      }
      else {
        return NULL;
      }
    }
  }
  return T;
}

Status isHigher(BiTree parent, BiTree child) {
  // 判断父母结点的运算符的优先级是否比子结点的优先级高
  switch (parent->data) {
    case '^':

      if (child->type == OPERATOR) {
        return TRUE;
      }
      break;

    case '/':

      switch (child->data) {
        case '*':
        case '-':
        case '+':
          return TRUE;
          break;
      }
      break;

    case '*':

      switch (child->data) {
        case '/':
        case '-':
        case '+':
          return TRUE;
          break;
      }
      break;
  }
  return FALSE;
}

void InOrderWrite(BiTree p) {
  // 用带括弧的中缀表示式输出表达式 E，添加括号
  if (p) {
    if (p->lchild) {
      if (isHigher(p, p->lchild)) {
        putchar('(');
        InOrderWrite(p->lchild);
        putchar(')');
      }
      else {
        InOrderWrite(p->lchild);
      }
    }

    switch (p->type) {
      case OPERATOR:
      case VARIABLE:
        putchar(p->data);
        break;

      case NUMBER:
        printf("%d", p->value);
        break;
    }

    if (p->rchild) {
      if (isHigher(p, p->rchild)) {
        putchar('(');
        InOrderWrite(p->rchild);
        putchar(')');
      }
      else {
        InOrderWrite(p->rchild);
      }
    }
  }
}

void WriteExpr(BiTree T) {
  // 加换行符
  InOrderWrite(T);
  putchar('\n');
}

BiTree CompoundExpr(char P, BiTree E1, BiTree E2) {
  // 构造一个新的复合表达式，(E1)P(E2)，(P E1 E1)
  if (!isOperator(P)) { // 不是运算符
    return NULL;
  }
  else {
    BiTree T;
    T = (BiTree)malloc(sizeof(BiTNode));

    if (T == NULL) {
      exit(OVERFLOW);
    }
    T->type   = OPERATOR;
    T->value  = 0;
    T->data   = P;
    T->lchild = E1;
    T->rchild = E2;
    return T;
  }
}

void Assign(BiTree E,
            char   V,
            int    num) {
  // 对变量 V 的赋值(V = c)
  if (E) {
    if ((E->type == VARIABLE) && (E->data == V)) {
      E->value = num;
    }
    Assign(E->lchild, V, num);
    Assign(E->rchild, V, num);
  }
}

int Value(BiTree E) {
  // 对算术表达式 E 求值
  if (E) {
    switch (E->type) {
      case VARIABLE:
      case NUMBER:
        return E->value;
        break;

      case OPERATOR:

        switch (E->data) {
          case '+':
            return Value(E->lchild) + Value(E->rchild);
            break;

          case '-':
            return Value(E->lchild) - Value(E->rchild);
            break;

          case '*':
            return Value(E->lchild) * Value(E->rchild);
            break;

          case '/':
            return Value(E->lchild) / Value(E->rchild);
            break;

          case '^':
            return pow(Value(E->lchild), Value(E->rchild));
            break;
        }
        break;
    }
  }
  return 0;
}
