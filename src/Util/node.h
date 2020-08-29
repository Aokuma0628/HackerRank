#ifndef _NODE_H
#define _NODE_H

/**
 * @struct NODE
 * @brief  node for binary tree
 */
typedef struct _node {
  char *key;
  void *data;
  struct _node *left;
  struct _node *right;
} NODE;

int   insert_node(NODE *node);
NODE *serch_node(char *key);
void  free_node(NODE *node);

#endif
