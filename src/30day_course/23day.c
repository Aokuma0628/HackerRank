#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
    struct Node* left;
    struct Node* right;
    int data;
}Node;
Node* newNode(int data){
    Node* node=(Node*)malloc(sizeof(Node));
    node->left=node->right=NULL;
    node->data=data;
    return node;
}

/**
 * @struct QUEUE
 * @brief  queue information
 */
typedef struct _queue {
  int front;
  int rear;
  int size;
  Node **array;
} QUEUE;

/*queue function*/
QUEUE *new_queue(int n);
void   delete_queue(QUEUE *que);
Node  *dequeue(QUEUE *que);
int    enqueue(QUEUE *que, Node *x);
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
  int    i    = 0;
  QUEUE *que  = (QUEUE*)malloc(sizeof(QUEUE));
  if (!que) {
    return NULL;
  }

  if (n <= 0) {
    return NULL;
  }

  que->front = 0;
  que->rear  = 0;
  que->size  = n;
  que->array = (Node**)malloc(sizeof(Node*) * n);
  if (!que->array) {
    goto l_end;
  }
  for (; i < n; i++) {
    que->array[i] = (Node*)malloc(sizeof(Node) * n);
    if (!que->array[i]) {
      goto l_end;
    }
  }

  return que;

l_end:
  if (que) {
    for (i = 0; i < n; i++) {
      if (que->array[i]) {
        free(que->array[i]);
      }
    }
    free(que->array);
    free(que);

  }
  return NULL;
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
  int i = 0;
  if (que) {
    if (que->array) {
      for (; i < que->size; i++) {
        if (que->array[i]) {
          free(que->array[i]);
        }
      }
      free(que->array);
    }
    free(que);
  }
  return ;
}

/**
* @brief      Dequeue
* @param[in]  que : Target queue
* @return     Node*: Dequeue result
*/
Node *dequeue(
  QUEUE *que
)
{
  Node *node = NULL;

  if (!que) {
    return NULL;
  }

  if (que->front == que->rear) {
    return NULL;
  }

  node = que->array[que->front];
  que->front++;
  if (que->front >= que->size) {
    que->front = 0;
  }

  return node;
}

/**
* @brief      Enqueue
* @param[in]  que : Target queue
* @param[in]  x   : add data
* @return     int : Enqueue result
*/
int enqueue(
  QUEUE *que,
  Node  *x
)
{
  if (!que) {
    return 0;
  }

  que->array[que->rear] = x;
  que->rear++;
  if (que->rear >= que->size) {
    que->rear = 0;
  }

  return 1;
}

void levelOrder(Node* root){
  Node *node = root;
  QUEUE *que = NULL;
  const int size = 10;

  if (!root) {
    return ;
  }

  que = new_queue(size);
  if (!que) {
    return ;
  }
  enqueue(que, root);

  while (node) {
    node = dequeue(que);
    if (!node) {
      break;
    }

    printf("%d ", node->data);

    if (node->left) {
      enqueue(que, node->left);
    }
    if (node->right) {
      enqueue(que, node->right);
    }
  }

  delete_queue(que);
  return ;
}


Node* insert(Node* root,int data){
    if(root==NULL)
        return newNode(data);
    else{
        Node* cur;
        if(data<=root->data){
            cur=insert(root->left,data);
            root->left=cur;
        }
        else{
            cur=insert(root->right,data);
            root->right=cur;
        }

    }
    return root;
}
int main(){
    Node* root=NULL;
    int T,data;
    scanf("%d",&T);
    while(T-->0){
        scanf("%d",&data);
        root=insert(root,data);
    }
    levelOrder(root);
    return 0;

}
