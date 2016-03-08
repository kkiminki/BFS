//Kyler Kiminki
//kkiminki
//cmps101
//Graph.c
//Graph ADT

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

//Graph struct

typedef struct GraphObj{
   List *adjList;
   int *color;
   int *parent;
   int *dist;
   int order;
   int size;
   int source;
} GraphObj;

//Constructors ~ Destructors

Graph newGraph(int n){
   Graph G = malloc(sizeof(GraphObj));
   G->adjList = malloc((n+1) * sizeof(List));
   G->color = malloc((n+1) * sizeof(int));
   G->parent = malloc((n+1) * sizeof(int));
   G->dist = malloc((n+1) * sizeof(int));
   int i;
   for(i=0; i < n+1; i++){
      G->adjList[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->dist[i] = INF;
   }
   G->size = NIL;
   G->source = NIL;
   G->order = n;
   return G;
}

void freeGraph(Graph *pG){
   int i;
   Graph G = *pG;
   for(i = 0; i < G->order + 1; i++){
      freeList(&G->adjList[i]);
   }
   free(G->color);
   free(G->parent);
   free(G->dist);
   free(G->adjList);
   free(*pG);
   pG = NULL;
}

//Access Functions

int getOrder(Graph G){
   return G->order;
}

int getSize(Graph G){
   return G->size;
}

int getSource(Graph G){
   return G->source;
}

int getParent(Graph G, int u){
   return G->parent[u];
}

int getDist(Graph G, int u){
   return G->dist[u];
}

void getPath(List L, Graph G, int u){
   if(G->dist[u]==INF){
      return;
   }
   int i;
   int curr = u;
   for(i=0; i < G->dist[u] + 1;i++){
      append(L, curr);
      curr = G->parent[curr];
   }
}

//Manipulation procedures

void makeNull(Graph G){
   int i;
   for(i=0; i<G->order + 1; i++){
      if(length(G->adjList[i])==0)continue;
      clear(G->adjList[i]);
   }
   G->size = 0;
}

void addEdge(Graph G, int u, int v){
   addArc(G, u, v);
   addArc(G, v, u);
   G->size--;
}

void addArc(Graph G, int u, int v){
   if(length(G->adjList[u])==0){
      append(G->adjList[u], v);
   }else{
      moveFront(G->adjList[u]);
      while(index(G->adjList[u])!=-1){
         if(get(G->adjList[u]) < v){
            moveNext(G->adjList[u]);
            continue;
         }else{
            insertBefore(G->adjList[u], v);
            
            return;
         }
      }
      append(G->adjList[u], v);
   }
}

void BFS(Graph G, int s){
   int i, x;
   G->source = s;
   for(i=0; i<getOrder(G)+1;i++){
      if(i==s)continue;
      G->color[i] = WHITE;
      G->dist[i] = INF;
      G->parent[i] = NIL;
   }
   G->color[s] = GRAY;
   G->dist[s] = 0;
   G->parent[s] = NIL;
   List Q = newList();
   Enqueue(Q, s);
   while(length(Q)!=0){
      x = Dequeue(Q);
      if(length(G->adjList[x])==0) continue;
      moveFront(G->adjList[x]);
      while(index(G->adjList[x])!=-1){
         int y = get(G->adjList[x]);
         if(G->color[y]==WHITE){
            G->color[y] = GRAY;
            G->dist[y] = G->dist[x] + 1;
            G->parent[y] = x;
            Enqueue(Q, y);
         }
         moveNext(G->adjList[x]);
      }
      G->color[x] = BLACK;
   }
   freeList(&Q);
}

void printGraph(FILE* out, Graph G){
   int i;
   for(i = 1; i < G->order + 1; i++){
      if(length(G->adjList[i])==0)continue;
      fprintf(out, "%d: ", i);
      printList(out, G->adjList[i]);
      fprintf(out, "\n");
   }
}

void Enqueue(List L, int item){
   append(L, item);
}

int Dequeue(List L){
   int i = front(L);
   deleteFront(L);
   return i;
}
