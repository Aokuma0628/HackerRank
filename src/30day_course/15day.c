#include <stdlib.h>
#include <stdio.h>


typedef struct Node
{
    int data;
    struct Node* next;
} Node;

/**
* @brief      insert Node
* @param[in]  head - head of node
* @param[in]  data -
* @return     Node* head pointer of node
*/
Node* insert(
  Node *head,
  int   data
)
{
    Node *tmp  = head;
    Node *node = (Node*)calloc(1, sizeof(Node));
    if (!node) {
      return NULL;
    }

    node->data = data;

    if (!head) {
      return node;
    }

    while(tmp->next) {
      tmp = tmp->next;
    }
    tmp->next = node;

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
  display(head);

}
