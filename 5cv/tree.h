#ifndef __TREE__
#define __TREE__

#define TRUE 1
#define FALSE 0

typedef struct thenode {
    int key;
    /* payload */
    struct thenode *left, *right;
} node;

int node_add(node **root , int key);
void node_dump(node *root);
void node_free(node **root);

#endif