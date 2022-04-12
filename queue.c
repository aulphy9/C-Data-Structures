#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"

/* 
 * enqueue a NODE *np and maintain the length property of the Queue. 
*/
void enqueue(QUEUE *qp, NODE *np) {
    if (qp->length == 0){ //queue is empty, adding and updating front/rear
        qp->front = np;
        qp->rear = np;
        qp->rear->next = NULL;
    }
    else{ //queue is not empty, linking and updating rear
        qp->rear->next = np;
        qp->rear = np;
    }
    qp->length++; //incrementing length
}  

/* 
 * dequeue and return the pointer of the removed NODE, maintain length property.
*/
NODE *dequeue(QUEUE *qp) {
    if (qp->length != 0){ //making sure we aren't trying to remove from an empty queue
        NODE *result = qp->front; //take from front (first in first out)
        if (qp->length == 1){ //special case
            qp->front = NULL; //making front and rear null as queue is now empty
            qp->rear = NULL;
        }
        else{ //generic case
            qp->front = qp->front->next;
        }
        qp->length--; //decrementing length
        return result;
    }
}

/* 
 * delete and free all nodes of the queue.  
*/
void clean_queue(QUEUE *qp) {
    if (qp->length != 0){ //making sure queue isn't empty
        NODE *start = qp->front;
        clean(&start);
        qp->length = 0;
    }
}  