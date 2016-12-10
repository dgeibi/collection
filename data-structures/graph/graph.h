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
} GraphKind;                   // 有向图,有向网,无向图,无向网

typedef struct AdjVexNode {
  int                adjvex;   // 邻接顶点在顶点数组中的位序
  struct AdjVexNode *next;     // 指向下一个邻接顶点
  int                info;     // 存储边（弧）相关信息，权值，对于非带权图可不用
} AdjVexNode, *AdjVexNodeP;    // 邻接链表的结点类型

typedef struct VexNode {
  VexType            data;     // 顶点值，VexType是顶点类型，由用户定义
  struct AdjVexNode *firstArc; // 邻接链表的头指针
} VexNode;                     // 顶点数组的元素类型

typedef struct {
  VexNode  *vexs;              // 顶点数组，用于存储顶点信息
  int       n, e;              // 顶点数和边（弧）数
  GraphKind kind;              // 图的类型
  int      *tags;              // 标志数组
} ALGraph;                     // 邻接表类型

typedef struct {
  VexType v, w;                // 顶点值
  int     info;                // 对带权图，为权值
} ArcInfo;                     // 边（弧）信息

Status CreateGraph(ALGraph   & G,
                   GraphKind   kind,
                   char const *vexs,
                   int         n,
                   ArcInfo    *arcs,
                   int         e); // 创建图的邻接表

Status DestoryGraph(ALGraph& G);   // 销毁图G

int    LocateVex(ALGraph G,
                 VexType v);

// 查找顶点v在图G的索引

Status GetVex(ALGraph  G,
              int      k,
              VexType& v);

// 取图G中索引为k的顶点的值到 v

Status SetVex(ALGraph G,
              int     k,
              VexType v);

// 给图G中索引为k的顶点赋值 v
// 若图G已经存在值为 v 的结点则不赋值

int FirstAdjVex(ALGraph      G,
                int          k,
                AdjVexNodeP& p);

// 若图G中索引为k的顶点的邻接链表非空，这令指针p指向第一个结点，并返回其索引
// 否则，令 p 为 NULL，返回-1

int NextAdjVex(ALGraph      G,
               int          k,
               AdjVexNodeP& p);

// p 所指结点在索引为 k 的顶点的邻接链表中，令 p 指向 p所指结点的下一个结点，并返回索引
// 如果 p 为 NULL，返回 -1

Status AddArc(ALGraph& G,
              VexType  v,
              VexType  w,
              int      info);

// 在图 G 中增加值为 v 的顶点到值为 w 的顶点的边或弧，info 为权值

Status RemoveArc(ALGraph& G,
                 VexType  v,
                 VexType  w);

// 删除图 G 中值为 v 的顶点到值为 w 的顶点的边或弧

Status ExistIn(ALGraph G,
               int     m,
               int     k);                    // 检查顶点k的邻接链表中是否存在
                                              // m顶点对应的结点

int outDegree(ALGraph G,
              VexType v);                     // 求有向图G中值为 v
                                              // 的顶点的出度。若k顶点不存在，则返回-1

int inDegree(ALGraph G,
             VexType v);                      // 求有向图G中值为 v
                                              // 的顶点的入度。若k顶点不存在，则返回-1

Status DFSTraverse(ALGraph  G,
                   Status (*visit)(VexType)); // 深度优先遍历图 G

Status BFSTraverse(ALGraph  G,
                   Status (*visit)(VexType)); // 广度优先遍历图 G

void   g_print(ALGraph G);                    // 打印有向图

#endif /* ifndef GRAPH_H */
