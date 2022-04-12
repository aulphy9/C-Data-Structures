// your code signature

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "hash.h"

extern int htsize;

extern int htsize;

int hash(char* word) {
  unsigned int hash = 0, i;
  for (i = 0; word[i] != '\0'; i++) {
    hash = 31 * hash + word[i];
  }
  return hash % htsize;
}

/* create dynamically a hash node and set 
key and value and return the point */
HSNODE *new_hashnode(char *key, int value) {
  HSNODE *new_hashnode = (HSNODE*)malloc(sizeof(HSNODE)); //allocating memory for new node
  new_hashnode->value = value; //setting value
  strcpy(new_hashnode->key, key); //copying key value
  new_hashnode->next = NULL; //setting next to null currently
  return new_hashnode;

}

/* create dynamically a chained hash table of the given size */
HASHTABLE *new_hashtable(int size) {
  HASHTABLE *ht = (HASHTABLE*)malloc(sizeof(HASHTABLE));
  ht->hna = (HSNODE**)malloc(sizeof(HSNODE**) * size);
  for (int i = 0; i < size; i++){
    *(ht->hna + i) = NULL;
  }
  ht->size = size;
  ht->count = 0;
  return ht;
}

/* search the hash table and return the pointer of found hashnode */
HSNODE *search(HASHTABLE *ht, char *key) { 
  int i = hash(key);
  HSNODE *p = ht->hna[i];
  int found = 0;
  while (p != NULL && found == 0){ //looping until we hit end of list, or find value
    if (strcmp(key, p->key) == 0){ //found node, stopping loop
      found = 1;
    }
    else{ //node doesnt match, going to next 
      p = p->next;
    }
  }
  return p;
}

/* insert hashnode np to hash table
 * when the named hashnode exists, update the hashnode's value by np->value, return 0;
 * otherwise insert into the hash table, return 1 
*/
int insert(HASHTABLE *ht, HSNODE *np) {
  char *k = np->key; 
  int i = hash(k); //getting index position
  HSNODE *p = ht->hna[i]; //setting up new and prev pointer
  HSNODE *prev = NULL;
  if (p == NULL){ //current index position is empty
    ht->hna[i] = np; //putting new node in proper index
  }
  else if (strcmp(k, p->key) == 0){ //key at index is equivalent
    p->value = np->value; //copying value, returning node
    free(np);
    return 0;
  }
  else{ //looping to proper index, inserting there
    while (p != NULL && strcmp(k, p->key) > 0){
      prev = p;
      p = p->next;
    }
    if (prev == NULL){
      ht->hna[i] = np;
    }
    else{
      prev->next = np;
    }
    np->next = p;
  }
  ht->count += 1;
  return 1;
}
/* 
 * delete hashnode by key. If the named hash node exists, 
 * delete it and return 1; 
 * otherwise return 0
*/
int delete(HASHTABLE *ht, char *key) {
  int i = hash(key);
  int j = 0;
  HSNODE *p = ht->hna[i], *pp = NULL;
  if (p != NULL){
    while (p && strcmp(key, p->key) > 0){
      pp = p;
      p = p->next;
      j++;
    }
    if (p && strcmp(key, p->key) == 0){
      if (pp)
        pp->next = p->next;
      else
        ht->hna[i] = p->next;
      free(p);
      ht->count--;
      return 1;
    }
  }
  return 0;
}


void clean_hash(HASHTABLE **htp) {
  if (*htp == NULL) return;
  HASHTABLE *ht = *htp;
  HSNODE *sp = ht->hna[0], *p, *temp;
  int i;
  for (i = 0; i < ht->size; i++) {
    p = ht->hna[i];
    while (p) {
      temp = p;  
      p = p->next;
      free(temp);
    }
    ht->hna[i] = NULL;
  }
  free(ht->hna);
  ht->hna = NULL;
  *htp = NULL;
}