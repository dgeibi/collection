#include "polish-notation.h"

void DestroyExpression(Expression& E) {
  if (E) {
    if (E->lchild) DestroyExpression(E->lchild);

    if (E->rchild) {
      DestroyExpression(E->rchild);
    }
    free(E);
  }
}

void MergeConst(Expression E) {
  // 合并表达式 E 中所有常数运算
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
      DestroyExpression(E->lchild);
      DestroyExpression(E->rchild);
      E->lchild = E->rchild = NULL;
    }
  }
}

bool isProper(Expression E) {
  // 判断表达式 E 是否适合插入新的结点
  // 表达式为空，适合
  // 类型为运算符，适合
  if (E == NULL) {
    return true;
  }

  if (E->type == OPERATOR) {
    return true;
  }
  return false;
}

Status PreOrderSearch(Expression& E,
                      bool (*test)(Expression), int type, char data, int value) {
  // 先序查找新结点的位置，根据 test 函数判断位置是否合理，如果合理则插入新结点，并返回 OK
  // 找不到适当的位置返回 ERROR
  if (E == NULL) {
    E = (ExprNode *)malloc(sizeof(ExprNode));

    if (E == NULL) {
      exit(OVERFLOW);
    }
    E->data   = data;
    E->type   = type;
    E->value  = value;
    E->lchild = NULL;
    E->rchild = NULL;
    return OK;
  }
  else if (test(E->lchild)) {
    if (OK == PreOrderSearch(E->lchild, test, type, data, value)) {
      return OK;
    }
    else if (test(E->rchild)) {
      return PreOrderSearch(E->rchild, test, type, data, value);
    }
  }
  else if (test(E->rchild)) {
    return PreOrderSearch(E->rchild, test, type, data, value);
  }
  return ERROR;
}

bool isOperator(char ch) {
  // 是运算符
  switch (ch) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
      return true;
  }
  return false;
}

bool isNumber(char ch) {
  // 是数字
  if ((ch >= '0') && (ch <= '9')) {
    return true;
  }
  return false;
}

bool isVariable(char ch) {
  // 是变量
  if ((ch >= 'a') && (ch <= 'z') || (ch >= 'A') && (ch <= 'Z')) {
    return true;
  }
  return false;
}

bool isAtom(char const *str) {
  // 判断是否为原子
  // 只含有运算符不是原子
  // 变量不是原子
  char ch;

  for (size_t i = 0; ch = str[i]; i++)
  {
    if (!(((i == 0) && isOperator(ch) && str[1]) || isNumber(ch))) {
      return false;
    }
  }
  return true;
}

Expression ReadExpr(char const *str) {
  // 由字符串构造表达式，如果语法有误，可能返回 NULL
  Expression E = NULL;
  char   ch;
  int    type, value = 0, flag = 0;

  for (size_t i = 0; ch = str[i]; i++) {
    if (isNumber(ch)) {
      value = value * 10 + (ch - '0');

      if (!isNumber(str[i + 1])) { // 下一个字符不是数字
        if (flag == 1) {
          value = -value;          // 是负的原子
        }

        if (PreOrderSearch(E, isProper, NUMBER, '\0', value) == ERROR) {
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
        else if (PreOrderSearch(E, isProper, OPERAT
OR, ch, 0) == ERROR) {
          return NULL;
        }
      }
      else if (isVariable(ch)) {
        if (PreOrderSearch(E, isProper, VARIABLE, ch, 0) == ERROR) {
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
  return E;
}

bool isHigher(Expression parent, Expression child) {
  // 判断父母结点的运算符的优先级是否比子结点的优先级高
  switch (parent->data) {
    case '^':

      if (child->type == OPERATOR) {
        return true;
      }
      break;

    case '/':

      switch (child->data) {
        case '*':
        case '-':
        case '+':
          return true;
          break;
      }
      break;

    case '*':

      switch (child->data) {
        case '/':
        case '-':
        case '+':
          return true;
          break;
      }
      break;
  }
  return false;
}

void InOrderWrite(Expression E) {
  // 用带括弧的中缀表示式输出表达式 E，添加括号
  if (E) {
    if (E->lchild) {
      if (isHigher(E, E->lchild)) {
        putchar('(');
        InOrderWrite(E->lchild);
        putchar(')');
      }
      else {
        InOrderWrite(E->lchild);
      }
    }

    switch (E->type) {
      case OPERATOR:
      case VARIABLE:
        putchar(E->data);
        break;

      case NUMBER:
        printf("%d", E->value);
        break;
    }

    if (E->rchild) {
      if (isHigher(E, E->rchild)) {
        putchar('(');
        InOrderWrite(E->rchild);
        putchar(')');
      }
      else {
        InOrderWrite(E->rchild);
      }
    }
  }
}

void WriteExpr(Expression E) {
  // 加换行符
  InOrderWrite(E);
  putchar('\n');
}

Expression CompoundExpr(char P, Expression E1, Expression E2) {
  // 构造一个新的复合表达式，(E1)P(E2)，(P E1 E1)
  if (!isOperator(P)) { // 不是运算符
    return NULL;
  }
  else {
    Expression E;
    E = (Expression)malloc(sizeof(ExprNode));

    if (E == NULL) {
      exit(OVERFLOW);
    }
    E->type   = OPERATOR;
    E->value  = 0;
    E->data   = P;
    E->lchild = E1;
    E->rchild = E2;
    return E;
  }
}

void Assign(Expression E,
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

int Value(Expression E) {
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
