#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "stack.h"
#include "expression.h"

/*
 * auxiliary function 
*/
int get_priority(char op) {
  if (op == '/' || op == '*' || op == '%') 
    return 1;
  else if (op == '+' || op == '-')
    return 0;
  else 
    return -1;    
}

/*
 * auxiliary function 
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
  else 
    return 4;
}

/* 
 * convert infix expression in string to postfix expression represented by QUEUE and return the postfix expression queue. 
*/
QUEUE infix_to_postfix(char *infixstr) {
    char *p = infixstr;
    QUEUE queue = {0};
    STACK stack = {0};
    int sign = 1, num = 0;
    NODE *hold = {0};
    while (*p){
        if (*p >= '0' && *p <= '9'){
            num = *p-'0'; 
            while ((*(p+1) >= '0' && *(p+1) <= '9')){
                num = num*10 + *(p+1)-'0'; 
                p++;
            }
            enqueue(&queue, new_node(num, 0));
        }
        else if (*p == '('){
            push(&stack, new_node(*p, type(*p)));
        }
        else if (*p == ')'){
            while (stack.top && (hold = pop(&stack))->type != 2) {
				        enqueue(&queue, hold); 
			    }
        }
        else if (type(*p) == 1){
            while (stack.top && get_priority(*p) <= get_priority(stack.top->data)) {
				      enqueue(&queue, pop(&stack));
			    }
			    push(&stack, new_node(*p, type(*p)));
        }
        p++;
    }
    while (stack.top){
        enqueue(&queue, pop(&stack));
    }
    return queue;
}

/* 
 * evaluate and returns the value postfix expression passed by queue.
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
 * Evaluate and return the value of infix expression passed by string infixstr, 
 * using infix_to_postfix() and evaluate_postfix() functions.
*/
int evaluate_infix(char *infixstr) {
    QUEUE start = infix_to_postfix(infixstr);
    int result = evaluate_postfix(start);
    clean_queue(&start);
    return result;
}