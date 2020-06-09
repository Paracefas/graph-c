#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N_EDGES 17
#define N_NODES 5

#define INF 9999999

typedef struct node {
    char label;
}node;

typedef struct edge {
    int w;
    node *from, *to;
}edge;

typedef struct graph {
    node* nodes[N_NODES];
    edge edges[N_EDGES];
}graph;

node* createNode(char lab)
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

int M[N_NODES][N_NODES];

void prim()
{
    int no_edge;  

    int selected[N_NODES];

    memset(selected, 0, sizeof(selected));
    no_edge = 0;


    selected[0] = 1;
    int x;  
    int y;  
    
    printf("Edge : Weight\n");

    while (no_edge < N_NODES - 1) {

        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < N_NODES; i++) {
            if (selected[i]) {
                for (int j = 0; j < N_NODES; j++) {
                    if (!selected[j] && M[i][j]) {  
                        if (min > M[i][j]) {
                            min = M[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        printf("%c - %c : %d\n", x+65, y+65, M[x][y]);
        selected[y] = 1;
        no_edge++;
    }

}
void from_graph_to_matrix(graph g)
{
    
    for(int i = 0; i < N_EDGES; ++i) 
    {
        M[((int)g.edges[i].from->label-65)][((int)g.edges[i].to->label-65)] = g.edges[i].w;
    }
}

int main()
{
    graph g;
    for(int i = 0; i <  N_NODES; ++i)
        g.nodes[i] = createNode((char)(i+65)); 
    for(int i = 0; i < N_NODES; ++i)
        printf("%c \n", *g.nodes[i]);  
    // A: 0, B: 1, C: 2, D: 3, E:4
    g.edges[0]  = createEdge(g.nodes[0],g.nodes[0], 0 ); 
    g.edges[1]  = createEdge(g.nodes[0],g.nodes[1], 10); 
    g.edges[2]  = createEdge(g.nodes[0],g.nodes[3], 6 ); 
    g.edges[3]  = createEdge(g.nodes[1],g.nodes[2], 6 ); 
    g.edges[4]  = createEdge(g.nodes[2],g.nodes[1], 6 ); 
    g.edges[5]  = createEdge(g.nodes[3],g.nodes[0], 6 ); 
    g.edges[6]  = createEdge(g.nodes[3],g.nodes[1], 6 ); 
    g.edges[7]  = createEdge(g.nodes[3],g.nodes[2], 7 ); 
    g.edges[8]  = createEdge(g.nodes[3],g.nodes[4], 11); 
    g.edges[9]  = createEdge(g.nodes[3],g.nodes[3], 0 ); 
    g.edges[10] = createEdge(g.nodes[2],g.nodes[2], 0 ); 
    g.edges[11] = createEdge(g.nodes[1],g.nodes[1], 0 ); 
    g.edges[12] = createEdge(g.nodes[1],g.nodes[0], 10); 
    g.edges[13] = createEdge(g.nodes[1],g.nodes[3], 7 ); 
    g.edges[14] = createEdge(g.nodes[2],g.nodes[3], 7 ); 
    g.edges[15] = createEdge(g.nodes[4],g.nodes[3], 11);
    g.edges[16] = createEdge(g.nodes[4],g.nodes[4], 0 );

    from_graph_to_matrix(g);
    prim();
}

