#include "graph.h"

Status CreateGraph(ALGraph   & G,
                   GraphKind   kind,
                   char const *vexs,
                   int         n,
                   ArcInfo    *arcs,
                   int         e) {
  // ������n�������e���ߵ�����ͼG��vexsΪ������Ϣ��arcsΪ����Ϣ
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
  // ������ͼG��ֵΪ v �Ķ������ȡ���k���㲻���ڣ��򷵻�-1
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
  // ������ͼG��ֵΪ v �Ķ���ĳ��ȡ���k���㲻���ڣ��򷵻�-1
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
  // ��鶥��k���ڽ��������Ƿ���� m�����Ӧ�Ľ��
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
  // ���Ҷ���v��ͼG������

  for (int i = 0; i < G.n; i++) {
    if (G.vexs[i].data == v) {
      return i;
    }
  }
  return -1; // û�ҵ�
}

int FirstAdjVex(ALGraph G, int k, AdjVexNodeP& p) {
  // ��ͼG������Ϊk�Ķ�����ڽ�����ǿգ�����ָ��pָ���һ����㣬������������
  // ������ p Ϊ NULL������-1
  if ((k < 0) || (k >= G.n)) {
    return -1;
  }
  p = G.vexs[k].firstArc;

  if (p != NULL) {
    return p->adjvex;
  }
  else {
    return -1; // ����Ϊk�Ķ������ڽӶ���
  }
}

int NextAdjVex(ALGraph G, int k, AdjVexNodeP& p) {
  // p ��ָ���������Ϊ k �Ķ�����ڽ������У��� p ָ��
  // p��ָ������һ����㣬����������
  // ��� p Ϊ NULL������ -1
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
        return -1; // ����Ϊk�Ķ������ڽӶ���
      }
    }
    t = t->next;
  }
  return -1; // p ��ָ��㲻������Ϊ k �Ķ�����ڽ�������
}

Status DestoryAdjVexNode(AdjVexNodeP& p) {
  // �����ڽ�����
  AdjVexNodeP current = p, t;

  while (current) {
    t = current->next;
    free(current);
    current = t;
  }
  return OK;
}

Status DestoryGraph(ALGraph& G) {
  // ����ͼG
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
  // ȡͼG������Ϊk�Ķ����ֵ�� w
  if ((k < 0) || (k >= G.n)) {
    return ERROR;
  }
  v = G.vexs[k].data;
  return OK;
}

Status SetVex(ALGraph G, int k, VexType v) {
  // ��ͼG������Ϊk�Ķ��㸳ֵ v
  // ���ͼG�Ѿ�����ֵΪ v �Ľ�㲻��ֵ
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
  // ��ͼ G ������ֵΪ v �Ķ��㵽ֵΪ w �Ķ���ı߻򻡣�info ΪȨֵ
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
      // ��������ͼ
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
  // ɾ��ͼ G ��ֵΪ v �Ķ��㵽ֵΪ w �Ķ���ı߻�
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
      // ��������ͼ
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
  // ������ȱ���ͼ G
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
  // ͼ�Ķ��������ָ��
  AdjVexNodeP p;

  // ���ѷ��ʱ��
  G.tags[v] = VISITED;

  // ��������ʶ���ı��
  if (ERROR == visit(G.vexs[v].data)) return ERROR;

  // pָ�򶥵�v�ĵ�һ�����Ļ�ͷ���
  p = G.vexs[v].firstArc;

  while (p != NULL)
  {
    // ��p->adjvex����δ����,�ݹ������
    if (G.tags[p->adjvex] == UNVISITED) {
      if (DFS(G, p->adjvex, visit) == ERROR) {
        return ERROR;
      }
    }

    // pָ�򶥵�v����һ�����Ļ�ͷ���
    p = p->next;
  }
  return OK;
}

Status DFSTraverse(ALGraph G, Status (*visit)(VexType)) {
  // ������ȱ���ͼ G
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
