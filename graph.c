// your code signature

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h" 
#include "graph.h"

/* create and return a new adjacent list graph of order n */
GRAPH *new_graph(int order) {
    GRAPH *p = malloc(sizeof(GRAPH)); //create a graph object in heap region
    p->size = 0; //set order and size
    p->order = order;
    p->nodes = malloc(order * sizeof(GNODE*)); //create array of GNODE pointers 
    for (int i = 0; i < order; i++){
        p->nodes[i] = malloc(sizeof(GNODE)); //create a GNOGE object
        p->nodes[i]->nid = i; //set node id to be i
        p->nodes[i]->neighbor = NULL; //Initialize neighbor linked list
    }
    return p;
}

/* add a new edge (from, to, weight) to the graph passed by GRAPH *g, 
  if the edge (from, to) exists, update its weight.
*/
void add_edge(GRAPH *g, int from, int to, int weight) {
    GNODE *from_n = g->nodes[from];
    ADJNODE *adj = from_n->neighbor;
    ADJNODE *prev_n;
    int adjac = 0, has_n = 0;
    if (adj != NULL){
        has_n = 1;
    }
    while (adjac == 0 && adj != NULL){
        if (adj->nid == to){
            adjac = 1;
            adj->weight = weight;
        }
        else{
            prev_n = adj;
            adj = adj->next;
        }
    }
    if (adjac == 0){ //nodes aren't adjacent, handling appropriately
        ADJNODE *new_ad = (ADJNODE*) malloc(sizeof(ADJNODE));
        new_ad->weight = weight;
        new_ad->nid = to;
        new_ad->next = NULL;
        if (has_n == 1){
            prev_n->next = new_ad;
        }
        else{
            from_n->neighbor = new_ad;
        }
        g->size += 1;
    }

}

/* display node data in breadth-first-order using auxiliary queue */
void display_bforder(GRAPH *g, int start) {
    if (g == NULL) return;
    int n = g->order, visited[n], i;
    for (i=0; i<n;i++) visited[i] = 0;
    // bread-first traversal algorithm, similar to the A7Q1 iterative_bf_search()
    QUEUE queue = {0};
    GNODE *gnp = NULL;
    ADJNODE *anp = NULL;
    enqueue(&queue, g->nodes[start]);
    visited[start] = 1;
    while (queue.front) {
        gnp = (GNODE*) dequeue(&queue);
        printf("%d ", gnp->nid);
        anp = gnp->neighbor;
        while (anp){
            i = anp->nid;
            if (visited[i] == 0){
                enqueue(&queue, g->nodes[i]);
                visited[i] = 1;
            }
            anp = anp->next;
        }
    }
    clean_queue(&queue);
}

/* display node data in depth-first-order using auxiliary stack */
void display_dforder(GRAPH *g, int start) {
    if (g == NULL) return;
    int n = g->order, visited[n], i;
    for (i=0; i<n;i++) visited[i] = 0;
    // depth-first traversal algorithm, similar to the A7Q1 iterative_bf_search()
    STACK stack = {0};
    GNODE *gnp = NULL;
    ADJNODE *anp = NULL;
    push(&stack, g->nodes[start]);
    visited[start] = 1;
    while ((gnp = peek(&stack))) {
        printf("%d ", gnp->nid);
        pop(&stack);
        anp = gnp->neighbor;
        while (anp){
            i = anp->nid;
            if (visited[i] == 0){
                push(&stack, g->nodes[i]);
                visited[i] = 1;
            }
            anp = anp->next;
        }
    }
    clean_stack(&stack);
}

/* return the weight of edge (from, to) if exists, 
 * otherwise return INFINITY
*/
int get_weight(GRAPH *g, int from, int to) {
  ADJNODE *p = g->nodes[from]->neighbor;
  int result = INFINITY;
  while (p) {
    if (p->nid == to) {
        result = p->weight;
        break;
    }
    p = p->next;
  }
  return result;
}

/* clean the graph by free all dynamically allocated memory */
void clean_graph(GRAPH **gp) {
  int i;
  GRAPH *g = *gp;
  ADJNODE *temp, *ptr;
  for (i = 0; i < g->order; i++) {
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      temp = ptr;
      ptr = ptr->next;
      free(temp);
    }
    free(g->nodes[i]);
  }
  free(g->nodes);
  free(g);
  *gp = NULL;
}

/* display the graph the proper format*/
void display_graph(GRAPH *g) {
  if (g == NULL) return;
  printf("order:%d\n", g->order);
  printf("size:%d\n", g->size);
  printf("from:(to weight)");
  int i;
  ADJNODE *ptr;
  for (i = 0; i < g->order; i++) {
    printf("\n%d:", g->nodes[i]->nid);
    ptr = g->nodes[i]->neighbor;
    while (ptr != NULL) {
      printf("(%d %d) ", ptr->nid, ptr->weight);
      ptr = ptr->next;
    }
  }
}