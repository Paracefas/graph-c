#include <stdio.h>
#include <stdlib.h>

#define BOOL int
#define TRUE  1
#define FALSE 0

#define SLICE(Type) typedef struct { \
    Type* array;\
    int size;\
    int capacity;\
}slice##Type; \
slice##Type createSlice##Type(int size) { \
    slice##Type slice = { .array=(Type*)malloc(size*sizeof(Type)), .size=0, .capacity=size };\
    return slice;\
}\
void reserve##Type (slice##Type* s, int cap) {\
    s->capacity = cap; \
    s->array = (Type*)realloc(s->array, cap*sizeof(Type));\
}\
void push_back##Type (slice##Type* s, Type value) {\
    s->array[s->size++] = value;\
    if(s->capacity == s->size) reserve##Type(s, s->capacity * 2);\
}\
Type pop_back##Type (slice##Type* s) {\
    s->size--;\
    return s->array[s->size+1];\
}\
void delete##Type(slice##Type* s) {\
    free(s->array);\
}\
void printslice##Type(slice##Type* s, void (*printer)(Type)) { \
    printf("{\n\tcapacity: %d\n\tsize: %d\n", s->capacity, s->size);\
    printf("\tarray:\t[ ");\
    for(int i = 0; i < s->size-1; ++i) \
    {\
        printer(s->array[i]);\
        printf(", ");\
    }\
    printer(s->array[s->size-1]);\
    printf(" ]\n}");\
}\

typedef struct node 
{
    int label;
}node;
typedef struct edge 
{
    int w;
    node *a, *b;
}edge;
typedef edge* edges;
typedef node* nodes;

SLICE(edges)
SLICE(nodes)

typedef struct graph
{
    slicenodes nodes;
    sliceedges edges;
}graph;

graph* createGraph(int nodesSize, int edgesSize)
{
    graph* g = (graph*)malloc(sizeof(graph));
    g->edges = createSliceedges(edgesSize);
    g->nodes = createSlicenodes(nodesSize);
    return g;
}

void deleteGraph(graph* g)
{
    deletenodes(&g->nodes);
    deleteedges(&g->edges);
    free(g);
}

node* createNode(int label)
{
    node* n = (node*)malloc(sizeof(node));
    n->label = label;
    return n;
}

node* find(slicenodes nodes, int label)
{
    for(int i = 0; i < nodes.size; ++i)
        if(nodes.array[i]->label == label) return nodes.array[i]; 
}

edge* createEdge(node* from, node* to, int w)
{
    edge* e = (edge*)malloc(sizeof(edge));
    e->a = from; e->b = to; e->w = w;
    return e;
}

void pushEdge(graph* g, int from, int to, int w)
{
    node* nfrom = find(g->nodes, from);
    node* nto = find(g->nodes, to);
    if(!(nfrom && nto)) return;
    push_backedges(&g->edges, createEdge(nfrom, nto, w));
}

void pushNode(graph* g, int label)
{
    node* n = createNode(label);
    push_backnodes(&g->nodes, n);
}

void printerNodes(node* n)
{
    printf("label: %d", n->label);
}

void printerEdges(edge* e)
{
    printf("\n\t\t{ weight: %d,", e->w);
    printf("\tfrom: %d,", e->a->label);
    printf("\tto: %d }", e->b->label);
}

void printGraph(graph* g)
{
    printf("{\nnodes:\n");
    printslicenodes(&g->nodes, printerNodes);
    printf("\n}\n");
    printf("{\nedges:\n");
    printsliceedges(&g->edges, printerEdges);
    printf("\n}");
}

int main(int argc, char const** argv)
{
    graph* g = createGraph(4, 5);

    pushNode(g, 0);
    pushNode(g, 1);
    pushNode(g, 2);
    pushNode(g, 3);
    
    pushEdge(g, 0, 1, 5);
    pushEdge(g, 0, 2, 3);
    pushEdge(g, 0, 3, 2);
    pushEdge(g, 1, 0, 5);
    pushEdge(g, 1, 2, 3);
    pushEdge(g, 2, 0, 3);
    pushEdge(g, 2, 1, 3);
    pushEdge(g, 2, 3, 8);
    
    printGraph(g);
    deleteGraph(g);
}