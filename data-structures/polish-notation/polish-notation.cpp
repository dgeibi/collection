#include "polish-notation.h"

void ToConst(Expression E) {
  if (E) {
    E->type = CONST;
    E->data = '\0';
    DestroyExpression(E->lchild);
    DestroyExpression(E->rchild);
    E->lchild = E->rchild = NULL;
  }
}

bool IsReasonable(Expression E) {
  // �жϱ��ʽ�Ƿ����
  if (E) {
    if (E->type != OPERATOR) {
      return true;
    }
    else if (false == IsReasonable(E->lchild)) {
      return false;
    }
    else return IsReasonable(E->rchild);
  }
  return false;
}

Expression Diff(Expression E, char V) {
  if (E == NULL) return NULL;

  if (E->type == OPERATOR) {
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

        // ȱ�ݣ���֧��ָ��������ƫ����
        return CompoundExpr('*', E, CompoundExpr('/', CompoundExpr('*',
                                                                   E->rchild,
                                                                   Diff(E->
                                                                        lchild,
                                                                        V)),
                                                 E->lchild));
        break;
    }
  }
  Expression nE = (Expression)malloc(sizeof(ExprNode));
  nE->type   = CONST;
  nE->data   = '\0';
  nE->lchild = nE->rchild = NULL;
  nE->value  = ((E->type == VARIABLE) && (E->data == V)) ? 1 : 0;
  return nE;
}

// ���Ʊ��ʽ
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
  // �ϲ����ʽ E �����г�������
  if (E) {
    MergeConst(E->lchild);
    MergeConst(E->rchild);

    if ((E->type == OPERATOR) && E->lchild && (E->lchild->type == CONST) &&
        E->rchild && (E->rchild->type == CONST)) {
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
        DestroyExpression(E->lchild); // + 0 x = x
        E = E->rchild;
      }
      else if ((E->rchild->type == CONST) && (E->rchild->value == 0)) {
        DestroyExpression(E->rchild); // + x 0 = x
        E = E->lchild;
      }
    }
    else if (E->data == '-') {
      if ((E->rchild->type == CONST) && (E->rchild->value == 0)) {
        DestroyExpression(E->rchild); // - x 0 = x
        E = E->lchild;
      }
    }
    else if (E->data == '*') {
      if ((E->lchild->type == CONST) && (E->lchild->value == 1)) {
        DestroyExpression(E->lchild); // * 1 x = x
        E = E->rchild;
      }
      else if ((E->rchild->type == CONST) && (E->rchild->value == 1)) {
        DestroyExpression(E->rchild); // * x 1 = x
        E = E->lchild;
      }
    }
  }
}

bool PreOrderFind(Expression& E, int type, char data, int value) {
  // ��������½���λ�ã����� IsReasonable �жϱ��ʽ�Ƿ���Բ���/��Ҫ�еݹ�
  // ��� E Ϊ NULL ����룬������ true
  // δ�����򷵻� false

  if (!IsReasonable(E)) {
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
      return true;
    }
    else if (!IsReasonable(E->lchild) &&
             PreOrderFind(E->lchild, type, data, value)) {
      return true; // ��ʽδ�����Ҳ���ɹ�
    }
    else if (!IsReasonable(E->rchild)) {
      return PreOrderFind(E->rchild, type, data, value);
    }
  }
  return false; // ���ʽ�Ѿ����ˣ����� false
}

bool Is(int type, char ch) {
  // �ж� ch �Ƿ��� type
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
  // �ж��Ƿ�Ϊ type ��ԭ��
  size_t length = strlen(str);

  if (type == CONST) {
    for (size_t i = 0; i < length; i++)
    {
      if ((i == 0) && ((str[0] == '+') || (str[0] == '-')) && str[1]) {
        continue;
      }

      if (Is(type, str[i])) {
        continue;
      }
      return false;
    }
    return true;
  }
  else if (type == VARIABLE) {
    if (length == 1) {
      return Is(type, str[0]);
    }
    else if (length == 2) {
      return (str[0] == '+' || str[0] == '-') && Is(type, str[1]);
    }
  }

  return false;
}

Expression ReadExpr(char const *str) {
  // ���ַ���������ʽ������﷨���󣬷��� NULL
  // ������ַ���
  //    �������+-*/^
  //    ������0-9
  //    ������a-zA-Z
  //    �ָ������ո񣨿�ѡ��
  Expression E = NULL;
  int        value = 0;
  size_t     length = strlen(str);
  bool       BAD = false, MINUS = false;

  for (size_t i = 0; i < length; i++) {
    if (Is(CONST, str[i])) {
      value = value * 10 + (str[i] - '0');

      if (!Is(CONST, str[i + 1])) { // ��һ���ַ����ǳ���
        if (MINUS) {
          value = -value;           // �Ǹ��ĳ���ԭ��
        }

        if (!PreOrderFind(E, CONST, '\0', value)) {
          BAD = true;
          break;
        }
        value = 0; // ����
      }
    }
    else {
      if (Is(OPERATOR, str[i])) {
        if ((i == 0) && IsAtom(CONST, str)) {
          if (str[i] == '-') {
            MINUS = true; // �Ǹ��ĳ���ԭ��
          }
        }
        else if (!PreOrderFind(E, OPERATOR, str[i], 0)) {
          BAD = true;
          break;
        }
      }
      else if (Is(VARIABLE, str[i])) {
        if ((i == 1) && IsAtom(VARIABLE, str)) {
          // ����Ǳ���ԭ�ӣ�ǰ�油��
          if (!PreOrderFind(E, CONST, '\0', 0)) {
            BAD = true;
            break;
          }
        }

        if (!PreOrderFind(E, VARIABLE, str[i], 0)) {
          BAD = true;
          break;
        }
      }
      else if (str[i] == ' ') {
        continue;
      }
      else {
        BAD = true;
        break;
      }
    } // endelse
  }   // endfor

  if (BAD || !IsReasonable(E)) {
    DestroyExpression(E);
    printf("%s\n", "������ı��ʽ��");
    return NULL;
  }
  return E;
}

bool IsHigher(Expression parent, Expression child) {
  // �жϸ�ĸ��������������ȼ��Ƿ���ӽ������ȼ���
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
  // �ô���������׺��ʾʽ������ʽ E���������
  if (E) {
    if (E->lchild) {
      if (IsHigher(E, E->lchild)) {
        putchar('(');
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
  // �ӻ��з�
  if (E) {
    WriteEx(E);
    putchar('\n');
  }
}

Expression CompoundExpr(char P, Expression E1, Expression E2) {
  // ����һ���µĸ��ϱ��ʽ��(E1)P(E2)��(P E1 E1)
  if (!Is(OPERATOR, P)) { // ���������
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
  // �Ա��� V �ĸ�ֵ(V = c)
  if (E) {
    if ((E->type == VARIABLE) && (E->data == V)) {
      E->value = num;
    }
    Assign(E->lchild, V, num);
    Assign(E->rchild, V, num);
  }
}

int Value(Expression E) {
  // ���������ʽ E ��ֵ
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
