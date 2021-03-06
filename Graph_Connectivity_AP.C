#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct AListNode{
int destination;
struct AListNode* next;
};
typedef struct AListNode ALNode;

struct AdjList{
ALNode* head;
};

typedef struct AdjList AList;

struct GraphNode{
int count;
AList** GArray;
};
typedef struct GraphNode GNode;


struct QueueNode{
int capacity;
int front;
int rear;
int* Array;
};
typedef struct QueueNode QNode;


QNode* CreateQueue(int capacity){
QNode* queue=(QNode*)malloc(sizeof(QNode));
if(!queue){
printf("\nMemory Error\n\n");
}
queue->capacity=capacity;
queue->front=-1;
queue->rear=-1;
queue->Array=(int* )malloc(sizeof(int)*queue->capacity);


return queue;
}

int IsEmptyQueue(QNode* queue){
return queue->front==-1;
}

int IsFullQueue(QNode* queue){
return (queue->rear+1)%queue->capacity==queue->front;
}

void ResizeQueue(QNode* queue){



queue->Array=(int*)realloc(queue->Array,queue->capacity*2);
//printf("\nhere\n");
if(queue->front>queue->rear){
int i;

for(i=0;i<queue->front;i++){
queue->Array[i+queue->capacity]=queue->Array[i];
}
queue->rear=queue->capacity+i;
}
queue->capacity*=2;
}

void EnQueue(QNode* queue,int node){

if((queue->rear+1)%queue->capacity==queue->front){
ResizeQueue(queue);
}
queue->rear=(queue->rear+1)%queue->capacity;
queue->Array[queue->rear]=node;
if(queue->front==-1){
queue->front=0;
}

}

int DeQueue(QNode* queue){
if(IsEmptyQueue(queue)){
printf("\nNo data");
return NULL;
}else{int data=queue->Array[queue->front];

if(queue->front==queue->rear){
queue->front=-1;
queue->rear=-1;
}else{
queue->front=(queue->front+1)%queue->capacity;
}

return data;
}
}

void DeleteQueue(QNode* queue){

free(queue->Array);
free(queue);

}

GNode* CreateGraph(int n){

GNode* graph=(GNode*)malloc(sizeof(GNode));
if(!graph){
printf("\nMemory Error");
}
graph->count=n;
graph->GArray=(AList**)malloc(sizeof(AList*)*n);
if(!graph->GArray){
printf("\nMemory Error");
}
int i;
for(i=0;i<n;i++){
   graph->GArray[i]=(AList*)malloc(sizeof(AList));
graph->GArray[i]->head=NULL;
}
return graph;
}

ALNode* AddEdge(int dest){

ALNode* newNode=(ALNode*)malloc(sizeof(ALNode));
newNode->destination=dest;
newNode->next=NULL;
return newNode;
}

void AddVertex(GNode* graph,int src,int dest){

ALNode* tmpNode=AddEdge(dest);
tmpNode->next=graph->GArray[src]->head;
graph->GArray[src]->head=tmpNode;

tmpNode=AddEdge(src);
tmpNode->next=graph->GArray[dest]->head;
graph->GArray[dest]->head=tmpNode;

}

void TraverseAdjList(GNode* graph){

int i;

for(i=0;i<graph->count;i++){

printf("[ %d ] :: --> ",i);
ALNode* tmpNode=graph->GArray[i]->head;

while(tmpNode){
printf("%d --> ",tmpNode->destination);
tmpNode=tmpNode->next;
}

printf("\n");

}

}

int min(int a,int b){
return a<b?a:b;
}

void FindAPUtility(GNode* graph,int* visited,int* parent,int* low,int* disc,int* ap,int u){
static int time=0;

low[u]=++time;
visited[u]=1;
disc[u]=low[u];
int children=0;
ALNode* tmpNode=graph->GArray[u]->head;

while(tmpNode){

int v=tmpNode->destination;

if(visited[v]==0){

parent[v]=u;
children++;
FindAPUtility(graph,visited,parent,low,disc,ap,v);

low[u]=min(low[u],low[v]);
if(parent[u]==-1 && children>=2){
ap[u]=1;
}

if(parent[u]!=-1 && low[v]>=disc[u]){
ap[u]=1;
}

}else if(v!=parent[u]){
low[u]=min(low[u],disc[v]);
}

tmpNode=tmpNode->next;
}


}



void FindAP(GNode* graph){



int* low=(int*)malloc(sizeof(int)*graph->count);
int* ap=(int*)malloc(sizeof(int)*graph->count);
int* disc=(int*)malloc(sizeof(int)*graph->count);
int* parent=(int*)malloc(sizeof(int)*graph->count);
int* visited=(int*)malloc(sizeof(int)*graph->count);

int i;

for(i=0;i<graph->count;i++){
ap[i]=0;
visited[i]=0;
parent[i]=-1;

}

for(i=0;i<graph->count;i++){
if(visited[i]==0){
FindAPUtility(graph,visited,parent,low,disc,ap,i);
}
}

for(i=0;i<graph->count;i++){
if(ap[i]==1){
printf("%d  ",i);
}
}

}


int main(){
int n;

printf("\nEnter the number of nodes in graph :  ");
scanf("%d",&n);
GNode* graph=CreateGraph(n);
int i,source,dest;
int E;
printf("\nEnter the number of edges :  ");
scanf("%d",&E);
for(i=0;i<E;i++){
printf("\nEnter source destionation...");
scanf("%d %d",&source,&dest);
AddVertex(graph,source,dest);
}

printf("\nPress enter to traverse adjacency List\n");
getch();
TraverseAdjList(graph);
getch();
printf("\nPress enter to see articulation points : ");
FindAP(graph);
getch();

return 0;
}
