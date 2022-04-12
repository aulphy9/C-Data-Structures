// your code signature

#include <stdio.h>
#include <stdlib.h> 
#include "heap.h"
#include "algorithm.h"

/* Compute and return MST by Prim's algorithm using priority queue (min-heap) 
 * @param g     - graph by reference
 * @param start - the root node of MST
 * @return      - pointer of edge list of MST
*/ 
EDGELIST *mst_prim(GRAPH *g, int start) {
    if (g == NULL) return NULL;
    int i, heapindex, u, n = g->order, T[n], parent[n];
    for (i = 0; i < n; i++) T[i] = 0;
    for (i = 0; i < n; i++) parent[i] = -1;

    HNODE hn;
    HEAP *h = new_heap(4);
    T[start] = 1;

    ADJNODE *temp = g->nodes[start]->neighbor;
    while (temp){
        hn.key = temp->weight;
        hn.data = temp->nid;
        insert(h, hn);
        parent[temp->nid] = start;
        temp = temp->next;
    }

    EDGELIST *mst = new_edgelist();
    while (h->size > 0){
        hn = extract_min(h);
        i = hn.data;
        T[i] = 1;
        add_edge_end(mst, parent[i], i, hn.key);
        temp = g->nodes[i]->neighbor;
        while (temp){
            heapindex = find_data_index(h, temp->nid);
            if (heapindex >= 0){
                if (T[temp->nid] == 0 && temp->weight < h->hna[heapindex].key){
                    change_key(h, heapindex, temp->weight);
                    parent[temp->nid] = i;
                }
            } else{
                if (T[temp->nid] == 0){
                    hn.key = temp->weight;
                    hn.data = temp->nid;
                    insert(h, hn);
                    parent[temp->nid] = i;
                }
            }
            temp = temp->next;
        }
    }
    return mst;
}

/* 
 * Compute shortest path tree as edge list by Dijkstra's algorithm using priority queue (min-heap) 
 * @param g     - graph by reference
 * @param start - the root node of shortest path tree
 * @return      - pointer of edge list of shortest path tree 
*/ 
EDGELIST *spt_dijkstra(GRAPH *g, int start) {
    if (!g) return NULL;
    EDGELIST *spt = new_edgelist();
    int i, heapindex, u, n = g->order, T[n], parent[n], label[n];
    HNODE hn;
    for (i = 0; i < n; i++) { T[i] = 0; label[i] = 9999; }
    HEAP *h = new_heap(4);
    ADJNODE *temp = g->nodes[start]->neighbor;
    label[start] = 0;
    T[start] = 1;
    while (temp){
        hn.key = temp->weight + label[start];
        hn.data = temp->nid; 
        insert(h, hn); 
        parent[temp->nid] = start; 
        temp = temp->next;
    }
    while (h->size > 0){
        hn = extract_min(h);
        i = hn.data; 
        T[i] = 1; 
        label[i] = hn.key;
        add_edge_end(spt, parent[i], i, label[i] - label[parent[i]]);
        temp = g->nodes[i]->neighbor;
        while (temp){
            heapindex = find_data_index(h, temp->nid);
            if (heapindex >= 0){
                if (T[temp->nid] == 0 && temp->weight + label[i] < h->hna[heapindex].key){
                    change_key(h, heapindex, temp->weight + label[i]);
                    parent[temp->nid] = i;
                }
            } else{
                if (T[temp->nid] == 0){
                    hn.key = temp->weight + label[i];
                    hn.data = temp->nid;
                    insert(h, hn);
                    parent[temp->nid] = i;
                }
            }
            temp = temp->next;
        }
    }
    return spt;
}

/* 
 * Compute shortest path as edge list by Dijkstra's algorithm using priority queue (min-heap) 
 * @param g     - graph by reference
 * @param start - the start node of shortest path
 * @param end   - the end node of shortest path
 * @return      - pointer of edge list of the shortest path
*/ 
EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
    if (!g) return NULL;
    EDGELIST *spt = new_edgelist();
    int i, heapindex, u, n = g->order, T[n], parent[n], label[n], found = 0;
    HNODE hn;
    for (i = 0; i < n; i++) { T[i] = 0; label[i] = 9999; }
    HEAP *h = new_heap(4);
    ADJNODE *temp = g->nodes[start]->neighbor;
    label[start] = 0;
    T[start] = 1;
    while (temp){
        hn.key = temp->weight + label[start];
        hn.data = temp->nid; 
        insert(h, hn); 
        parent[temp->nid] = start; 
        temp = temp->next;
    }
    while (h->size > 0 && found == 0){
        hn = extract_min(h);
        i = hn.data;
        if (hn.key == end){
            found = 1;
        } 
        T[i] = 1; 
        label[i] = hn.key;
        add_edge_end(spt, parent[i], i, label[i] - label[parent[i]]);
        temp = g->nodes[i]->neighbor;
        while (temp){
            heapindex = find_data_index(h, temp->nid);
            if (heapindex >= 0){
                if (T[temp->nid] == 0 && temp->weight + label[i] < h->hna[heapindex].key){
                    change_key(h, heapindex, temp->weight + label[i]);
                    parent[temp->nid] = i;
                }
            } else{
                if (T[temp->nid] == 0){
                    hn.key = temp->weight + label[i];
                    hn.data = temp->nid;
                    insert(h, hn);
                    parent[temp->nid] = i;
                }
            }
            temp = temp->next;
        }
    }
    EDGELIST *sp = new_edgelist();
    i = end;
    while (1){
        if (i == start) break;
        add_edge_start(sp, parent[i], i, label[i] - label[parent[i]]);
        i = parent[i];
    }
    return sp;
}