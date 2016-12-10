#include "../vendor/miniunit.h"

#include <cstdlib>

#ifndef QUEUE_H
# define QUEUE_H

typedef int QElemType;

typedef struct LQNode {
  QElemType      data;
  struct LQNode *next;
} LQNode, *QueuePtr;                       // ���ͽ��ָ������

typedef struct {
  QueuePtr front;                          // ��ͷָ��
  QueuePtr rear;                           // ��βָ��
} LQueue;                                  // ����������

void   InitQueue_LQ(LQueue& Q);            /* ����һ���ն���Q */

void   DestroyQueue_LQ(LQueue& Q);         /* ���ٶ���Q(���ۿշ����) */

bool   IsEmpty_LQ(LQueue Q);               /* ��QΪ�ն��У��򷵻� true�����򷵻� false */

int    QueueLength_LQ(LQueue Q);           /* ����еĳ��� */

Status GetHead_LQ(LQueue     Q,
                  QElemType& e);           /*
                                              �����в��գ�����e����Q�Ķ�ͷԪ�أ�������OK�����򷵻�ERROR*/

void   EnQueue_LQ(LQueue  & Q,
                  QElemType e);            /* ����Ԫ��eΪQ���µĶ�βԪ�� */

Status DeQueue_LQ(LQueue   & Q,
                  QElemType& e);           /*
                                              �����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
                                            */

void   Traverse_LQ(LQueue Q,
                   void (*vi)(QElemType)); /*
                                              �Ӷ�ͷ����β���ζԶ���Q��ÿ��Ԫ�ص��ú���vi()
                                            */
#endif /* ifndef QUEUE_H */
