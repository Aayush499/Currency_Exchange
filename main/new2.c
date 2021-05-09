#include <stdio.h>
#include <stdlib.h>
 #include <string.h>
 #include"queue.c"

// Define the maximum number of vertices in the graph
#define N 6
#define MAX 6
#define INFINITY 100000
#define AVAILABLE 1;
#define NOTAVAILABLE 0;

 /////////////////////////////////////////
 ////////////////////////////////////////
 ///////////////////////////////////////
 //Struct part of the code

int arr_banks[MAX]={0};

int num=0;

typedef struct Graph
{
    char name[5]; //name of bank
    // An array of pointers to Node to represent an adjacency list
    struct Node* head[N];
    int refer[N];
}bank;
 
// Data structure to store adjacency list nodes of the graph
typedef struct Node
{
    char curr[4]; //3 letter name of currency
    int dest, weight;
    struct Node* next;
}currency;
 
// Data structure to store a graph edge
typedef struct Edge {
    int src, dest, weight;
}conversion;

struct stTable
{
    int *pKnown;
    float *pdistance_to_source;
    int *pPrevious_vertex;
};
 
// Function to create an adjacency list from specified edges
bank* createGraph(char name_of_bank[],  int array[],int V)
{
    unsigned i;
 
    // allocate storage for the graph data structure
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    
    strcpy(graph->name,name_of_bank);

    // initialize head pointer for all vertices
    for (i = 0; i < N; i++) {
        graph->head[i] = NULL;
        graph->refer[i]=NOTAVAILABLE;
    }

    for(i=0;i<V;i++){
        graph->refer[array[i]]=AVAILABLE;
    }
 
  
    num++;
    return graph;
}

 int find_min(long long int A[],int n)
{
   long long int min=A[0];
   int index=0;
   for(int i=1;i<n;i++){
       if(min>A[i]) 
       {
           min=A[i];
           index=i;
       }    
   }
   return index;
}
 /////////////////////////////////////////////////
 ///////////////////////////////////////////
 ////////////////////////////////////////

// Function to print adjacency list representation of a graph
void printGraph(struct Graph* graph)
{
    int i;
    printf("%s\n",graph->name);
    for (i = 0; i < N; i++)
    {
        // print current vertex and all its neighbors
        struct Node* ptr = graph->head[i];
        while (ptr != NULL)
        {
            printf("%d —> %d (%d)\t", i, ptr->dest, ptr->weight);
            ptr = ptr->next;
        }
 
        printf("\n");
    }
}

void AddConversion(struct Node** head_ref,int dest,int weight)
{
    struct Node* curr= *head_ref;
    struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
    newnode->dest=dest;
    newnode->weight=weight;
    newnode->next=curr->next;
    curr->next=newnode;
}

// void AddConversion(struct Node** head_ref, int dest,int weight)
// {
//     /* 1. allocate node */
//     struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
   
//     /* 2. put in the data  */
//     new_node->dest  = dest;
//     new_node->weight  = weight;
//     /* 3. Make next of new node as head */
//     new_node->next = (*head_ref);
   
    /* 4. move the head to point to the new node */
//     (*head_ref)    = new_node;
// }
void AddCurrency(int c,bank* G)
{
    G->refer[c]= AVAILABLE;
}

////////////////////////////////////////
//////////////////////////////////////////
//Sir's old deletion codes from linked list

 void deleteList(struct Node** head_ref)
{
   /* deref head_ref to get the real head */
   struct Node* current = *head_ref;
   struct Node* next;
 
   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }
   
   /* deref head_ref to affect the real head back
      in the caller. */
   *head_ref = NULL;
}

void deleteNode(struct Node** head_ref, int key)
{
    // Store head node
    struct Node *temp = *head_ref, *prev;
 
    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->dest == key) {
        *head_ref = temp->next; // Changed head
        free(temp); // free old head
        return;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->dest!= key) {
        prev = temp;
        temp = temp->next;
    }
 
    // If key was not present in linked list
    if (temp == NULL)
        return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
 
    free(temp); // Free memory
}

//////////////////////////////////////////
/////////////////////////////////////////
///////////////////////////////////////


//The currency deletion and conversion deletion have been implemented, please do test it out and debug
//The implementation of the additon of currency and conversion should be equally easy

void DeleteBank(bank* G)
{
    for(int i=0;i<N;i++){
        deleteList(&G->head[i]);
    }
    free(G);
}

void deleteCurrency(bank* B, int key) //deleting an entire currency
{
    for(int i =0;i<N;i++)
      {
          deleteNode(&B->head[i],key);
      }
      deleteList(&B->head[key]);
}

void deleteConversion(bank* B,int source,int destination) //deleting a conversion/edge
{
    deleteNode(&B->head[source],destination);
}

struct stTable* Djistra ( bank* G,  int from , int to)
{
    struct stTable* myTable;
    int i,j;
    PQueue Q;
    int u,v,x;
    struct Node* temp;
    double cost;

    myTable = (struct stTable*)malloc(sizeof(struct stTable));
    if(myTable == NULL)
    {
        exit(0);
    }
    myTable->pKnown                 = (int *)   malloc(N*sizeof(int));
    myTable->pdistance_to_source    = (float *) malloc(N*sizeof(float));
    myTable->pPrevious_vertex       = (int *)malloc(N*sizeof(int));
    
