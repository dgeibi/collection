#include "../vendor/miniunit.h"
#include "../queue/queue.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

#ifndef GRAPH_H
# define GRAPH_H
# define UNVISITED  0
# define VISITED    1
# define MAX_SIZE_ARCS 20

typedef char VexType;

typedef enum {
  DG, DN, UDG, UDN
} GraphKind;                   // ����ͼ,������,����ͼ,������

typedef struct AdjVexNode {
  int                adjvex;   // �ڽӶ����ڶ��������е�λ��
  struct AdjVexNode *next;     // ָ����һ���ڽӶ���
  int                info;     // �洢�ߣ����������Ϣ��Ȩֵ�����ڷǴ�Ȩͼ�ɲ���
} AdjVexNode, *AdjVexNodeP;    // �ڽ�����Ľ������

typedef struct VexNode {
  VexType            data;     // ����ֵ��VexType�Ƕ������ͣ����û�����
  struct AdjVexNode *firstArc; // �ڽ������ͷָ��
} VexNode;                     // ���������Ԫ������

typedef struct {
  VexNode  *vexs;              // �������飬���ڴ洢������Ϣ
  int       n, e;              // �������ͱߣ�������
  GraphKind kind;              // ͼ������
  int      *tags;              // ��־����
} ALGraph;                     // �ڽӱ�����

typedef struct {
  VexType v, w;                // ����ֵ
  int     info;                // �Դ�Ȩͼ��ΪȨֵ
} ArcInfo;                     // �ߣ�������Ϣ

Status CreateGraph(ALGraph   & G,
                   GraphKind   kind,
                   char const *vexs,
                   int         n,
                   ArcInfo    *arcs,
                   int         e); // ����ͼ���ڽӱ�

Status DestoryGraph(ALGraph& G);   // ����ͼG

int    LocateVex(ALGraph G,
                 VexType v);

// ���Ҷ���v��ͼG������

Status GetVex(ALGraph  G,
              int      k,
              VexType& v);

// ȡͼG������Ϊk�Ķ����ֵ�� v

Status SetVex(ALGraph G,
              int     k,
              VexType v);

// ��ͼG������Ϊk�Ķ��㸳ֵ v
// ��ͼG�Ѿ�����ֵΪ v �Ľ���򲻸�ֵ

int FirstAdjVex(ALGraph      G,
                int          k,
                AdjVexNodeP& p);

// ��ͼG������Ϊk�Ķ�����ڽ�����ǿգ�����ָ��pָ���һ����㣬������������
// ������ p Ϊ NULL������-1

int NextAdjVex(ALGraph      G,
               int          k,
               AdjVexNodeP& p);

// p ��ָ���������Ϊ k �Ķ�����ڽ������У��� p ָ�� p��ָ������һ����㣬����������
// ��� p Ϊ NULL������ -1

Status AddArc(ALGraph& G,
              VexType  v,
              VexType  w,
              int      info);

// ��ͼ G ������ֵΪ v �Ķ��㵽ֵΪ w �Ķ���ı߻򻡣�info ΪȨֵ

Status RemoveArc(ALGraph& G,
                 VexType  v,
                 VexType  w);

// ɾ��ͼ G ��ֵΪ v �Ķ��㵽ֵΪ w �Ķ���ı߻�

Status ExistIn(ALGraph G,
               int     m,
               int     k);                    // ��鶥��k���ڽ��������Ƿ����
                                              // m�����Ӧ�Ľ��

int outDegree(ALGraph G,
              VexType v);                     // ������ͼG��ֵΪ v
                                              // �Ķ���ĳ��ȡ���k���㲻���ڣ��򷵻�-1

int inDegree(ALGraph G,
             VexType v);                      // ������ͼG��ֵΪ v
                                              // �Ķ������ȡ���k���㲻���ڣ��򷵻�-1

Status DFSTraverse(ALGraph  G,
                   Status (*visit)(VexType)); // ������ȱ���ͼ G

Status BFSTraverse(ALGraph  G,
                   Status (*visit)(VexType)); // ������ȱ���ͼ G

void   g_print(ALGraph G);                    // ��ӡ����ͼ

#endif /* ifndef GRAPH_H */
