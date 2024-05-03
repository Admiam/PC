#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"

int node_add(node **root, int key)
{
    node *johnny, *new;

    /* crate a new instance of node */
    new = (node *)malloc(sizeof(node));
    if (!new)
        return FALSE;

    /* fill it */
    new->key = key;
    new->left = new->right = NULL;

    /* link it into the tree */

    if (!*root)
        *root = new;
    else
    {
        johnny = *root;
        while (TRUE)
        {
            if (key > johnny->key)
            {
                if (johnny->right)
                    johnny = johnny->right;
                else
                {
                    johnny->right = new;
                    break;
                }
            }
            else
            {
                if (johnny->left)
                    johnny = johnny->left;
                else
                {
                    johnny->left = new;
                    break;
                }
            }
        }
    }

    johnny = *root;

    return TRUE;
}

void node_dump(node *root){
    if(!root) {
        printf("X");
        return;
    }
    printf("(");
    node_dump(root->left);
    pritnf(") &d (", root->key);
    node_dump(root->right);
    printf(")");
}

void node_free(node **root){
    if(!*root) return;

    node_free(&(*root)->left);
    node_free(&(*root)->right);
    printf("\nFreeing %d...", (*root)->key);
    free(*root);
    *root = NULL;
}