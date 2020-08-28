#include <stdio.h>
#include <stdlib.h>
//5.2.1 Stack using Linked List
struct node
{
	int data;
	struct node *link;
};
struct node *top;
void pull()
{
	if(top==NULL)
		printf("Deletion not possible.");	
	else
		top=top->link;
}
void push()
{
	struct node *n=(struct node *) malloc(sizeof(struct node));
	printf("Enter the value: ");
	scanf("%d", &(n->data));
	if(top==NULL)
	{
		n->link=NULL;
		top=n;
	}
	else
	{
		n->link=top;
		top=n;
	}
}
void display()
{
	struct node *a=top;
	printf("The stack is: ");
	for(;a!=NULL;a=a->link)
		printf("%d ", a->data);
	printf("\n");
}
void main()
{
	int x, y=0;
	do
	{		
		printf("What to do?\nTo insert: Press 1\nTo delete: Press 0\n");
		scanf("%d", &x);
		switch(x)
		{
			case 0:
				pull();
				break;
			case 1:
				push();
				break;
		}
		printf("To continue: Press 0\n");
		scanf("%d", &y);
	}while(y==0);
	display();
}
