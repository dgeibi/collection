#include "polish-notation.h"

int tests_run = 0;

static char const* testinit() {
  BiTree T;
  char const *str[] = {
    "0",
    "a",
    "-91",
    "+a*bc",
    "+*15^x2*8x",
    "+++*3^x3*2^x2x6",
    "+ 1 2",
    "/ + 12 22 * 11 66",
    "^* 1 2 /3 5",
    "^ ^ 2 3 4",
    "* / 2 45 2"
  };
  size_t length = sizeof(str) / sizeof(*str);

  printf("\n%s\n", "ReadExpr and WriteExpr:");

  for (int i = 0; i < length; i++) {
    T = ReadExpr(str[i]);
    mu_assert("read expression", T != NULL);
    WriteExpr(T);
  }
  return OK;
}

static char const* testcompound() {
  BiTree t1 = ReadExpr("+12 11"), t2 = ReadExpr("-1 20");
  BiTree T = CompoundExpr('+', t1, t2);

  mu_assert("compound", NULL != T);
  printf("\n%s\n", "CompoundExpr:");
  WriteExpr(t1);
  WriteExpr(t2);
  WriteExpr(T);
  return OK;
}

static char const* testvalue() {
  BiTree T;

  mu_assert("value",       Value(ReadExpr("0")) == 0);
  mu_assert("value",       Value(ReadExpr("a")) == 0);
  mu_assert("value_atom",  Value(ReadExpr("-91")) == -91);
  mu_assert("value_add",   Value(ReadExpr("+ 1 2")) == 3);
  mu_assert("value_power", Value(ReadExpr("^ 3 3")) == 27);
  T = ReadExpr("+a*bc");
  Assign(T, 'a', 11);
  Assign(T, 'b', 2);
  Assign(T, 'c', 3);
  mu_assert("value_assign", Value(T) == 17);
  return OK;
}

static char const* testmerge() {
  BiTree T;

  T = ReadExpr("+ 1 2");
  printf("\n%s\n", "MergeConst:");
  WriteExpr(T);
  MergeConst(T);
  WriteExpr(T);
  T = ReadExpr("*-+2 3a+b*3 4");
  WriteExpr(T);
  MergeConst(T);
  WriteExpr(T);
  return OK;
}

static char const* run() {
  mu_run_test(testinit);
  mu_run_test(testcompound);
  mu_run_test(testvalue);
  mu_run_test(testmerge);
  return OK;
}

TEST_MAIN;
