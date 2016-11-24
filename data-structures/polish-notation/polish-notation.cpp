#include "polish-notation.h"

bool isReasonable(Expression E) {
  // 判断表达式是否合理
  if (E) {
    if (E->type != OPERATOR) {
      return true;
    }
    else if (false == isReasonable(E->lchild)) {
      return false;
    }
    else return isReasonable(E->rchild);
  }
  return false;
}

Expression Diff(Expression e, char V) {
  Expression E;

  if (e->type == OPERATOR) {
    E = Copy(e);

    switch (E->data) {
      case '+':
      case '-':
        return CompoundExpr(E->data, Diff(E->lchild, V), Diff(E->rchild, V));
        break;

      case '*':
        return CompoundExpr('+',
                            CompoundExpr('*', Diff(E->lchild, V),
                                         E->rchild),
                            CompoundExpr('*', E->lchild,
                                         Diff(E->rchild, V)));
        break;

      case '/':
        return CompoundExpr('/', CompoundExpr('-',
                                              CompoundExpr('*',
                                                           Diff(E->lchild, V),
                                                           E->rchild),
                                              CompoundExpr('*', E->lchild,
                                                           Diff(
                                                             E->rchild, V))),
                            CompoundExpr('*', E->rchild,
                                         E->rchild));
        break;

      case '^':

        // 缺陷：不支持指数函数求偏导数
        return CompoundExpr('*', E, CompoundExpr('/', CompoundExpr('*',
                                                                   E->rchild,
                                                                   Diff(E->
                                                                        lchild,
                                                                        V)),
                                                 E->lchild));
        break;
    }
  }
  else if ((e->type == VARIABLE) && (e->data == V)) {
    // 指定的变量
    E         = (Expression)malloc(sizeof(ExprNode));
    E->type   = NUMBER;
    E->value  = 1;
    E->data   = '\0';
    E->lchild = E->rchild = NULL;
    return E;
  }

  // 其它变量或者常数项
  E         = (Expression)malloc(sizeof(ExprNode));
  E->type   = NUMBER;
  E->value  = 0;
  E->data   = '\0';
  E->lchild = E->rchild = NULL;
  return E;
}

// 复制表达式
Expression Copy(Expression E) {
  Expression p;

  if (E) {
    p = (Expression)malloc(sizeof(ExprNode));

    if (p == NULL) {
      exit(OVERFLOW);
    }
    p->type   = E->type;
    p->data   = E->data;
    p->value  = E->value;
    p->lchild = Copy(E->lchild);
    p->rchild = Copy(E->rchild);
    return p;
  }
  return NULL;
}

void DestroyExpression(Expression& E) {
  if (E) {
    if (E->lchild) DestroyExpression(E->lchild);

    if (E->rchild) {
      DestroyExpression(E->rchild);
    }
    free(E);
  }
}

void MergeConst(Expression& E) {
  // 合并表达式 E 中所有常数运算
  if (E != NULL) {
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
    else if (((E->data == '*') &&
              (((E->lchild->type == NUMBER) && (E->lchild->value == 0)) ||
               ((E->rchild->type == NUMBER) && (E->rchild->value == 0)))) ||
             (((E->data == '/') || (E->data == '^')) &&
              (E->lchild->type == NUMBER) &&
              (E->lchild->value == 0))) {
      E->data  = '\0';
      E->type  = NUMBER;
      E->value = 0;
      DestroyExpression(E->lchild);
      DestroyExpression(E->rchild);
      E->lchild = E->rchild = NULL;
    }
    else if ((E->data == '^') && (E->rchild->type == NUMBER) &&
             (E->rchild->value == 0)) {
      E->data  = '\0';
      E->type  = NUMBER;
      E->value = 1;
      DestroyExpression(E->lchild);
      DestroyExpression(E->rchild);
      E->lchild = E->rchild = NULL;
    }
    else if (E->data == '+') {
      if ((E->lchild->type == NUMBER) && (E->lchild->value == 0)) {
        DestroyExpression(E->lchild);
        E = E->rchild;
      }
      else if ((E->rchild->type == NUMBER) && (E->rchild->value == 0)) {
        DestroyExpression(E->rchild);
        E = E->lchild;
      }
    }
    else if (E->data == '-') {
      if ((E->rchild->type == NUMBER) && (E->rchild->value == 0)) {
        DestroyExpression(E->rchild);
        E = E->lchild;
      }
    }
    else if (E->data == '*') {
      if ((E->lchild->type == NUMBER) && (E->lchild->value == 1)) {
        DestroyExpression(E->lchild);
        E = E->rchild;
      }
      else if ((E->rchild->type == NUMBER) && (E->rchild->value == 1)) {
        DestroyExpression(E->rchild);
        E = E->lchild;
      }
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
                      bool (*test)(Expression), int type, char data,
                      int value) {
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
  else if (test(E)) {
    if (test(E->lchild)) {
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
  if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))) {
    return true;
  }
  return false;
}

bool isAtom(char const *str) {
  // 判断是否为原子
  // 只含有运算符不是原子
  // 变量不是原子
  size_t length = strlen(str);

  for (size_t i = 0; i < length; i++)
  {
    if (!isNumber(str[i]) && !isOperator(str[i]) && !isVariable(str[i]) &&
        (str[i] != ' ')) {
      continue;
    }

    if (!(((i == 0) && isOperator(str[i]) && str[1]) || isNumber(str[i]))) {
      return false;
    }
  }
  return true;
}

Expression ReadExpr(char const *str) {
  // 由字符串构造表达式，如果语法有误，可能返回 NULL
  Expression E = NULL;
  int        value = 0;
  size_t     length = strlen(str);
  bool       BAD = false, MINUS = false;

  for (size_t i = 0; i < length; i++) {
    if (isNumber(str[i])) {
      value = value * 10 + (str[i] - '0');

      if (!isNumber(str[i + 1])) { // 下一个字符不是数字
        if (MINUS) {
          value = -value;          // 是负的原子
        }

        if (PreOrderSearch(E, isProper, NUMBER, '\0', value) == ERROR) {
          BAD = true;
          break;
        }
        value = 0; // 重置
      }
    }
    else {
      if (isOperator(str[i])) {
        if ((i == 0) && isAtom(str)) {
          if (str[i] == '-') {
            MINUS = true; // 是负的原子
          }
        }
        else if (PreOrderSearch(E, isProper, OPERATOR, str[i], 0) == ERROR) {
          BAD = true;
          break;
        }
      }
      else if (isVariable(str[i])) {
        if (PreOrderSearch(E, isProper, VARIABLE, str[i], 0) == ERROR) {
          BAD = true;
          break;
        }
      }
      else {
        continue;
      }
    } // endelse
  }   // endfor

  if (BAD) {
    DestroyExpression(E);
    return NULL;
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
  if (isReasonable(E)) {
    InOrderWrite(E);
    putchar('\n');
  }
  else {
    printf("%s\n", "无效的表达式");
  }
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
    E->lchild = Copy(E1);
    E->rchild = Copy(E2);
    return E;
  }
}

void Assign(Expression E,
            char       V,
            int        num) {
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
  if (isReasonable(E)) {
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