    for(i=0;i<N;i++)
    {
        myTable->pKnown[i]                = 0;
        myTable->pdistance_to_source[i]   = INFINITY;
        myTable->pPrevious_vertex[i]      = -1;            
    }

    myTable->pdistance_to_source[from]   = 0;

    Q = CreateEmptyPriorityQueue(N);
    for(i=0;i<N;i++)
        newnode(Q,i,myTable->pdistance_to_source[i]); 

    while(!IsPQueueEmpty(Q))
    {
        u = ExtractMin(Q);

        myTable->pKnown[u] = 1;
        temp    = G->head[u];
        while(temp!= NULL)
        {
            v = temp->dest;
            if((!myTable->pKnown[v])  && (myTable->pdistance_to_source[v]  > temp->weight + myTable->pdistance_to_source[u] ))
            {
                myTable->pdistance_to_source[v] = (temp->weight) + myTable->pdistance_to_source[u];
                myTable->pPrevious_vertex[v]    = u;
                DecreaseKey(Q,v,myTable->pdistance_to_source[v]);
            }
            temp = temp->next;
        }
    }

       // cost=myTable->pdistance_to_source[to];

         return myTable;
}

void printpath(struct stTable* T,int from,int to)
{
        int x=to;
        while( x!=from){
            printf("%d<--",x);
            x=T->pPrevious_vertex[x];
        }
        printf("%d\n",from);
}

long long int bestpath(bank* arr[],int from ,int to,int delete[])
{
    long long int A[MAX];
     for(int i=0;i<num;i++)
     {
      if(delete[i]==1)
      A[i]= (Djistra(arr[i],from,to))->pdistance_to_source[to];
      else A[i]=INFINITY;
     }
    int x= find_min(A,num);
    if(A[x]!=INFINITY){
    printf("Bank_name:%s Cost:%lld\n",arr[x]->name,A[x]);
    printf("path: ");
    printpath(Djistra(arr[x],from,to),from,to);
    }
    else printf("NOT POSSIBLE\n");
}

// int main(void)
// {
//     // input array containing edges of the graph (as per the above diagram)
//     // (x, y, w) tuple represents an edge from `x` to `y` having weight `w`
//     struct Edge edges[] =
//     {
//         { 0, 1, 6 }, { 4, 5, 1 },{ 1, 2, 7 },{1,3,5}, { 2, 0, 5 }, { 2, 1, 4 },
//         { 3, 2, 10 },{3,5,9},  { 5, 4, 3 }
//     };
    
    
//     bank* arr[MAX]; // array of banks

//     // calculate the total number of edges
//     int n = sizeof(edges)/sizeof(edges[0]);
 
//     // construct a graph from the given edges

//    int ver[6]={0,1,2,3,4,5};

//     arr[0] = createGraph("BoA", n,ver,6); //Bank 1: Bank of AMerica 
//     arr[1] = createGraph("Citi",n,ver,6);    //Bank 2: Wix

      //add edges to the directed graph one by one
    // for (int i = 0; i < n; i++)
    // {
    //     // get the source and destination vertex
    //     int src = edges[i].src;
    //     int dest = edges[i].dest;
    //     int weight = edges[i].weight;
         
    //     // allocate a new node of adjacency list from `src` to `dest`
    //     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    //     newNode->dest = dest;
    //     newNode->weight = weight;
 
    //     // point new node to the current head
    //     newNode->next = arr[0]->head[src];
 
    //     // point head pointer to the new node
    //     arr[0]->head[src] = newNode;
    // }
    // Function to print adjacency list representation of a graph
    
    // for(int i=0;i<n;i++)
    // {
    //     int src = edges[i].src;
    //     int dest = edges[i].dest;
    //     int weight = edges[i].weight;
    //     if(arr[0]->refer[src]&&arr[0]->refer[dest])
    //     {
    //         addConversion(&arr[0]->head[src],dest,weight);
    //     }
    //     else
    //     puts("Vertex not present");
    // }
    // printGraph(arr[0]);
    // push(&arr[0]->head[3],4,15);
    // printGraph(arr[0]);
    //   deleteNode(&arr[0]->head[0],2);
    //    deleteNode(&arr[0]->head[1],2);
    //    deleteNode(&arr[0]->head[2],2);
    //    if(arr[0]->refer[1] == 1)
    //    AddConversion(&arr[0]->head[1],5,4);
    //    for(int i =0;i<N;i++)
    //   {
    //       deleteNode(&arr[0]->head[i],2);
    //   }
    // deleteList(&arr[0]->head[2]);
    
    //deleteCurrency(arr[0],2);
    // deleteConversion(arr[0],3,5);
    // int A[2];
    // printGraph(arr[0]);
    // printGraph(arr[1]);

    //bestpath(arr,1,5);
    // for(int i=0;i<2;i++){
    //   A[i]=Djistra(arr[i],1,5);
    // }
    // int x=find_min(A,2);
    // if(A[x]==INFINITY) printf("conversion not possible");
    // else printf("Bank:%s cost:$ %d\n",arr[x]->name,A[x]);

//     return 0;
// }