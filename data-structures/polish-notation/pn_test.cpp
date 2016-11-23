#include "polish-notation.h"

int tests_run = 0;

static char const* testinit() {
  BiTree T = ReadExpr("+*15^x2*8x");

  mu_assert("read expression", T != NULL);
  InOrderPrint(T);
  return OK;
}

static char const* run() {
  mu_run_test(testinit);
  return OK;
}

TEST_MAIN;
