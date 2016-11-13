#ifndef MINIUNIT_H
#define MINIUNIT_H

#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR 1
#define IBFEASIBLE -1
#define OVERFLOW -2
#define MAXLEN 20
#define MAXSIZE 20

#ifndef NULL
# ifdef __cplusplus
#  define NULL 0
# else /* ifdef __cplusplus */
#  define NULL ((void *)0)
# endif /* ifdef __cplusplus */
#endif /* ifndef NULL */

typedef int Status;

#define mu_assert(message, test) \
  { if (!(test)) return message; }

#define mu_run_test(test)                      \
  { char const *message = test(); tests_run++; \
    if (message) return message; }

extern int tests_run;

#include <cstdio>

#define TEST_MAIN int main()                       \
  {                                                \
    char const *result = run();                    \
    if (result != 0) printf("%s\n", result);       \
    else printf("All passed.\n");                  \
    printf("Total %d test(s) runned.", tests_run); \
    return 0;                                      \
  }

#endif /* ifndef MINIUNIT_H */
