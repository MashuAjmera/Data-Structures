#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *right, *left;
}*head;

void insert()
{
    struct node *nn=(struct node *)malloc(sizeof(struct node));
    printf("Enter data: ");
    scanf("%d", &nn->data);
    if(head->right==NULL)
        head->right=nn;
    nn->right=head;
    nn->left=head;
    head->left=nn;
}

void delete()
{

}

void display()
{
    struct node *temp=head;
    printf("The linked list is: ");
    for(;temp->right!=NULL;temp=temp->right)
        printf("%d, ", temp->data);
}

void main()
{
    int x, y=0;
    do
    {
        printf("Press 1: To insert\nPress 2: To delete\nPress 3: To display\n");
        scanf("%d", &x);
        switch(x)
        {
            case 1:
                insert();
                break;
            case 2:
                delete();
                break;
            case 3:
                display();
                break;
        }
        printf("To continue, Press 0: ");
        scanf("%d", &y);
    }while(y==0);
}