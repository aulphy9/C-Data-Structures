#ifndef GRAPH_H
#define GRAPH_H

#define INFINITY 99999

typedef struct adjnode  {
    int nid;
    int weight;
    struct adjnode *next;
} ADJNODE;

typedef struct gnode  {
    int nid;
    ADJNODE *neighbor; 
} GNODE;

typedef struct graph {
    int order; 
    int size;  
  GNODE **nodes; 
} GRAPH;

/* create and return a new adjacent list graph of order n */
GRAPH *new_graph(int n);

/* add a new edge (from, to, weight) to the graph passed by GRAPH *g, 
  if the edge (from, to) exists, update its weight.
*/
void add_edge(GRAPH *g, int from, int to, int weight);

/* return the weight of edge (from, to) if exists, 
 * otherwise return INFINITY
*/
int get_weight(GRAPH *g, int from, int to);

/* display the graph the proper format*/
void display_graph(GRAPH *g);

/* clean the graph by free all dynamically allocated memory */
void clean_graph(GRAPH **gp);

/* display node data in breadth-first-order using auxiliary queue */
void display_bforder(GRAPH *g, int start);

/* display node data in depth-first-order using auxiliary stack */
void display_dforder(GRAPH *g, int start); 

#endif