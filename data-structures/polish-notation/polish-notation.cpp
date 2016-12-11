#include "polish-notation.h"

void ToConst(Expression E) { // 转化为常量
  if (E) {
    E->type = CONST;
    E->data = 0;
    DestroyExpr(E->lchild);
    DestroyExpr(E->rchild);
    E->lchild = E->rchild = NULL;
  }
}

bool IsReasonable(Expression E) {
  // 判断表达式是否合理
  if (E) {
    if (E->type != OPERATOR) {
      return true;
    } // 运算符需判断子式
    else if (false == IsReasonable(E->lchild)) {// 左子式不合理
      return false;
    }
    else return IsReasonable(E->rchild);
  }
  return false; // E==NULL，不合理
}

Expression Diff(Expression E, char V) {
  if (E == NULL) return NULL;

  if (E->type == OPERATOR) { // 依照求导公式实现
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

  // 变量V，其它原子的对V的偏导数分别为1，0
  Expression nE = (Expression)malloc(sizeof(ExprNode));
  nE->type   = CONST;
  nE->data   = '\0';
  nE->lchild = nE->rchild = NULL;
  nE->value  = ((E->type == VARIABLE) && (E->data == V)) ? 1 : 0;
  return nE;
}

// 复制表达式
Expression Copy(Expression E) {
  Expression p;

  if (E) {
    p = (Expression)malloc(sizeof(ExprNode));

    if (p == NULL) {
      exit(_OVERFLOW_);
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

void DestroyExpr(Expression& E) {
  if (E) {
    if (E->lchild) DestroyExpr(E->lchild);

    if (E->rchild) {
      DestroyExpr(E->rchild);
    }
    free(E);
  }
}

void MergeConst(Expression& E) {
  // 合并表达式 E 中所有常量运算
  if (E) {
    MergeConst(E->lchild);
    MergeConst(E->rchild);

    if ((E->type == OPERATOR) && E->lchild && (E->lchild->type == CONST) &&
        E->rchild && (E->rchild->type == CONST)) {
      // （OPERATOR CONST CONST)
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
      ToConst(E);
    }
    else if (((E->data == '*') &&
              (((E->lchild->type == CONST) && (E->lchild->value == 0)) ||
               ((E->rchild->type == CONST) && (E->rchild->value == 0)))) || // * x 0 = 0
                                                                            // * 0 x = 0
             (((E->data == '/') || (E->data == '^')) &&
              (E->lchild->type == CONST) &&
              (E->lchild->value == 0))) {                                   // / 0 x = 0
                                                                            // ^ 0 x = 0
      E->value = 0;
      ToConst(E);
    }
    else if ((E->data == '^') && (E->rchild->type == CONST) &&
             (E->rchild->value == 0)) { // ^ x 0 == 1
      E->value = 1;
      ToConst(E);
    }
    else if (E->data == '+') {
      if ((E->lchild->type == CONST) && (E->lchild->value == 0)) {
        DestroyExpr(E->lchild); // + 0 x = x
        E = E->rchild;
      }
      else if ((E->rchild->type == CONST) && (E->rchild->value == 0)) {
        DestroyExpr(E->rchild); // + x 0 = x
        E = E->lchild;
      }
    }
    else if (E->data == '-') {
      if ((E->rchild->type == CONST) && (E->rchild->value == 0)) {
        DestroyExpr(E->rchild); // - x 0 = x
        E = E->lchild;
      }
    }
    else if (E->data == '*') {
      if ((E->lchild->type == CONST) && (E->lchild->value == 1)) {
        DestroyExpr(E->lchild); // * 1 x = x
        E = E->rchild;
      }
      else if ((E->rchild->type == CONST) && (E->rchild->value == 1)) {
        DestroyExpr(E->rchild); // * x 1 = x
        E = E->lchild;
      }
    }
  }
}

bool PreOrderFind(Expression& E, int type, char data, int value) {
  // 先序查找新结点的位置，根据 IsReasonable 判断表达式是否可以插入/需要有递归
  // 如果 E 为 NULL 则插入，并返回 true
  // 未插入则返回 false

  if (!IsReasonable(E)) {
    if (E == NULL) {
      E = (ExprNode *)malloc(sizeof(ExprNode));

      if (E == NULL) {
        exit(_OVERFLOW_);
      }
      E->data   = data;
      E->type   = type;
      E->value  = value;
      E->lchild = NULL;
      E->rchild = NULL;
      return true;
    }
    else if (!IsReasonable(E->lchild) &&
             PreOrderFind(E->lchild, type, data, value)) {
      return true; // 左式未满并且插入成功
    }
    else if (!IsReasonable(E->rchild)) {
      return PreOrderFind(E->rchild, type, data, value);
    }
  }
  return false; // 表达式已经满了，返回 false
}

bool Is(int type, char ch) {
  // 判断 ch 是否是 type
  switch (type) {
    case CONST:

      if ((ch >= '0') && (ch <= '9')) return true;
      break;

    case VARIABLE:

      if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'))) return true;
      break;

    case OPERATOR:

      switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
          return true;
      }
      break;
  }
  return false;
}

bool IsAtom(int type, char const *str) {
  // 判断是否为 type 类原子
  size_t length = strlen(str);

  if (type == CONST) {
    for (size_t i = 0; i < length; i++)
    {
      if ((i == 0) && ((str[0] == '+') || (str[0] == '-')) && str[1]) {
        continue; // str[0] 可以为 + -，但必须存在下一位
      }

      if (Is(type, str[i])) {
        continue;
      }
      return false;
    }
    return true;
  }
  else if (type == VARIABLE) {
    if (length == 1) {      // 无符号变量原子
      return Is(type, str[0]);
    }
    else if (length == 2) { // 有符号变量原子
      return (str[0] == '+' || str[0] == '-') && Is(type, str[1]);
    }
  }

  return false;
}

Expression ReadExpr(char const *str) {
  // 由字符串构造表达式，如果语法有误，返回 NULL
  // 允许的字符：
  //    运算符：+-*/^
  //    常量：0-9
  //    变量：a-zA-Z
  //    分隔符：空格（可选）
  Expression E = NULL;
  int        value = 0;
  size_t     length = strlen(str);
  bool       BAD = false, MINUS = false;

  for (size_t i = 0; i < length; i++) {                 // 依次读取每一个字符
    if (Is(CONST, str[i])) {                            // 常量
      value = value * 10 + (str[i] - '0');              // 进位，转换为int

      if (!Is(CONST, str[i + 1])) {                     // 下一个字符不是常量
        if (MINUS) {                                    // 是负的常量原子
          value = -value;                               // 将值设为相反数
        }

        if (!PreOrderFind(E, CONST, '\0', value)) {     // 插入常量结点到 E
          BAD = true;                                   // 插入失败
        }// 表达式已经满了
        value = 0;                                      // 重置
      }
    }
    else if (Is(OPERATOR, str[i])) {                    // 运算符
      if ((i == 0) && IsAtom(CONST, str)) {
        if (str[i] == '-') {
          MINUS = true;                                 // 是负的常量原子
        }
      }
      else if (!PreOrderFind(E, OPERATOR, str[i], 0)) { // 插入运算符结点到 E
        BAD = true;
      }
    }
    else if (Is(VARIABLE, str[i])) {            // 变量
      if ((i == 1) && IsAtom(VARIABLE, str)) {  // 有符号变量原子
        if (!PreOrderFind(E, CONST, '\0', 0)) { // 前面补一个零
          BAD = true;
          break;
        }
      }

      if (!PreOrderFind(E, VARIABLE, str[i], 0)) { // 插入变量结点到 E
        BAD = true;
      }
    }
    else if (str[i] == ' ') { // 空格，可选分隔符，忽略
      continue;
    }
    else {                    // 其它字符非法
      BAD = true;
    }

    if (BAD) break;
  } // endfor

  if (BAD || !IsReasonable(E)) {
    DestroyExpr(E);
    printf("%s\n", "illegal expression");
    return NULL;
  }
  return E;
}

bool IsHigher(Expression parent, Expression child) {
  // 判断父式的运算符的优先级是否比子式的优先级高
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

void WriteEx(Expression E) {
  // 用带括弧的中缀表示式输出表达式 E，添加括号
  if (E) {
    if (E->lchild) {
      if (IsHigher(E, E->lchild)) { // 父式比子式的优先级高
        putchar('(');               // 加括号
        WriteEx(E->lchild);
        putchar(')');
      }
      else {
        WriteEx(E->lchild);
      }
    }

    switch (E->type) {
      case OPERATOR:
      case VARIABLE:
        putchar(E->data);
        break;

      case CONST:
        printf("%d", E->value);
        break;
    }

    if (E->rchild) {
      if (IsHigher(E, E->rchild)) {
        putchar('(');
        WriteEx(E->rchild);
        putchar(')');
      }
      else {
        WriteEx(E->rchild);
      }
    }
  }
}

void WriteExpr(Expression E) {
  // 加换行符
  if (E) {
    WriteEx(E);
    putchar('\n');
  }
}

Expression CompoundExpr(char P, Expression E1, Expression E2) {
  // 构造一个新的复合表达式，(E1)P(E2)，(P E1 E1)
  if (!Is(OPERATOR, P)) { // 不是运算符
    return NULL;
  }
  else {
    Expression E;
    E = (Expression)malloc(sizeof(ExprNode));

    if (E == NULL) {
      exit(_OVERFLOW_);
    }
    E->type   = OPERATOR;
    E->value  = 0;
    E->data   = P;
    E->lchild = Copy(E1); // 存副本
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
  if (E) {
    switch (E->type) {
      case VARIABLE:
      case CONST:
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
