#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

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

void insert(TNODE **rootp, char *name, float score) {
    RECORD new_record; //creating new record
    strcpy(new_record.name, name); //adding name
    new_record.score = score; //adding score
    TNODE *new_node = (TNODE*)malloc(sizeof(TNODE)); //creating new node and alllocating memory
    new_node->data = new_record;
    new_node->left = NULL, new_node->right = NULL;
    if (*rootp == NULL){
      *rootp = new_node;
    }
    else{
      TNODE *p = *rootp;
      while (1){
        if (strcmp(name, p->data.name) == 0){ //found a duplicate, breaking
          break;
        }
        else if (strcmp(name, p->data.name) < 0){
          if (p->left == NULL){
            p->left = new_node;
            break;
          }
          else{
            p = p->left;
          }
        }
        else{
          if (p->right == NULL){
            p->right = new_node;
            break;
          }
          else{
            p = p->right;
          }
        }
      }
    }
}

void delete(TNODE **rootp, char *name) {
    TNODE *p = *rootp, *parent = NULL, *child;
    while (p != NULL && strcmp(name, p->data.name) != 0){
      parent = p;
      p = (strcmp(name, p->data.name) < 0 ? p->left : p->right);
    }
    if (p != NULL){ //have found node to be deleted
      if (p->left == NULL){ //left child is null
        child = p->right;
      }
      else if (p->right == NULL){ //right child is null
        child = p->left;
      }
      else{ //both children aren't null
        child = extract_smallest_node(&p->right);
        child->right = p->right;
        child->left = p->left;
      }
      if (parent == NULL){
        *rootp = child;
      }
      else if (parent->left == p){
        parent->left = child;
      }
      else{
        parent->right = child;
      }
      free(p);
    }
}


/* auxiliary function for delete */
TNODE *extract_smallest_node(TNODE **rootp) {
  TNODE *p = *rootp, *parent = NULL;
  if (p) {
    while (p->left) {
      parent = p;
      p = p->left;
    }
    
    if (parent == NULL)
      *rootp = p->right;
    else
      parent->left = p->right;
    
    p->left = NULL;
    p->right = NULL;
  }
  
  return p;
}


// the following functions are given for testing, need to add to your program.
void clean_tree(TNODE **rootp) {
    TNODE *root = *rootp;
    if (root) {
        if (root->left)
            clean_tree(&root->left);
        if (root->right)
            clean_tree(&root->right);
        free(root);
    }
    *rootp = NULL;
}