#include <stdio.h>
#include "stack.h"

/*
 * push NODE *np onto STACK *sp, and maintain the height property
 */ 
void push(STACK *sp, NODE *np) {
    if (sp->height == 0){ //empty stack
        sp->top = np;
    }
    else{ //non-empty stack
        np->next = sp->top; //pointing new node to current top
        sp->top = np; //updating top of stack
    }
    sp->height++; //updating height
}

/*
 * pop and return the pointer to the removed top node, maintain the height property.
 */ 
NODE *pop(STACK *sp) {
    if (sp->height != 0){ //making sure stack isn't empty
        NODE *top_s = sp->top; //getting top node
        if (sp->height == 1){ //special case, stack is empty after removal
            sp->top = NULL;
        }
        else{ //generic case
            sp->top = sp->top->next;
        }
        sp->height--;
        return top_s;
    }
}

/* 
 * delete and free all nodes of the queue.  
*/
void clean_stack(STACK *sp) {
    if (sp->top != NULL){ //making sure stack isn't empty
        NODE *start = sp->top;
        clean(&start);
        sp->height = 0; //resetting height
    }
}