
#include<stdio.h>
#include<stdbool.h> 

#define INF 9999999

// number of vertices in graph
#define V 5
int count(node* n, graph g)
{
    int res = 0;
    for(int i = 0; i < N_EDGES; ++i)
        if(g.edges[i].from->label == n->label) ++res;
    return res;
}

int degree(char label, graph g)
{
    node* n = find(label, g);
    return count(n, g)-1;
}

typedef struct { int degr; node* n; } int_node;

int_node check_less_degree(graph g)
{
    int degr = 999999;
    node* nod = NULL;
    for(int i = 0; i < N_NODES; ++i)
    {
        if(degree(g.nodes[i]->label, g) < degr)
        {
            degr = degree(g.nodes[i]->label, g);
            nod = g.nodes[i];
        }
    }
    return (int_node) { .degr = degr, .n = nod };
}

node* find_neighbours(char label, graph g)
{
    node* neighbours = (node*)malloc(sizeof(node)*degree(label, g));
    for(int i = 0, j = 0; i < N_EDGES; ++i)
        if(g.edges[i].from->label == label) neighbours[j++] = *g.edges[i].to;
    return neighbours;
}

node* find(char label, graph g)
{
    node* n = NULL;
    for(int i = 0; i < N_NODES; ++i)
        if(g.nodes[i]->label == label) n = g.nodes[i];
    return n;
}


// create a 2d array of size 5x5
//for adjacency matrix to represent graph
int G[V][V] = {{0, 10, 0, 6, 0},
               {10, 0, 6, 7, 0},
               {0 , 6, 0, 7, 0},
               {6 , 7, 7, 0, 11},
               {0 , 0, 0, 11, 0}};

int main() {

  return 0;
}