#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

#define TRUE  1
#define FALSE 0

int checkDuplicate(
  Node *head,
  Node *target
)
{
  Node *tmp = head;

  while (tmp != target && tmp != NULL) {
    if (tmp->data == target->data) {
      return TRUE;
    }
    tmp = tmp->next;
  }

  return FALSE;
}

Node* removeDuplicates(Node *head){
  Node *tmp = head;
  Node *pre = head;
  while(tmp->next) {
    tmp = tmp->next;

    if (checkDuplicate(head, tmp)) {
      pre->next = tmp->next;
    }
    else {
      pre = tmp;
    }
  }
  return head;
}

Node* insert(Node *head,int data)
{
  Node *p = (Node*)malloc(sizeof(Node));
  p->data = data;
  p->next=NULL;

  if(head==NULL){
   head=p;

  }
  else if(head->next==NULL)
  {
      head->next=p;

  }
  else{
  Node *start=head;
  while(start->next!=NULL)
    start=start->next;

  start->next=p;

  }
      return head;
}
void display(Node *head)
{
	Node *start=head;
	while(start)
	{
		printf("%d ",start->data);
		start=start->next;
	}
}
int main()
{
	int T,data;
    scanf("%d",&T);
    Node *head=NULL;
    while(T-->0){
        scanf("%d",&data);
        head=insert(head,data);
    }
    head=removeDuplicates(head);
	display(head);

}
