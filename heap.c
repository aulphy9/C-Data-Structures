#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

/* 
 * create and return a heap data structure 
 * to instantiate and return the pointer of the above heap structure,  size=0, capacity=4, allocate memory space to hold array of 
 * elements of the capacity and store pointer in data
*/
HEAP *new_heap(int capacity)
{
    HEAP *hp = (HEAP*)malloc(sizeof(HEAP));
    hp->capacity = capacity;
    hp->size = 0;
    hp->hna = (HNODE*)malloc(sizeof(HNODE) * capacity);
    return hp;
}

/* 
 * this inserts the given node data a into the heap; When the heap size 
 * is equal to the capacity, the inserting process needs first to expand 
 * data array by doubling its amount. This may need to copy the data of 
 * old array to new array, secondly insert the new data element into the 
 * end of the array and update size.
*/
void insert(HEAP *heap, HNODE new_node)
{
    if (heap->size == heap->capacity){ //heap is at max capacity, resizing and inserting
        heap->capacity *= 2;
        HNODE *temp = realloc(heap->hna, sizeof(HNODE) * heap->capacity);
        if (temp){
            heap->hna = temp;
        }
        else{
            temp = malloc(sizeof(HNODE) * heap->capacity);
            if (temp){
                memcpy(temp, heap->hna, sizeof(HNODE) * heap->size);
                free(heap->hna);
                heap->hna = temp;
            }
            else{
                printf("array size failed\n");
            }
        }
        heap->hna[heap->size] = new_node;
    }
    else{ //performing regular insertion
        heap->hna[heap->size] = new_node;
    }
    heap->size++; //incrementing size
    int curr_i = heap->size - 1; //heapifying to maintain min heap properties
    int parent = (curr_i - 1) / 2;
    while (cmp(heap->hna[curr_i].key, heap->hna[parent].key) == -1){
        HNODE curr = heap->hna[curr_i];
        heap->hna[curr_i] = heap->hna[parent];
        heap->hna[parent] = curr;
        curr_i = parent;
        parent = (curr_i - 1)/ 2;
    }
}

/* 
 * this gets the data element of minimum key and delete the element from the 
 * binary heap. When the heap size  is no more than a quarter of the capacity, it 
 * needs to shrink the data array by half to free the unused memory space. 
*/
HNODE extract_min(HEAP *heap){
    HNODE min = *(heap->hna); //getting min node and freeing it
    heap->hna[0] = heap->hna[heap->size - 1];
    free(heap->hna + heap->size - 1);
    heapify_down(heap, 0); //heapifying down
    if (heap->size == (heap->capacity)/2){ //resizing heap array
        heap->capacity = heap->capacity / 2;
        HNODE *hold = realloc(heap->hna, sizeof(HNODE)*heap->capacity);
        if (hold != NULL){
            heap->hna = hold;
        }
        else{
            hold = malloc(sizeof(HNODE)*heap->capacity);
            if (hold != NULL){
                memcpy(hold, heap->hna, sizeof(HNODE)*heap->size);
                free(heap->hna);
                heap->hna = hold;
            }
            else{
                printf("Failed to resize array\n");
            }
        }
    }
    heap->size -= 1;
    return min;
}

/* 
 * this changes the key of given element at given index position to 
 * new_key, and return the index of updated key node 
*/
int change_key(HEAP *heap, int index, KEYTYPE new_key){
    int new_index;
    DATA initial_data = heap->hna[index].data; //storing initial data to find index after changing the key
    if (heap->size != 0 && index <= heap->size){ //we are able to insert into heap
        heap->hna[index].key = new_key; //updating key
        if (cmp(new_key, heap->hna[index].key) == -1){ //new key is less than old key, moving it up in heap
            heapify_up(heap, index);
        }
        if (cmp(new_key, heap->hna[index].key) == 1){ //new key is greater than old key, moving it down in heap
            heapify_down(heap, index);
        }
        new_index = find_index_data(heap, initial_data); //getting new index of moved key, if required 
    }
    return new_index;
}
/* this finds and returns the first index of the heap node matching given data */
int find_index_data(HEAP *heap, DATA data){
    int found = 0, position = 0, result;
    while (position < heap->size && found == 0){
        if (heap->hna[position].data == data){ //found value
            result = position;
            found = 1;
        }
        else{ //not found, incrementing index
            position++;
        }
    }
    return result;
}

/*
 * compare two key values a and b, return -1 if a<b, 0 if a=b, 1 if
 * a>b  
*/
int cmp(KEYTYPE a, KEYTYPE b) {
    if (a < b){
        return -1;
    }
    else if (a > b){
        return 1;
    }
    else{
        return 0;
    }
}

/* helper function to swap nodes in heap */
void heap_swap(HNODE a, HNODE b){
	HNODE  temp;
	temp = a;
	a   = b;
	b   = temp;
	return;
}

/* heapify up helper function for minimum heap */
void heapify_up(HEAP *heap, int i){
    int parent_i = (i-1)/2; //getting parent index
    if (i && heap->hna[parent_i].key > heap->hna[i].key){ //violates heap property, swapping node
        heap_swap(heap->hna[i], heap->hna[parent_i]);
        heapify_up(heap, parent_i); //call heapify up to recurse up tree
    }
}

/* heapify down helper function for minimum heap */
void heapify_down(HEAP *heap, int i){
    int left = 2*i + 1; //getting left and right child indices
    int right = 2*i + 2;
    int min = i;
    if (left < heap->size && heap->hna[left].key < heap->hna[i].key){
        min = left;
    }
    if (right < heap->size && heap->hna[right].key < heap->hna[min].key){
        min = right;
    }
    if (min != i){
        heap_swap(heap->hna[i], heap->hna[min]);
        heapify_down(heap, min);
    }
}
