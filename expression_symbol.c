#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression_symbol.h"

int get_priority(char op) {
  if (op == '/' || op == '*' || op == '%') 
    return 1;
  else if (op == '+' || op == '-')
    return 0;
  else 
    return -1;    
}

/* 
 * convert infix expression string to postfix expression queue, 
 * getting symbol values from the hash table
*/
QUEUE infix_to_postfix_symbol(char *infixstr,  HASHTABLE *ht) {
  char *p = infixstr;
  QUEUE queue = {0};
  STACK stack = {0};
  int num = 0;
  NODE *hold = {0};
  while (*p){
    char symbol[11] = {0};
    if (*p >= '0' && *p <= '9'){
      num = *p-'0'; 
      while ((*(p+1) >= '0' && *(p+1) <= '9')){
        num = num*10 + *(p+1)-'0'; 
        p++;
      }
      enqueue(&queue, new_node(num, 0));
    }
    else if (*p == ')'){
      while (stack.top && (hold = pop(&stack))->type != 2) {
        enqueue(&queue, hold); 
      }
    }
    else if (*p == '('){
      push(&stack, new_node(*p, type(*p)));
    }
    else if (type(*p) == 1){
      while (stack.top && get_priority(*p) <= get_priority(stack.top->data)) {
        enqueue(&queue, pop(&stack));
      } 
      push(&stack, new_node(*p, type(*p)));
    }
    else if (type(*p) == 4){
      strncat(symbol, p, 1); //find symbol
      while ((*(p + 1) >= 'a' && *(p + 1) <= 'z') || (*(p + 1) >= 'A' && *(p + 1) <= 'Z')) {
        strncat(symbol, (p + 1), 1);
        p++;
      }
      HSNODE *found = search(ht, symbol); //search the hash table from while loop result
      enqueue(&queue, new_node(found->value, 0));
    }
  p++;
  }
  while (stack.top){
    enqueue(&queue, pop(&stack));
  }
  return queue;
}

/*
 * evaluate symbolic infix expression, 
 * call queue = infix_to_postfix_symbol(char *infixstr, HASHTABLE *ht); 
 * then call evaluate_postfix(QUEUE queue);
*/ 
int evaluate_infix_symbol(char *infixstr,  HASHTABLE *ht) {
  QUEUE q = infix_to_postfix_symbol(infixstr, ht);
  int final = evaluate_postfix(q);
  return final;
}

/*
 * the same as A6Q3
*/
int evaluate_postfix(QUEUE queue) {
  NODE *p = queue.front;
    STACK stack = {0}; // auxilliary stack for postfix evaluation
    int type = 0;
    while (p) { // traversal the queue linked list
        type = p->type;
        if (type == 0) { // operant
            push(&stack, new_node(p->data, 0));
        }
        else if (type==1){ // operator
            NODE *B = pop(&stack);
			      NODE *A = pop(&stack);
			      NODE *C = new_node(0, 0);
            switch (p->data){
              case '/':
                C->data = A->data / B->data;
                break;
              case '*':
                C->data = A->data * B->data;
                break;
              case '-':
                C->data = A->data - B->data;
                break;
              case '+':
                C->data = A->data + B->data;
                break;
            }
			      push(&stack, C);
        }
        p = p->next;
    }
    int final = 0;
    if (stack.top != NULL){
      final = stack.top->data;
    }
    clean_stack(&stack);
    return final;
}

/*
 * helper function to determine the type of character c is 
*/
int type(char c) {
  if (c >= '0' &&  c <= '9' )
     return 0;
  else if (c == '/' || c == '*' || c == '%' || c == '+' || c == '-')

    return 1;
  else if (c == '(')
    return 2;
  else if ( c == ')')
    return 3;  
  else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    return 4;
  else 
    return 5;
}

