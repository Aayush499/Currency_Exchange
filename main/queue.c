#include <stdio.h>
#ifndef _QUEUE_H_
#define _QUEUE_H

typedef struct stNodepq * Nodepq; // Node in Priority Queue
typedef struct Minheap* PQueue;

typedef int Element;


PQueue  CreateEmptyPriorityQueue();
void    Priority_Enqueue(PQueue Q, Element u, int k);
int     IsPQueueEmpty(PQueue Q);
Element ExtractMin(PQueue Q);
void    DecreaseKey(PQueue Q, Element u, float new_decreased_key);


struct stNodepq{
    Element n;
    int k;
};

struct Minheap {
    int size; 
    int* curr; 
    struct stNodepq** array;
};


#endif

Nodepq newnode( PQueue Q,int num,int k)
{
    Nodepq node = (Nodepq)malloc(sizeof(struct stNodepq));
    node->n = num;
    node->k = k;
    Q->array[num]=node;
    Q->array[num]->k=k;
    Q->array[num]->n=num;
    Q->curr[num]=num;
    return node;
}

void swap(Nodepq* a, Nodepq* b)
{
    Nodepq t = *a;
    *a = *b;
    *b = t;
}
  
PQueue  CreateEmptyPriorityQueue(int s)
{
    PQueue Q = (PQueue)malloc(sizeof(struct Minheap));
    Q->curr = (int*)malloc(s * sizeof(int));
    Q->size = s;
    Q->array = (Nodepq*)malloc(s * sizeof(Nodepq));
    return Q;
}

void minHeapify( PQueue Q, int index)
{
    int parent, left_c, right_c;
    parent = index;
    left_c = 2 * index + 1;
    right_c = 2 * index + 2;
  
    if (left_c < Q->size && Q->array[left_c]->k < Q->array[parent]->k)
        parent = left_c;
  
    if (right_c < Q->size && Q->array[right_c]->k < Q->array[parent]->k)
        parent = right_c;
  
    if (parent != index) {

        Q->curr[Q->array[parent]->n] = index;
        Q->curr[Q->array[index]->n] = parent;
        swap(&Q->array[parent], &Q->array[index]);
        minHeapify(Q, parent);
    }
}

int  IsPQueueEmpty(PQueue Q)
{
    if(Q->size == 0) return 1;
    else return 0;
}

Element ExtractMin(PQueue Q)
{
    if (!IsPQueueEmpty(Q)){ 
    struct stNodepq* root = Q->array[0]; 
    struct stNodepq* last = Q->array[Q->size - 1];
    Q->array[0] = last; 
    Q->curr[root->n] = Q->size - 1;
    Q->curr[last->n] = 0;
  
    --Q->size;
    minHeapify(Q, 0);
  
    return root->n;
    }
}

void   DecreaseKey(PQueue Q, Element u, float new_decreased_key)
{
      int i = Q->curr[u];
    Q->array[i]->k = new_decreased_key;
    while (i>=0 && Q->array[i]->k < Q->array[(i - 1) / 2]->k) {
        Q->curr[Q->array[i]->n] = (i - 1) / 2;
        Q->curr[Q->array[(i - 1) / 2]->n] = i;
        swap(&Q->array[i], &Q->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    } 
}

