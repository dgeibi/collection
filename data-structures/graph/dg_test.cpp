#include "graph.h"

int tests_run = 0; // ��¼���Դ���

Status vi(VexType i) {
  // ����ʹ�õĺ���
  printf("%c  ", i);
  return OK;
}

static char const* testinit() {
  // ���� CreateGraph �� DestoryGraph
  ALGraph G;
  ArcInfo arcs[MAX_SIZE_ARCS];

  arcs[0] = { 'a', 'b', 1 };
  arcs[1] = { 'a', 'e', 1 };
  arcs[2] = { 'e', 'd', 1 };
  arcs[3] = { 'b', 'c', 1 };

  mu_assert("init: empty", CreateGraph(G, DG, NULL, 0, NULL, 0) == ERROR);
  DestoryGraph(G);
  mu_assert("init: subset", CreateGraph(G, DG, "abcde", 2, arcs, 4) == ERROR);
  DestoryGraph(G);
  mu_assert("init: normal",
            CreateGraph(G, DG, "abcde", 5, arcs, 4) == OK);
  DestoryGraph(G);
  mu_assert("init: arcs too small",
            CreateGraph(G,
                        DG,
                        "abcde",
                        5,
                        arcs,
                        MAX_SIZE_ARCS + 20) == ERROR);
  return OK;
}

static char const* testTraverse() {
  // ���� DFSTraverse �� BFSTraverse
  ALGraph G;
  ArcInfo arcs[MAX_SIZE_ARCS];

  arcs[0] = { 'a', 'b', 1 };
  arcs[1] = { 'a', 'e', 1 };
  arcs[2] = { 'e', 'd', 1 };
  arcs[3] = { 'b', 'c', 1 };

  CreateGraph(G, DG, "abcde", 5, arcs, 4);
  g_print(G);
  printf("DFS: ");
  mu_assert("DFSTraverse", DFSTraverse(G, vi) == OK);
  printf("\nBFS: ");
  mu_assert("BFSTraverse", BFSTraverse(G, vi) == OK);
  putchar('\n');
  putchar('\n');
  return OK;
}

static char const* testAdd() {
  // ���� AddArc
  ALGraph G;
  ArcInfo arcs[MAX_SIZE_ARCS];

  arcs[0] = { 'a', 'b', 1 };
  arcs[1] = { 'a', 'e', 1 };
  arcs[2] = { 'e', 'd', 1 };
  arcs[3] = { 'b', 'c', 1 };
  arcs[4] = { 'b', 'd', 1 };
  arcs[5] = { 'c', 'd', 1 };

  CreateGraph(G, DG, "abcde", 5, arcs, 6);
  mu_assert("add: repeat", AddArc(G, 'b', 'c', 1) == ERROR && G.e == 6);
  printf("\nBefore adding:\n");
  g_print(G);
  mu_assert("add: normal", AddArc(G, 'a', 'c', 1) == OK && G.e == 7);
  printf("\nAfter adding:\n");
  g_print(G);
  return OK;
}

static char const* testRemove() {
  // ���� RemoveArc
  ALGraph G;
  ArcInfo arcs[MAX_SIZE_ARCS];

  arcs[0] = { 'a', 'b', 1 };
  arcs[1] = { 'a', 'e', 1 };
  arcs[2] = { 'e', 'd', 1 };
  arcs[3] = { 'b', 'c', 1 };
  arcs[4] = { 'b', 'd', 1 };
  arcs[5] = { 'c', 'd', 1 };
  arcs[6] = { 'f', 'd', 1 };
  arcs[7] = { 'f', 'e', 1 };
  arcs[8] = { 'c', 'g', 1 };

  CreateGraph(G, DG, "abcdefg", 7, arcs, 9);
  mu_assert("remove: not exist", RemoveArc(G, 'g', 'c') == ERROR && G.e == 9);
  printf("\nBefore removing:\n");
  g_print(G);
  mu_assert("remove: normal", RemoveArc(G, 'a', 'b') == OK && G.e == 8);
  printf("\nAfter removing:\n");
  g_print(G);
  return OK;
}

static char const* testDegree() {
  //  ���� inDegree �� outDegree
  ALGraph G;
  ArcInfo arcs[MAX_SIZE_ARCS];

  arcs[0] = { 'a', 'b', 1 };
  arcs[1] = { 'a', 'e', 1 };
  arcs[2] = { 'e', 'd', 1 };
  arcs[3] = { 'b', 'c', 1 };
  arcs[4] = { 'b', 'd', 1 };
  arcs[5] = { 'c', 'd', 1 };
  arcs[6] = { 'f', 'd', 1 };
  arcs[7] = { 'f', 'e', 1 };
  arcs[8] = { 'c', 'g', 1 };

  CreateGraph(G, DG, "abcdefg", 7, arcs, 9);
  mu_assert("inDegree: normal",     inDegree(G, 'g') == 1);
  mu_assert("inDegree: zero",       inDegree(G, 'a') == 0);
  mu_assert("inDegree: not exist",  inDegree(G, 'h') == -1);
  mu_assert("outDegree: not exist", outDegree(G, 'h') == -1);
  mu_assert("outDegree: zero",      outDegree(G, 'd') == 0);
  mu_assert("outDegree: normal",    outDegree(G, 'f') == 2);
  return OK;
}

static char const* testVex() {
  // ���� SetVex �� GetVex
  ALGraph G;
  ArcInfo arcs[MAX_SIZE_ARCS];
  VexType ch;

  arcs[0] = { 'a', 'b', 1 };
  arcs[1] = { 'a', 'e', 1 };
  arcs[2] = { 'e', 'd', 1 };
  arcs[3] = { 'b', 'c', 1 };
  arcs[4] = { 'b', 'd', 1 };
  arcs[5] = { 'c', 'd', 1 };

  CreateGraph(G, DG, "abcde", 5, arcs, 6);
  mu_assert("SetVex: not exist", SetVex(G, 10, 'h') == ERROR);
  mu_assert("SetVex: repeat",    SetVex(G, 3,  'c') == ERROR);
  mu_assert("SetVex: normal",    SetVex(G, 3,  'h') == OK);
  mu_assert("GetVex: not exist", GetVex(G, 12, ch) == ERROR);
  mu_assert("GetVex: normal",    GetVex(G, 3, ch) == OK && ch == 'h');
  return OK;
}

static char const* run() {
  // ִ�����в���
  mu_run_test(testinit);
  mu_run_test(testTraverse);
  mu_run_test(testAdd);
  mu_run_test(testRemove);
  mu_run_test(testDegree);
  mu_run_test(testVex);
  return OK;
}

TEST_MAIN;
