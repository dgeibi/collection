#include "graph.h"

Status CreateGraph(ALGraph   & G,
                   GraphKind   kind,
                   char const *vexs,
                   int         n,
                   ArcInfo    *arcs,
                   int         e) {
  // 创建含n个顶点和e条边的有向图G，vexs为顶点信息，arcs为边信息
  int i;

  G.kind = kind;
  G.n    = n;
  G.e    = 0;
  G.vexs = NULL;
  G.tags = NULL;

  if (n <= 0) {
    return ERROR;
  }

  if (MAX_SIZE_ARCS < e) {
    return ERROR;
  }

  G.vexs = (VexNode *)malloc(n * sizeof(VexNode));
  G.tags = (int *)malloc(n * sizeof(int));

  for (i = 0; i < G.n; i++)
  {
    G.tags[i]          = UNVISITED;
    G.vexs[i].data     = vexs[i];
    G.vexs[i].firstArc = NULL;
  }

  for (i = 0; i < e; i++)
  {
    if (ERROR == AddArc(G, arcs[i].v, arcs[i].w, arcs[i].info)) return ERROR;
  }
  return OK;
}

int inDegree(ALGraph G, VexType v) {
  // 求有向图G中值为 v 的顶点的入度。若k顶点不存在，则返回-1
  int k = LocateVex(G, v);

  if ((G.n <= 0) || (k < 0) || (k >= G.n)) {
    return -1;
  }

  int i, sum = 0;
  AdjVexNodeP p;

  for (i = 0; i < G.n; i++)
  {
    if (i == k) continue;
    p = G.vexs[i].firstArc;

    while (p)
    {
      if (p->adjvex == k) sum++;
      p = p->next;
    }
  }
  return sum;
}

int outDegree(ALGraph G, VexType v) {
  // 求有向图G中值为 v 的顶点的出度。若k顶点不存在，则返回-1
  int k = LocateVex(G, v);

  if ((G.n <= 0) || (k < 0) || (k >= G.n)) {
    return -1;
  }
  int i         = 0;
  AdjVexNode *p = G.vexs[k].firstArc;

  while (p)
  {
    i++;
    p = p->next;
  }
  return i;
}

Status ExistIn(ALGraph G, int m, int k) {
  // 检查顶点k的邻接链表中是否存在 m顶点对应的结点
  if ((k < 0) || (m < 0) || (k >= G.n) || (m >= G.n)) return ERROR;

  AdjVexNodeP p = G.vexs[k].firstArc;

  while (p) {
    if (p->adjvex == m) {
      return TRUE;
    }
    p = p->next;
  }
  return FALSE;
}

int LocateVex(ALGraph G, VexType v) {
  // 查找顶点v在图G的索引

  for (int i = 0; i < G.n; i++) {
    if (G.vexs[i].data == v) {
      return i;
    }
  }
  return -1; // 没找到
}

int FirstAdjVex(ALGraph G, int k, AdjVexNodeP& p) {
  // 若图G中索引为k的顶点的邻接链表非空，这令指针p指向第一个结点，并返回其索引
  // 否则，令 p 为 NULL，返回-1
  if ((k < 0) || (k >= G.n)) {
    return -1;
  }
  p = G.vexs[k].firstArc;

  if (p != NULL) {
    return p->adjvex;
  }
  else {
    return -1; // 索引为k的顶点无邻接顶点
  }
}

int NextAdjVex(ALGraph G, int k, AdjVexNodeP& p) {
  // p 所指结点在索引为 k 的顶点的邻接链表中，令 p 指向
  // p所指结点的下一个结点，并返回索引
  // 如果 p 为 NULL，返回 -1
  if ((k < 0) || (k >= G.n) || (p == NULL)) {
    return -1;
  }
  AdjVexNodeP t;
  FirstAdjVex(G, k, t);

  while (t) {
    if (t == p) {
      p = p->next;

      if (p != NULL) {
        return p->adjvex;
      }
      else {
        return -1; // 索引为k的顶点无邻接顶点
      }
    }
    t = t->next;
  }
  return -1; // p 所指结点不在索引为 k 的顶点的邻接链表中
}

Status DestoryAdjVexNode(AdjVexNodeP& p) {
  // 销毁邻接链表
  AdjVexNodeP current = p, t;

  while (current) {
    t = current->next;
    free(current);
    current = t;
  }
  return OK;
}

Status DestoryGraph(ALGraph& G) {
  // 销毁图G
  int n = G.n;

  for (int i = 0; i < n; i++) {
    DestoryAdjVexNode(G.vexs[i].firstArc);
  }

  if (G.tags != NULL) {
    free(G.tags);
  }

  if (G.vexs != NULL) {
    free(G.vexs);
  }
  G.n = 0;
  G.e = 0;
  return OK;
}

Status GetVex(ALGraph G, int k, VexType& v) {
  // 取图G中索引为k的顶点的值到 w
  if ((k < 0) || (k >= G.n)) {
    return ERROR;
  }
  v = G.vexs[k].data;
  return OK;
}

Status SetVex(ALGraph G, int k, VexType v) {
  // 给图G中索引为k的顶点赋值 v
  // 如果图G已经存在值为 v 的结点不赋值
  if ((k < 0) || (k >= G.n)) {
    return ERROR;
  }

  if (-1 == LocateVex(G, v)) {
    G.vexs[k].data = v;
    return OK;
  }
  else {
    return ERROR;
  }
}

