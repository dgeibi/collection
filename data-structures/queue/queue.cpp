#include "queue.h"

void InitQueue_LQ(LQueue& Q) {
  /* 构造一个空队列Q */
  Q.front = Q.rear = NULL;
}

void DestroyQueue_LQ(LQueue& Q) {
  /* 销毁队列Q(无论空否均可) */
  while (Q.front)
  {
    Q.rear = Q.front->next;
    free(Q.front);
    Q.front = Q.rear;
  }
  Q.front = Q.rear = NULL;
}

bool IsEmpty_LQ(LQueue Q) {
  /* 若Q为空队列，则返回TRUE，否则返回FALSE */
  if (Q.front == NULL) return true;
  else return false;
}

int QueueLength_LQ(LQueue Q) {
  /* 求队列的长度 */
  int i = 0;
  QueuePtr p;

  p = Q.front;

  while (Q.rear != p)
  {
    i++;
    p = p->next;
  }

  if (Q.rear != Q.front) {
    i++;
  }

  return i;
}

Status GetHead_LQ(LQueue Q, QElemType& e) {
  /* 若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR */

  if (Q.front == Q.rear) return ERROR;
  e = Q.front->data;
  return OK;
}

void EnQueue_LQ(LQueue& Q, QElemType e) {
  /* 插入元素e为Q的新的队尾元素 */
  QueuePtr p = (QueuePtr)malloc(sizeof(LQNode));

  if (!p) /* 存储分配失败 */
    exit(_OVERFLOW_);
  p->data = e;
  p->next = NULL;

  if (NULL == Q.front) {
    Q.front = p;
  }
  else {
    Q.rear->next = p;
  }
  Q.rear = p;
}

Status DeQueue_LQ(LQueue& Q, QElemType& e) {
  /* 若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR */
  QueuePtr p;

  if (IsEmpty_LQ(Q)) return ERROR;

  p       = Q.front; /* 指向头结点 */
  e       = p->data;
  Q.front = p->next; /* 摘下头节点 */

  if (Q.rear == p) Q.rear = NULL;
  free(p);
  return OK;
}

void Traverse_LQ(LQueue Q, void (*vi)(QElemType)) {
  /* 从队头到队尾依次对队列Q中每个元素调用函数vi() */
  QueuePtr p;

  p = Q.front;

  while (p)
  {
    vi(p->data);
    p = p->next;
  }
  printf("\n");
}
