#include <stdio.h>
#include <stdlib.h> 
#include "dllist.h"

NODE *new_node(char data) {
    NODE *new = (NODE*) malloc(sizeof(NODE));
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

void insert_start(DLLIST *dllistp, NODE *np) {
    if (dllistp->start == NULL){ //list is empty
        np->prev = NULL;
        np->next = NULL;
        dllistp->start = np;
        dllistp->end = np;
    }
    else{
        np->prev = NULL;
        np->next = dllistp->start;
        dllistp->start->prev = np;
        dllistp->start = np;
    }
    dllistp->length += 1;
}

void insert_end(DLLIST *dllistp, NODE *np) {
    if (dllistp->start == NULL){ //list is empty
        np->prev = NULL;
        np->next = NULL;
        dllistp->start = np;
        dllistp->end = np;
    }
    else{ //list isn't empty, adding node to end
        np->prev = dllistp->end;
        dllistp->end->next = np;
        dllistp->end = np;
    }
    dllistp->length += 1;
}

void delete_start(DLLIST *dllistp) {
    if (dllistp->length != 0){ //making sure list isn't empty before deletion
        dllistp->start = dllistp->start->next;
        if (dllistp != NULL){
            dllistp->start->prev = NULL;
        }
      dllistp->length -= 1;
    }
}

void delete_end(DLLIST *dllistp) {
    if (dllistp->length != 0){ //making sure list isn't empty
        if (dllistp->start->next == NULL){ //only 1 node in list
            dllistp->start = NULL;
        }
        else{
            NODE *temp = dllistp->end;
            dllistp->end = dllistp->end->prev;
            dllistp->end->next = NULL;
            free(temp); 
        }
      dllistp->length -= 1;
    }
}

void display_forward(DLLIST *dllistp) {
  NODE *np = dllistp->start;
  while ( np != NULL) {
    printf("%c", np->data);
    np = np->next;
  }
}

void display_backward(DLLIST *dllistp) {
  NODE *np = dllistp->end;
  while ( np != NULL) {
    printf("%c", np->data);
    np = np->prev;
  }
}

void clean(DLLIST *dllistp) {
  NODE *temp, *np = dllistp->start;
  while (np != NULL) {
    temp = np;
    np = np->next;
      free(temp);
  }
  dllistp->start = NULL;
  dllistp->end = NULL;
  dllistp->length = 0;
}