#include <stdio.h>
#include <stdlib.h>
// Binary Search Tree

struct node
{
    int data;
    struct node *left, *right;
};

struct node *create()
{
    struct node *root=(struct node *)malloc(sizeof(struct node));
    printf("Enter root data: ");
    scanf("%d", &root->data);
    root->right=NULL;
    root->left=NULL;
    return root;
}

int find(int value, struct node *a)
{
    if(a->data==value)
        return 1;
    else if(a->data<value)
    {
        if(a->right==NULL)
            return 0;
        else
            find(value, a->right);
    }
    else
    {
        if(a->left==NULL)
            return 0;
        else
            find(value, a->left);
    }    

}

void add(int value, struct node *a)
{
    if(a->data<value)
    {
        if(a->right==NULL)
        {
            a->right=(struct node *)malloc(sizeof(struct node));
            a->right->data=value;
            a->right->right=NULL;
            a->right->left=NULL;
        }
        else
            add(value, a->right);
    }
    else
    {
        if(a->left==NULL)
        {
            a->left=(struct node *)malloc(sizeof(struct node));
            a->left->data=value;
            a->left->right=NULL;
            a->left->left=NULL;
        }
        else
            add(value, a->left);
    }    
}

void inorder(struct node *a)
{
    if(a==NULL)
        return;
    inorder(a->left);
    printf("%d ", a->data);
    inorder(a->right);
}

void preorder()
{

}

void postorder()
{

}

void bfs()
{

}

void dfs()
{

}

void delete()
{

}

void main()
{
    int x=0;
    for(;x==0;)
    {
        struct node *root;
        int value;
        printf("Press 1: To create a BST\nPress 2: To find if node exists\nPress 3: To add a node\nPress 4: Inorder display\n Press 5: To find minimum\n Press 6: To find maximum");
        scanf("%d", &x);
        switch(x)
        {
            case 1:
                root= create();
                break;
            case 2:
                printf("Enter node data: ");
                scanf("%d", &value);
                if(find(value, root)==1)
                    printf("Node available.\n");
                else
                    printf("Node not available.\n");
                break;
            case 3:
                printf("Enter the value: ");
                scanf("%d", &value);
                add(value, root);
                break;
            case 4:
                printf("The sorted tree is: ")
                inorder(root);
                break;
            default:
                printf("Invalid Input.");
                break;
        }
        printf("To continue, Press 0: ");
        scanf("%d", &x);
    }
}