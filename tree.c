#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"

TNODE *new_node(int value) {
  TNODE *np = (TNODE *) malloc(sizeof(TNODE));
  if (np == NULL) return NULL;
  np->data = value;
  np->left = NULL;
  np->right = NULL;
  return np;
}


TPROPS get_props(TNODE *root) {
    TPROPS r = {0}; //initalizaing properties object
    if (root == NULL){ //checking if tree is empty
        return r;
    }
    else{ //tree isn't empty
        TPROPS lp = get_props(root->left);
        TPROPS rp = get_props(root->right);
        if (lp.height > rp.height){ //updating height
            r.height = lp.height + 1;
        }
        else{
            r.height = rp.height + 1;
        }
        r.order = lp.order + rp.order + 1; //need sum of all orders
        return r;
    }

}

void display_preorder(TNODE *root) {
    if (root == NULL){
        return;
    }
    else{
        printf("%c ", root->data); //printing current node data
        display_preorder(root->left); //traverse left subtree
        display_preorder(root->right);
    }
}

void display_inorder(TNODE *root) {
    if (root == NULL){ //terminating function if node is null
        return;
    }
    else{
        display_inorder(root->left);
        printf("%c ", root->data);
        display_inorder(root->right);
    }
}

void display_postorder(TNODE *root) {
    if (root == NULL){ //terminating function if node is null
        return;
    }
    else{ //traversing tree
        display_postorder(root->left);
        display_postorder(root->right);
        printf("%c ", root->data);
    }
}

/* use auxiliary queue data structure for the algorithm  */
void display_bforder(TNODE *root) {
    QUEUE q = {0};
    TNODE *p = NULL;
    if (root != NULL){
        enqueue(&q, root);
        while (q.front){
            p = dequeue(&q);
            printf("%c ", p->data);
            if (p->left){
                enqueue(&q, p->left);
            }
            if (p->right){
                enqueue(&q,p->right);
            }
        }
        clean_queue(&q);
    } 
}

/* use auxiliary queue data structure for the algorithm  */
TNODE *iterative_bfs(TNODE *root, int val) {
    QUEUE q = {0};
    TNODE *r = NULL, *p = NULL;
    if (root != NULL){
        enqueue(&q, root);
        while (q.front){
            p = dequeue(&q);
            if (p->data == val){
                r = p;
                break;
            }
            if (p->left){
                enqueue(&q, p->left);
            }
            if (p->right){
                enqueue(&q,p->right);
            }
        }
        clean_queue(&q);
    }
    return r;
}

TNODE *iterative_dfs(TNODE *root, int val) {
    STACK s = {0};
    TNODE *r = NULL, *p = NULL;
    if (root != NULL){
        push(&s, root);
        while (s.top){
            p = peek(&s); //need to get top stack node here
            pop(&s); //got to here, can't get top stack node for some stupid ass reason
            if (p->data == val){
                r = p;
                break;
            }
            if (p->left){
                push(&s, p->left);
            }
            if (p->right){
                push(&s, p->right);
            }
        }
        clean_stack(&s);
    }
    return r;
}


// the following functions are given, need to add to your program.

void clean_tree(TNODE **rootp) {
  TNODE *p = *rootp;
  if (p) {
    if (p->left)
      clean_tree(&p->left);
    if (p->right)
      clean_tree(&p->right);
    free(p);
  }
  *rootp = NULL;
}

void insert_complete(TNODE **rootp, int val){
  if( *rootp == NULL) { 
    *rootp = new_node(val);
  } else {
    QUEUE queue = {0};
    TNODE *p;
    enqueue(&queue, *rootp);
    while(queue.front){
      p = dequeue(&queue);
      if(p->left == NULL){
        p->left = new_node(val);
        break;
      } else {
        enqueue(&queue, p->left);
      }
      
      if(p->right == NULL){
        p->right = new_node(val);
        break;
      } else  {
        enqueue(&queue, p->right);
      }
    }
  }
}