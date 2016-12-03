#include "../vendor/miniunit.h"

#include <cstdlib>

#ifndef QUEUE_H
# define QUEUE_H

typedef int QElemType;

typedef struct LQNode {
  QElemType      data;
  struct LQNode *next;
} LQNode, *QueuePtr;                       // 结点和结点指针类型

typedef struct {
  QueuePtr front;                          // 队头指针
  QueuePtr rear;                           // 队尾指针
} LQueue;                                  // 链队列类型

void   InitQueue_LQ(LQueue& Q);            /* 构造一个空队列Q */

void   DestroyQueue_LQ(LQueue& Q);         /* 销毁队列Q(无论空否均可) */

bool   IsEmpty_LQ(LQueue Q);               /* 若Q为空队列，则返回 true，否则返回 false */

int    QueueLength_LQ(LQueue Q);           /* 求队列的长度 */

Status GetHead_LQ(LQueue     Q,
                  QElemType& e);           /* 若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR*/

void   EnQueue_LQ(LQueue  & Q,
                  QElemType e);            /* 插入元素e为Q的新的队尾元素 */

Status DeQueue_LQ(LQueue   & Q,
                  QElemType& e);           /* 若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR */

void   Traverse_LQ(LQueue Q,
                   void (*vi)(QElemType)); /* 从队头到队尾依次对队列Q中每个元素调用函数vi() */
#endif /* ifndef QUEUE_H */
