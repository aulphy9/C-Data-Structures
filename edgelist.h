// your code signature

#ifndef EDGELIST_H
#define EDGELIST_H

// your code document
typedef struct edge {
  int from;
  int to;
  int weight;
  struct edge *next;
} EDGE;

// your code document
typedef struct edgelist {
  int size;    
  EDGE *start;
  EDGE *end;
} EDGELIST;


/* create and return a new edge list graph*/
EDGELIST *new_edgelist();

/* add an new edge at the end of the linked list of edges*/
void add_edge_end(EDGELIST *g, int from, int to, int weight);

/* add an new edge at the start of the linked list of edges*/
void add_edge_start(EDGELIST *g, int from, int to, int weight);

/* get weight of the edge list graph*/
int weight_edgelist(EDGELIST *g);

/* display edge list graph*/
void display_edgelist(EDGELIST *g);

/* clean the graph by free all dynamically allocated memory*/
void clean_edgelist(EDGELIST **gp);

#endif