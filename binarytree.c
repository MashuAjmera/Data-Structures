#include <stdio.h>
#include <stdlib.h>
// Binary Tree

struct node
{
    int data;
    struct node *left;
    struct node *right;
}*a, *root;

void create()
{
    root=(struct node*)malloc(sizeof(struct node));
    printf("Enter root data: ");
    scanf("%d", &root->data);
}

struct node *find(struct node *a,int value)
{
    struct node *c;
    if(a==NULL)
        return NULL;
    if(a->data==value)
        return a;
    else
    {
        c=find(a->left,value);
        if(c!=NULL)
            return c;
        c=find(a->right,value);
        if(c!=NULL)
            return c;
        return NULL;
    }
}

void left()
{
    a->left=(struct node *)malloc(sizeof(struct node));
    a->left->left=NULL;
    a->left->right=NULL;
    printf("Enter child data: ");
    scanf("%d", &a->left->data);
}

void right()
{
    a->right=(struct node *)malloc(sizeof(struct node));
    a->right->left=NULL;
    a->right->right=NULL;
    printf("Enter child data: ");
    scanf("%d", &a->right->data);
}

void delete()
{
   if(a->right==NULL && a->left==NULL)
    {
        a=NULL;
        printf("Node deleted.");
    }
   else
        printf("Node cannot be deleted.");
}

void height()
{
    
}

void istreebst()
{

}

void main()
{
    int x=0;
    for(;x==0;)
    {
        int value;
        printf("Press 1: To create a binary tree\nPress 2: To find a node\nPress 3: To insert a left child\nPress 4: To insert a right child\nPress 5: To delete a leaf node\nPress 6: To find the height\n");
        scanf("%d", &x);
        switch(x)
        {
            case 1:
                create();
                break;
            case 2:
                a=root;
                printf("Enter node data: ");
                scanf("%d", &value);
                if (find(a,value)==NULL)
                    printf("Node not found.");
                else
                    printf("Node found.");
                break;
            case 3:
                a=root;
                printf("Enter parent data: ");
                scanf("%d", &value);
                a=find(a,value);
                if(a==NULL)
                    printf("Parent node invalid.");
                else left();
                break;
            case 4:
                a=root;
                printf("Enter parent data: ");
                scanf("%d", &value);
                a=find(a,value);
                if(a==NULL)
                    printf("Parent node invalid.");
                else right();
                break;
            case 5:
                a=root;
                printf("Enter node data: ");
                scanf("%d", &value);
                a=find(a,value);
                if(a==NULL)
                    printf("Node not available.");
                else delete();
                break;
            case 6:
                height();
                break;
            default:
                printf("Invalid Input.");
                break;
        }
        printf("To continue, Press 0: ");
        scanf("%d", &x);
    }
}