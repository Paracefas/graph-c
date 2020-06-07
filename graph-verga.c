#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int label;
}node;

typedef struct edge {
    int w;
    node *from, *to;
}edge;

typedef struct graph {
    node* nodes[5];
    edge edges[25];
}graph;

node* createNode(int lab)
{
    node* n = (node*)malloc(sizeof(node));
    n->label = lab;
    return n;
}

edge createEdge(node* from, node* to, int w)
{
    edge e;
    e.from = from;
    e.to = to;
    e.w = w;
    return e;
}

int main()
{
    graph g;
    for(int i = 0; i < 5; ++i)
        g.nodes[i] = createNode(i); // 0: <- Rep.: Node 
    for(int i = 0; i < 5; ++i)
        printf("%d \n", *g.nodes[i]);  
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            printf("Insert W[ %d, %d ] = ", i, j);
            int w;
            scanf("%d", &w);
            g.edges[i*5+j] = createEdge(g.nodes[i], g.nodes[j], w);
        }
    }  
    
    for(int i = 0; i < 25; ++i)
    {
        printf("from: %d\nto: %d\nw:%d\n", g.edges[i].from->label, g.edges[i].to->label, g.edges[i].w);
    } 
}

