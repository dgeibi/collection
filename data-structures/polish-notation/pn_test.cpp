#include "polish-notation.h"

int tests_run = 0; // 记录测试次数

static char const* testinit() {
  Expression  E;
  char const *str1[] = {
    "0",
    "a",
    "+111",
    "-91",
    "+a*bc",
    "+a",
    "-a",
    "+*15^x2*8x",
    "+++*3^x3*2^x2x6",
    "+ 1 2",
    "/ + 12 22 * 11 66",
    "^* 1 2 /3 5",
    "^ ^ 2 3 4",
    "* / 2 45 2"
  };
  size_t length = sizeof(str1) / sizeof(*str1); // 表达式的个数

  printf("\n%s\n", "ReadExpr and WriteExpr:");

  for (size_t i = 0; i < length; i++) {
    // 依次读取表达式，并输出中缀表达式
    E = ReadExpr(str1[i]);
    mu_assert("read expression", E != NULL);
    printf("Input: %-20s Output: ", str1[i]);
    WriteExpr(E);
    DestroyExpr(E);
  }
  char const *str2[] = {
    "1+2",
    "*11",
    "+ 1 2 3",
    "+ * 2 3 1 x",
    "+ * 2 3"
  };
  length = sizeof(str2) / sizeof(*str2);

  for (size_t i = 0; i < length; i++) {
    printf("Input: %-20s Output: ", str2[i]);
    mu_assert("read expression NULL", ReadExpr(str2[i]) == NULL);
  }
  return OK;
}

static char const* testatom() {
  mu_assert("IsAtom_CONST",  IsAtom(CONST, "12"));
  mu_assert("IsAtom_CONST",  IsAtom(CONST, "+1112"));
  mu_assert("IsAtom_CONST",  IsAtom(CONST, "-23"));
  mu_assert("!IsAtom_CONST", !IsAtom(CONST, "-23v"));
  mu_assert("!IsAtom_CONST", !IsAtom(CONST, "*23"));
  mu_assert("!IsAtom_CONST", !IsAtom(CONST, "-23 3"));
  mu_assert("IsAtom_VAR",    IsAtom(VARIABLE, "b"));
  mu_assert("IsAtom_VAR",    IsAtom(VARIABLE, "-a"));
  mu_assert("IsAtom_VAR",    IsAtom(VARIABLE, "+a"));
  mu_assert("!IsAtom_VAR",   !IsAtom(VARIABLE, "+ab"));
  mu_assert("!IsAtom_VAR",   !IsAtom(VARIABLE, "/b"));
  return OK;
}

static char const* testcompound() {
  Expression t1 = ReadExpr("+12 11"), t2 = ReadExpr("-1 20");
  Expression E = CompoundExpr('*', t1, t2);

  mu_assert("compound", NULL != E);
  mu_assert("null expression compound", NULL == CompoundExpr('/', NULL, t1));
  mu_assert("illegal operator compound", NULL == CompoundExpr('c', t2, t1));
  
  printf("\n%s\n", "CompoundExpr:");
  WriteEx(t1); printf(" %s ", "multiplied by"); WriteEx(t2); printf(" %s ",
                                                                    "equals");
  WriteExpr(E);
  DestroyExpr(t1);
  DestroyExpr(t2);
  DestroyExpr(E);
  return OK;
}

static char const* testvalue() {
  Expression E;

  mu_assert("value",       Value(ReadExpr("0")) == 0);
  mu_assert("value",       Value(ReadExpr("a")) == 0);
  mu_assert("value_atom",  Value(ReadExpr("-91")) == -91);
  mu_assert("value_add",   Value(ReadExpr("+ 1 2")) == 3);
  mu_assert("value_power", Value(ReadExpr("^ 3 3")) == 27);
  E = ReadExpr("+a*bc");
  Assign(E, 'a', 11);
  Assign(E, 'b', 2);
  Assign(E, 'c', 3);
  mu_assert("value_assign", Value(E) == 17);
  return OK;
}

