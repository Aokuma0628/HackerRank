#include <stdio.h>
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

int countHeight(
  Node *node
)
{
  if (node->right) {
    return (countHeight(node->right) + 1);
  }
  if (node->left) {
    cnt++;
    return (cnt + countHeight(node->left, cnt));
  }
  return 0;
}

int getHeight(Node* root){
  const int init = 0;

  if (!root) {
    return -1;
  }

  int height = countHeight(root, init);
  int height_l = countHeight(root->left, init);

  if (height > height_l) {
    return height;
  }
  else {
    return height_l;
  }

  return 1;
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
    int height=getHeight(root);
    printf("%d",height);
    return 0;

}
