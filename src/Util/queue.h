#ifndef _QUEUE_H
#define _QUEUE_H

/**
 * @struct QUEUE
 * @brief  queue information
 */
typedef struct _queue {
  int front;
  int rear;
  int size;
  int *array;
} QUEUE;

QUEUE *new_queue(int n);
void   delete_queue(QUEUE *que);
int    dequeue(QUEUE *que, int *x);
int    enqueue(QUEUE *que, int x);
void   clean_queue(QUEUE *que);

#endif