static char const* testmerge() {
  Expression  E;
  char const *str[] = {
    "+ 1 2",
    "*-+2 3a+b*3 4",
    "*1x",
    "*0b"
  };
  size_t length = sizeof(str) / sizeof(*str);

  printf("\n%s\n", "MergeConst:");

  for (size_t i = 0; i < length; i++) {
    E = ReadExpr(str[i]);
    printf("%s", "Before: "); WriteExpr(E);
    MergeConst(E);
    printf("%s", "After: "); WriteExpr(E);
    DestroyExpr(E);
  }
  return OK;
}

static char const* testdiff() {
  Expression  E, dE;
  char const *str[] = {
    "a",
    "+- 233 y x",
    "^x2",
    "/ 1 x",
    "* + x 2 - * x 2 1",
    "* - + 2 3 a + x * 3 4",
    "-*3^x4*2^x2",
    "+ / 2 x / 3 * 2 x"
  };
  size_t length = sizeof(str) / sizeof(*str);

  printf("\n%s\n", "Diff:");

  for (size_t i = 0; i < length; i++) {
    E  = ReadExpr(str[i]);
    dE = Diff(E, 'x');
    MergeConst(dE);
    printf("%s", "primitive: "); WriteExpr(E);
    printf("%s", "diff(x): "); WriteExpr(dE);
    putchar('\n');
  }
  return OK;
}

int getChoice() {
  int choice;

  printf("Do something with expression:\n");
  printf("1. Value\n");
  printf("2. Assign\n");
  printf("3. Diff\n");
  printf("4. Enter next expression or Exit\n");
  printf("Enter your choice:");

  while (scanf("%d", &choice) != 1) {
    CLEAN_INPUT;
    printf("Enter your choice again:");
  }
  CLEAN_INPUT;
  return choice;
}

static char const* testcalculator() {
  char *buffer = (char *)malloc(100);
  char  ch;
  int   value;
  Expression E, nE;

  printf("\n%s\n",
         "Please enter polish notation (press enter key directly to exit): ");

  while (fgets(buffer, 100, stdin)) {
    buffer[strcspn(buffer, "\r\n")] = 0; // 将第一个 \r 或者 \n 替换为 \0

    if (buffer[0] == 0) {
      break;
    }
    E = ReadExpr(buffer);

    if (E) {
      switch (getChoice()) {
        case 2:

          printf("%s\n",
                 "Enter variable for assignment (press enter key directly to exit): ");

          while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
            CLEAN_INPUT;

            if (Is(VARIABLE, ch)) {
              printf("Enter the value to be assigned to %c:\n", ch);

              while (scanf("%d", &value) != 1) {
                CLEAN_INPUT;
                printf("Enter the value to be assigned to %c again:\n", ch);
              }
              CLEAN_INPUT;
              Assign(E, ch, value);
            }

            printf("%s\n",
                   "Enter variable for assignment (press enter key directly to exit): ");
          }

        case 1:
          printf("Result: ");
          WriteEx(E);
          printf("=%d\n", Value(E));
          break;

        case 3:
          printf("%s\n",
                 "Enter variable for differentiation (press enter key directly to exit): ");

          while (!Is(VARIABLE, (ch = fgetc(stdin)))) {
            if ((ch == EOF) || (ch == '\n')) {
              break;
            }
            CLEAN_INPUT;
            printf("%c is not a variable.\n", ch);
            printf("Please enter a variable: ");
          }

          if ((ch != EOF) && (ch != '\n')) {
            CLEAN_INPUT;
          }

          if (Is(VARIABLE, ch)) {
            printf("primitive: "); WriteExpr(E);
            nE = Diff(E, ch);
            printf("diff(%c): ", ch); WriteExpr(MergeConst(nE));
          }
          break;

        default:
          break;
      }
    }
    printf("\n%s\n",
           "Please enter polish notation (press enter key directly to exit): ");
  }
  return OK;
}

static char const* run() {
  mu_run_test(testinit);
  mu_run_test(testatom);
  mu_run_test(testcompound);
  mu_run_test(testvalue);
  mu_run_test(testmerge);
  mu_run_test(testdiff);
  mu_run_test(testcalculator);
  return OK;
}

TEST_MAIN;
