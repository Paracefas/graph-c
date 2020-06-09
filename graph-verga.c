#include <stdlib.h>
#include <stdio.h>

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

node* find(char label, graph g)
{
    node* n = NULL;
    for(int i = 0; i < N_NODES; ++i)
        if(g.nodes[i]->label == label) n = g.nodes[i];
    return n;
}

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
    g.edges[0]  = (edge){ .from = g.nodes[0], .to = g.nodes[0], .w = 0  }; 
    g.edges[1]  = (edge){ .from = g.nodes[0], .to = g.nodes[1], .w = 10 }; 
    g.edges[2]  = (edge){ .from = g.nodes[0], .to = g.nodes[3], .w = 6  }; 
    g.edges[3]  = (edge){ .from = g.nodes[1], .to = g.nodes[2], .w = 6  }; 
    g.edges[4]  = (edge){ .from = g.nodes[2], .to = g.nodes[1], .w = 6  }; 
    g.edges[5]  = (edge){ .from = g.nodes[3], .to = g.nodes[0], .w = 6  }; 
    g.edges[6]  = (edge){ .from = g.nodes[3], .to = g.nodes[1], .w = 6  }; 
    g.edges[7]  = (edge){ .from = g.nodes[3], .to = g.nodes[2], .w = 7  }; 
    g.edges[8]  = (edge){ .from = g.nodes[3], .to = g.nodes[4], .w = 11 }; 
    g.edges[9]  = (edge){ .from = g.nodes[3], .to = g.nodes[3], .w = 0  }; 
    g.edges[10] = (edge){ .from = g.nodes[2], .to = g.nodes[2], .w = 0  }; 
    g.edges[11] = (edge){ .from = g.nodes[1], .to = g.nodes[1], .w = 0  }; 
    g.edges[12] = (edge){ .from = g.nodes[1], .to = g.nodes[0], .w = 10 }; 
    g.edges[13] = (edge){ .from = g.nodes[1], .to = g.nodes[3], .w = 7  }; 
    g.edges[14] = (edge){ .from = g.nodes[2], .to = g.nodes[3], .w = 7  }; 
    g.edges[15] = (edge){ .from = g.nodes[4], .to = g.nodes[3], .w = 11 };
    g.edges[16] = (edge){ .from = g.nodes[4], .to = g.nodes[4], .w = 0  };

    from_graph_to_matrix(g);
    prim();
}

