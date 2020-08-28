#include <stdio.h>
#include <stdlib.h>
// Graphs

struct edge
{
    int edata;
    struct edge *next;
};

struct vertex
{
    int vdata;
    struct vertex *vlink;
    struct edge *elink;
};

struct vertex *create()
{
    struct vertex *G=(struct vertex *)malloc(sizeof(struct vertex));
    printf("Enter first vertex value: ");
    scanf("%d", &G->vdata);
    G->vlink=NULL;
    G->elink=NULL;
    return G;
}

void addvertex(struct vertex *G, int Vi)
{
    struct vertex *a=G;
    for(;a->vlink!=NULL;)
        a=a->vlink;
    struct vertex *nv=(struct vertex *)malloc(sizeof(struct vertex));
    nv->vdata=Vi;
    a->vlink=nv;
    nv->vlink=NULL;
    nv->elink=NULL;
}

void addedge(struct vertex *G, int Vi, int Vj)
{
    struct vertex *a=G;
    for(;a->vdata!=Vi;)
        a=a->vlink;
    if(a->vdata==Vi)
    {struct edge *b=a->elink;
    for(;b!=NULL;)
        b=b->next;
    struct edge *ne=(struct edge *)malloc(sizeof(struct edge));
    ne->edata=Vj;
    b=ne;
    ne->next=NULL;
    }
    else
        printf("Vertx not valid.");
}

void findvertex(struct vertex *G, int Vi)
{
    struct vertex *a=G;
    for(;a->vlink->vdata!=Vi;)
        a=a->vlink;
    printf("man");
    if(a->vlink==NULL)
        printf("Vertex not available.\n");
    else
        printf("Vertex available.\n");
}

void findedge(struct vertex *G, int Vi, int Vj)
{
    struct vertex *a=G;
    for(;a->vlink->vdata!=Vi;a=a->vlink);
    if(a->vlink==NULL)
        printf("Vertex not available.\n");
    else
    {
        struct edge *b=a->elink;
        for(;b->next->edata!=Vj;b=b->next);
        if(b->next==NULL)
            printf("Edge not available.\n");
        else
            printf("Edge is available.\n");
    }
}

void traverse(struct vertex *G, int Vi, int Vj)
{
    struct vertex *a=G;
    for(;a->vlink!=NULL;a=a->vlink)
    {
        printf("\n%d: ", a->vdata);
        struct edge *b=a->elink;
        for(;b->next!=NULL;b=b->next)
            printf("%d ", b->edata);
    }
}

void main()
{
    int x=0, Vi, Vj;
    struct vertex *G=NULL;
        printf("Hello!\nPress 1: Create an Empty Graph\nPress 2: Add a Vertex\nPress 3: Add an Edge\nPress 4: Find if Vertex Exists\nPress 5: Find if Edge Exists\nPress 6: Graph Traversal\n");
    for(;1;)
    {
        printf("Enter your choice: ");
        scanf("%d", &x);
        switch(x)
        {
            case 1:
                G= create();
                break;
            case 2:
                printf("Enter new vertex value: ");
                scanf("%d", &Vi);
                addvertex(G, Vi);
                break;
            case 3:
                printf("Enter parent vertex value: ");
                scanf("%d", &Vi);
                printf("Enter new edge value: ");
                scanf("%d", &Vj);
                addedge(G, Vi,Vj);
                break;
            case 4:
                printf("Enter vertex value: ");
                scanf("%d", &Vi);
                findvertex(G, Vi);
                break;
            case 5:
                printf("Enter parent vertex value: ");
                scanf("%d", &Vi);
                printf("Enter edge value: ");
                scanf("%d", &Vj);
                findedge(G, Vi, Vj);
                break;
            case 6:
                printf("Enter from node value: ");
                scanf("%d", &Vi);
                printf("Enter to node value: ");
                scanf("%d", &Vj);
                traverse(G, Vi, Vj);
                break;
            default:
                printf("Invalid Input.");
                break;
        }
    }
}