// your code signature

#include <stdio.h>
#include <stdlib.h> 
#include "edgelist.h"

/* create and return a new edge list graph*/
EDGELIST *new_edgelist() {
  EDGELIST *p = (EDGELIST*) malloc(sizeof(EDGELIST));
  p->size = 0; //setting initial size to 0
  p->start = NULL;
  p->end = NULL;
  return p;
}

/* add an new edge at the end of the linked list of edges*/
void add_edge_end(EDGELIST *g, int from, int to, int weight) {
  EDGE *new = (EDGE*) malloc(sizeof(EDGE)); //dynamically create new edge object
  new->to = to; //adding properties to new node
  new->from = from;
  new->weight = weight;
  new->next = NULL;
  if (g->size != 0){ //edge list isn't empty, pointing ends next to new edge
    g->end->next = new;
  }
  else{ //graph is empty, making new edge the start of list
    g->start = new;
  }
  g->size += 1;
  g->end = new;
}

/* add an new edge at the start of the linked list of edges*/
void add_edge_start(EDGELIST *g, int from, int to, int weight) {
  EDGE *new = (EDGE*) malloc(sizeof(EDGE)); //creating new edge and adding properties
  new->to = to;
  new->from = from;
  new->weight = weight;
  g->size++; //incrementing size
  new->next = NULL;
  if (g->start != NULL){ //graph isn't empty, setting new front
    new->next = g->start; //pointing new node to front of graph
  }
  else{ //graph is empty, setting new to end
    g->end = new; 
  }
  g->start = new;
}

/* get weight of the edge list graph*/
int weight_edgelist(EDGELIST *g) {
  EDGE *temp = (EDGE*) malloc(sizeof(EDGE));
  temp = g->start;
  int result = 0;
  while (temp != NULL){
    result += temp->weight;
    temp = temp->next;
  }
  return result;
}

void clean_edgelist(EDGELIST **gp) {
  EDGELIST *g = *gp;
  EDGE *temp, *p = g->start;
  while (p) {
    temp = p;
    p = p->next;
    free(temp);
  }
  free(g);
  *gp = NULL;
}

void display_edgelist(EDGELIST *g) {
  if (g == NULL) return;
  printf("size:%d\n", g->size);
  printf("(from to weight):");
  EDGE *p = g->start;
  while (p) {
    printf("(%d %d %d) ", p->from, p->to, p->weight);
    p = p->next;
  }
}