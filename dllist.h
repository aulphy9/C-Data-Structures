#ifndef DLLIST_H
#define DLLIST_H

typedef struct node {
  char data;
  struct node *prev;  
  struct node *next;
} NODE;

typedef struct dllist {
  int length;
  NODE *start;
  NODE *end;
} DLLIST;

NODE *new_node(char value);
void insert_start(DLLIST *dllistp, NODE *np);
void insert_end(DLLIST *dllistp, NODE *np);
void delete_start(DLLIST *dllistp);
void delete_end(DLLIST *dllistp);

void display_forward(DLLIST *dllistp);
void display_backward(DLLIST *dllistp);
void clean(DLLIST *dllistp);

#endif