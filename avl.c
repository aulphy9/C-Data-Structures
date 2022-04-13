// your program signature

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "avl.h"

// help functions
TNODE *extract_smallest_node(TNODE **rootp);

int height(TNODE *np)
{
    int result = 0;
    if (np != NULL){ //node isn't null, returning height
        result = np->height;
    }
    return result;
}

static void update_height(TNODE *node)
//===========================================
{
	int left_height;
	int right_height;

	left_height = height(node->left);
	right_height = height(node->right);

	if (left_height >= right_height) {
		node->height = left_height + 1;
	} else {
		node->height = right_height + 1;
	}
	return;
}

int balance_factor(TNODE* np) 
{
    if (np != NULL){
      return (height(np->left) - height(np->right));
    }
    else{
      return 0;
    }
}

int is_avl(TNODE *root) 
{
    int is_avl(TNODE *root);
    if (root == NULL){
        return 1;
    }
    else{
        int bf = balance_factor(root);
        if (bf > 1 || bf < -1){
            return 0;
        }
        else if (is_avl(root->left) == 0){
            return 0;
        }
        else if (is_avl(root->right) == 0){
            return 0;
        }
        return 1;
    }
}

TNODE *rotate_right(TNODE *y)
{
    TNODE *t1 = y->left;
    TNODE *t2 = t1->right;
    t1->right = y;
    y->left = t2;
    update_height(y);
    update_height(t1);
}

TNODE *rotate_left(TNODE *x)
{
    TNODE *t1 = x->right;
    TNODE *t2 = t1->left;
    t1->left = x;
    x->right = t2;
    update_height(x);
    update_height(t1);
}

void insert(TNODE **rootp, char *name, float score) 
// create the new node
{
TNODE *np = (TNODE *) malloc(sizeof(TNODE));
if (np == NULL) return;
strcpy(np->data.name, name);
np->data.score = score;
np->height = 1;
np->left = NULL;
np->right = NULL;
// 1. Perform the normal BST insertion
if (*rootp == NULL) { *rootp = np; return; }
TNODE *root = *rootp;
int cmp = strcmp(name, root->data.name);
if (cmp == 0 ) return; // do nothing
else if (cmp < 0 ) insert(&root->left, name, score); // insert to left subtrree
else insert(&root->right, name, score); // insert to right subtree
// Rebalancing root
root->height = 1 + max(height(root->left), height(root->right));
int bf = balance_factor(root);
if (bf > 1) {
if (balance_factor(root->left) >=0 ) *rootp = rotate_right(root);
else {
root->left = rotate_left(root->left);
*rootp = rotate_right(root);
}
}
else if (bf < -1) {
if (balance_factor(root->right) <= 0 ) *rootp = rotate_left(root);
else {
root->right = rotate_right(root->right);
*rootp = rotate_left(root);
}
} }

void delete(TNODE **rootp, char *name)
{
  TNODE *root = *rootp;
  TNODE* np;

  if (root == NULL) return;

  if (strcmp(name, root->data.name) == 0) {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      *rootp = NULL;
    } else if (root->left != NULL && root->right == NULL) {
      np = root->left;
      free(root);
      *rootp = np;
    } else if (root->left == NULL && root->right != NULL) {
      np = root->right;
      free(root);
      *rootp = np;
    } else if (root->left != NULL && root->right != NULL) {
      np = extract_smallest_node(&root->right);
      np->left = root->left;
      np->right = root->right;
      free(root);
      *rootp = np;
    }
  } else {
    if (strcmp(name, root->data.name) < 0) {
      delete(&root->left, name);
    } else {
      delete(&root->right, name);
    }
  }

    // If the tree had only one node then return
  if (*rootp == NULL) return;

  root = *rootp;
  
  // Rebalancing root
  root->height = 1 + max(height(root->left), height(root->right));
  int bf = balance_factor(root);
  if (bf > 1) {
  if (balance_factor(root->left) >=0 ) *rootp = rotate_right(root);
  else {
  root->left = rotate_left(root->left);
  *rootp = rotate_right(root);
  }
  }
  else if (bf < -1) {
  if (balance_factor(root->right) <= 0 ) *rootp = rotate_left(root);
  else {
  root->right = rotate_right(root->right);
  *rootp = rotate_left(root);
}}

}



TNODE *extract_smallest_node(TNODE **rootp) {
  TNODE *tnp = *rootp;
  TNODE *parent = NULL;
  if (tnp == NULL) {
    return NULL;
  } else {
    while (tnp->left) {
      parent = tnp;
      tnp = tnp->left;
    }
    if (parent == NULL)
      *rootp = tnp->right;
    else
      parent->left = tnp->right;
    tnp->left = NULL;
    tnp->right = NULL;
    return tnp;
  }
}

// the following functions are from A7

// You are allowed to use the following functions
int max(int a, int b)
{
  return (a > b) ? a : b;
}

TNODE *search(TNODE *root, char *name) {
      while (root != NULL){
        if (strcmp(name, root->data.name) == 0){ //node is found
        return root;
      }
        else if (strcmp(name, root->data.name) < 0){
          root = root->left;
      }
        else{
          root = root->right;
      }
    }
    return NULL;
}

void clean_tree(TNODE **rootp) {
  if (*rootp) {
    TNODE *np = *rootp;
    if (np->left)
      clean_tree(&np->left);
    if (np->right)
      clean_tree(&np->right);
    free(np);
  }
  *rootp = NULL; ;
}