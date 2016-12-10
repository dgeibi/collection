#include "queue.h"

void InitQueue_LQ(LQueue& Q) {
  /* ����һ���ն���Q */
  Q.front = Q.rear = NULL;
}

void DestroyQueue_LQ(LQueue& Q) {
  /* ���ٶ���Q(���ۿշ����) */
  while (Q.front)
  {
    Q.rear = Q.front->next;
    free(Q.front);
    Q.front = Q.rear;
  }
  Q.front = Q.rear = NULL;
}

bool IsEmpty_LQ(LQueue Q) {
  /* ��QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE */
  if (Q.front == NULL) return true;
  else return false;
}

int QueueLength_LQ(LQueue Q) {
  /* ����еĳ��� */
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
  /* �����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR */

  if (Q.front == Q.rear) return ERROR;
  e = Q.front->data;
  return OK;
}

void EnQueue_LQ(LQueue& Q, QElemType e) {
  /* ����Ԫ��eΪQ���µĶ�βԪ�� */
  QueuePtr p = (QueuePtr)malloc(sizeof(LQNode));

  if (!p) /* �洢����ʧ�� */
    exit(OVERFLOW);
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
  /* �����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR */
  QueuePtr p;

  if (IsEmpty_LQ(Q)) return ERROR;

  p       = Q.front; /* ָ��ͷ��� */
  e       = p->data;
  Q.front = p->next; /* ժ��ͷ�ڵ� */

  if (Q.rear == p) Q.rear = NULL;
  free(p);
  return OK;
}

void Traverse_LQ(LQueue Q, void (*vi)(QElemType)) {
  /* �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi() */
  QueuePtr p;

  p = Q.front;

  while (p)
  {
    vi(p->data);
    p = p->next;
  }
  printf("\n");
}