Status AddArc(ALGraph& G, VexType v, VexType w, int info) {
  // 在图 G 中增加值为 v 的顶点到值为 w 的顶点的边或弧，info 为权值
  AdjVexNodeP p;

  int k = LocateVex(G, v);
  int m = LocateVex(G, w);

  if ((k < 0) || (m < 0) || (k >= G.n) || (m >= G.n)) return ERROR;

  if (!ExistIn(G, m, k)) {
    G.e++;
    p                  = (AdjVexNodeP)malloc(sizeof(AdjVexNode));
    p->info            = info;
    p->adjvex          = m;
    p->next            = G.vexs[k].firstArc;
    G.vexs[k].firstArc = p;

    if ((G.kind == UDG) || (G.kind == UDN)) {
      // 对于无向图
      p                  = (AdjVexNodeP)malloc(sizeof(AdjVexNode));
      p->info            = info;
      p->adjvex          = k;
      p->next            = G.vexs[m].firstArc;
      G.vexs[m].firstArc = p;
    }
  }
  else {
    return ERROR;
  }
  return OK;
}

Status RemoveArc(ALGraph& G, VexType v, VexType w) {
  // 删除图 G 中值为 v 的顶点到值为 w 的顶点的边或弧
  AdjVexNodeP p, t;
  int k = LocateVex(G, v);
  int m = LocateVex(G, w);

  if ((k < 0) || (m < 0) || (k >= G.n) || (m >= G.n)) return ERROR;

  if (ExistIn(G, m, k)) {
    p = G.vexs[k].firstArc;

    if (p->adjvex == m) {
      G.vexs[k].firstArc = p->next;
      free(p);
    }
    else {
      while (p) {
        if (p->next->adjvex == m) {
          t = p->next;
          break;
        }
        p = p->next;
      }

      if ((p != NULL) && (t != NULL)) {
        p->next = t->next;
        t->next = NULL;
        free(t);
      }
    }
    G.e--;

    if ((G.kind == UDG) || (G.kind == UDN)) {
      // 对于无向图
      p = G.vexs[m].firstArc;

      if (p->adjvex == k) {
        G.vexs[m].firstArc = p->next;
        free(p);
      }
      else {
        while (p) {
          if (p->next->adjvex == k) {
            t = p->next;
            break;
          }
          p = p->next;
        }

        if ((p != NULL) && (t != NULL)) {
          p->next = t->next;
          t->next = NULL;
          free(t);
        }
      }
    }
  }
  else {
    return ERROR;
  }
  return OK;
}

Status BFSTraverse(ALGraph G, Status (*visit)(VexType)) {
  // 广度优先遍历图 G
  int i, j, k;
  AdjVexNodeP p;
  LQueue Q; InitQueue_LQ(Q);

  for (i = 0; i < G.n; i++) {
    G.tags[i] = UNVISITED;
  }

  for (i = 0; i < G.n; i++)
    if (UNVISITED == G.tags[i]) {
      if (ERROR == visit(G.vexs[i].data)) return ERROR;

      G.tags[i] = VISITED;
      EnQueue_LQ(Q, i);

      while (OK == DeQueue_LQ(Q, k)) {
        for (j = FirstAdjVex(G, k, p); j >= 0; j = NextAdjVex(G, k, p))
          if (UNVISITED == G.tags[j]) {
            if (ERROR == visit(G.vexs[j].data)) return ERROR;

            G.tags[j] = VISITED;
            EnQueue_LQ(Q, j);
          }
      }
    }
  return OK;
}

Status DFS(ALGraph G, int v, Status (*visit)(VexType)) {
  // 图的顶点的搜索指针
  AdjVexNodeP p;

  // 置已访问标记
  G.tags[v] = VISITED;

  // 输出被访问顶点的编号
  if (ERROR == visit(G.vexs[v].data)) return ERROR;

  // p指向顶点v的第一条弧的弧头结点
  p = G.vexs[v].firstArc;

  while (p != NULL)
  {
    // 若p->adjvex顶点未访问,递归访问它
    if (G.tags[p->adjvex] == UNVISITED) {
      if (DFS(G, p->adjvex, visit) == ERROR) {
        return ERROR;
      }
    }

    // p指向顶点v的下一条弧的弧头结点
    p = p->next;
  }
  return OK;
}

Status DFSTraverse(ALGraph G, Status (*visit)(VexType)) {
  // 深度优先遍历图 G
  int i;

  for (i = 0; i < G.n; i++) {
    G.tags[i] = UNVISITED;
  }

  for (i = 0; i < G.n; i++) {
    if (UNVISITED == G.tags[i]) {
      if (DFS(G, i, visit) == ERROR) return ERROR;
    }
  }

  return OK;
}

void g_print(ALGraph G) {
  AdjVexNodeP p;

  for (int i = 0; i < G.n; i++) {
    putchar(G.vexs[i].data);
    putchar(':');
    p = G.vexs[i].firstArc;

    while (p) {
      printf(" %c", G.vexs[p->adjvex].data);
      p = p->next;
    }
    putchar('\n');
  }
  putchar('\n');
}
