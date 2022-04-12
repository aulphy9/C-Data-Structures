#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "myrecord_sllist.h"


void display(SLLIST *sllistp) {
    NODE *np = sllistp->start;
    printf("length:%d\n", sllistp->length);
    while (np != NULL) {
        printf("%s,%.1f\n", np->data.name, np->data.score);
        np = np->next;
    }
}

NODE *search(SLLIST *sllistp, char *name) {
	NODE *np = sllistp->start;
	while (np != NULL){
		if (strcmp(np->data.name, name) == 0)
			return np;
		np = np->next;
	}
	return np;
}

void insert(SLLIST *sllistp, char *name, float score) {
	NODE* p = (NODE *)malloc(sizeof(NODE));
	strcpy(p->data.name, name);
	p->data.score = score;
	p->next = NULL;
	NODE *prev = NULL;
	NODE *ptr = sllistp->start;
	while (ptr != NULL){
		if (strcmp(ptr->data.name, name) >= 0){
			break;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	if (prev == NULL){
		sllistp->start = p;
		p->next = ptr;
	}
	else{
		prev->next = p;
		p->next = ptr;
	}
  sllistp->length += 1;
}

/**
 * Delete a node of record matched by the name key from linked list.
 * @param @param SLLIST *sllistp provides the address of a singly linked list structure.
 * @param name  The key used to find the node for deletion.
 * @return 1 if deleted a matched node, 0 otherwise.
 */
int delete(SLLIST *sllistp, char *name) {
	NODE *prev = NULL;
  NODE *curr = sllistp->start;
  int found = 0;
  while (found == 0 && curr != NULL){ //looping until the end of the list or until we find matching node
    if (strcmp(curr->data.name, name) == 0){
      found = 1;
    }
    else{ //continue looping
      prev = curr;
      curr = curr->next;
    }
  }
  if (found == 1){ //deleting node
    if (prev == NULL){
      sllistp->start = sllistp->start->next;
    }
    else{
      prev->next = curr->next;
    }
  }
  return found;
}

void clean(SLLIST *sllistp) {
    NODE *temp, *np = sllistp->start;
    while (np != NULL) {
    temp = np;
    np = np->next;
      free(temp);
  }
  sllistp->start = NULL;
  sllistp->length = 0;
}



// you are allowed to refer or use the following functions

char letter_grade(float s){
  char r = 'F';
  if (s >= 90) r = 'S';
  else if (s >= 80) r = 'A';
  else if (s >= 70) r = 'B';
  else if (s >= 60) r = 'C';
  else if (s >= 50) r = 'D';
  else r = 'F';
  return r;
}

void select_sort(float a[], int left, int right)
{
  int i, j, k;
  float temp;
  for (i = left; i <= right; ++i) {
    k = i;
    for(j = i+1; j <= right; ++j) {
      if (a[j] < a[k]) {
        k = j;
      }
    }
    if (i != k) {
      temp = a[k];
      a[k] = a[i];
      a[i] = temp;
    }
  }
}

float median(SLLIST *sllistp)
{
  if (sllistp->start == NULL) return 0;
  NODE *np = sllistp->start;
  int i=0, n = sllistp->length;
  float a[n];   // create array for score float values for sorting
  while (np) {  // get score values from sllist
    a[i] = np->data.score;
    np = np->next;
    i++;
  }
  select_sort(a, 0, n-1);
  return (n % 2 == 1)? a[n/2] : (a[n/2-1] + a[n/2])/2 ;
}

STATS get_stats(SLLIST *sllistp) {
  int count = 0;
  float mean = 0;
  float stddev = 0;
  NODE *np = sllistp->start;
  while (np != NULL) {
    count++;
    mean += np->data.score;
    stddev += np->data.score * np->data.score ;
    np = np->next;
  }
  mean /= count;
  stddev = sqrt(stddev/count - mean*mean);

  STATS stats = {};
  stats.count = count;
  stats.mean = mean;
  stats.stddev = stddev;
  stats.median = median(sllistp);
  return stats;
}

int import_data(SLLIST *sllistp, char *filename) {
  char line[40], name[40];
  char *valuestr = NULL;
  char delimiters[] = ",";
  float score = 0;

  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error while opening the file.\n");
    return 0;
  }
  while (fgets(line, sizeof(line), fp) != NULL) {
    valuestr = strtok(line, delimiters);
    strcpy(name, valuestr);
    valuestr = strtok(NULL, delimiters);
    score = atof(valuestr);
        if (strlen(name)>0 && score >0 ) // validate data
      insert(sllistp, name, score);
  }
  fclose(fp);
  return sllistp->length;
}

STATS report_data(SLLIST *sllistp, char *filename) {
  NODE *np = sllistp->start;
  FILE *fp = fopen(filename, "w");
  while (np != NULL) {
    fprintf(fp, "%s,%c\n", np->data.name, letter_grade(np->data.score));
    np = np->next;
  }
  fclose(fp);

  return get_stats(sllistp);
}
