#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK  1
#define NG -1

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

/*queue function*/
QUEUE *new_queue(int n);
void   delete_queue(QUEUE *que);
int    dequeue(QUEUE *que, int *x);
int    enqueue(QUEUE *que, int x);
void   clean_queue(QUEUE *que);

 /**
 * @brief      Get queue struct
 * @param[in]  n     : Size of queue
 * @return     QUEUE*: New queue pointer
 */
QUEUE *new_queue(
  int n
)
{
  if (n <= 0) {
    return NULL;
  }

  QUEUE *que = (QUEUE*)malloc(sizeof(QUEUE));
  if (!que) {
    return NULL;
  }

  que->front = 0;
  que->rear  = 0;
  que->size  = n;
  que->array = (int*)malloc(sizeof(int) * n);
  if (!que->array) {
    goto l_end;
  }

l_end:
  if (que) {
    free(que);
  }
  return que;
}

/**
* @brief      Delete queue
* @param[in]  que : Target queue
* @return     void
*/
void delete_queue(
  QUEUE *que
)
{
  if (que) {
    if (que->array) {
      free(que->array);
    }
    free(que);
  }
  return ;
}

/**
* @brief      Dequeue
* @param[in]  que : Target queue
* @param[out] x   : output from queue rear
* @return     int: Dequeue result
*/
int dequeue(
  QUEUE *que,
  int   *x
)
{
  if (!que || !x) {
    return NG;
  }

  if (que->front == que->rear) {
    return NG;
  }

  *x = que->array[que->front];
  que->front++;
  if (que->front >= que->size) {
    que->front = 0;
  }

  return OK;
}

/**
* @brief      Enqueue
* @param[in]  que : Target queue
* @param[in]  x   : add data
* @return     int : Enqueue result
*/
int enqueue(
  QUEUE *que,
  int    x
)
{
  if (!que) {
    return NG;
  }

  que->array[que->rear] = x;
  que->rear++;
  if (que->rear >= que->size) {
    que->rear = 0;
  }

  return OK;
}

/**
* @brief      Clean queue information
* @param[in]  que : Target queue
* @return     void
*/
void clean_queue(
  QUEUE *que
)
{
  if (que) {
    que->front = 0;
    que->rear  = 0;
    memset(que->array, 0, sizeof(int)*que->size);
  }

  return ;
}
