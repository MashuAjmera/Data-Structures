#include <stdio.h>
#include <stdlib.h>
//5.2.2 Queue using Linked List
struct node
{
	int data;
	struct node *link;
};
struct node *front=NULL, *rear=NULL;
void pull()
{
	front=front->link;
}
void push()
{
	struct node *n=(struct node *) malloc(sizeof(struct node));
	printf("Enter the value: ");
	scanf("%d", &(n->data));
	n->link=NULL;
	if(front==NULL)
	{
		front=n;
		rear=n;
	}
	else
	{
		rear->link=n;
		rear=n;
	}
}
void display()
{
	struct node *a=front;
	printf("The queue is: ");
	for(;a!=NULL;a=a->link)
		printf("%d ", a->data);
	printf("\n");
}
void main()
{
	int x, y=0;
	do
	{		
		printf("What to do?\nTo insert: Press 1\nTo delete: Press 2\nTo display: Press 3\n");
		scanf("%d", &x);
		switch(x)
		{
			case 1:
				push();
				break;
			case 2:
				pull();
				break;
			case 3:
				display();
				break;
		}
		printf("To continue: Press 0\n");
		scanf("%d", &y);
	}while(y==0);
}
