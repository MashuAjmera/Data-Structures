#include <stdio.h>
#include <stdlib.h>
// 4 Various operations in Linked Lists.
struct node
{
	int data;
	struct node *link;
};
struct node *p;
void display()
{
	struct node *a=p;
	printf("The linked list is: ");
	for(;a!=NULL;a=a->link)
		printf("%d ", a->data);
	printf("\n");
}
void middle()
{
	int c=0, i;
	struct node *a=p;
	while(a->link!=NULL)
	{	
		a=a->link;
		c++;
	}
	a=p;
	for(i=0;i<c/2-1;i++)
		a=a->link;
	printf("The middle element is %d.\n", a->link->data);
	a->link=a->link->link;
}
void reverse()
{
	struct node *a=p,*a1=p->link,*a2=p->link->link;
	a->link=NULL;
	while(a1->link!=NULL)
	{
		a1->link=a;
		a=a1;
		a1=a2;
		a2=a2->link;
	}
	a1->link->link=a1;
}
void remdup()
{
	struct node *a=p;
	for(;a!=NULL;a=a->link)
		if(a->data==a->link->data)
			a->link=a->link->link;
}
void delgiven()
{
	int t;
	struct node *a=p;
	while(a->link->data!=t)
		a=a->link;
	a->link=a->link->link;
}
void detloop()
{
	
}
void nthend()
{
	int n, c, i;
	struct node *a=p;
	while(a->link!=NULL)
	{	
		a=a->link;
		c++;
	}	
	printf("Enter n: ");
	scanf("%d", &n);
	for(i=0;i<c-n;i++)
		a=a->link;
	printf("The nth element from the end is %d.", a->data);
}
void main()
{
	int x,q=1;
	struct node *n2;
	printf("Create a linked list.\n");
	struct node *n1=(struct node *)malloc(sizeof(struct node));
	printf("Enter the 1st value: ");
	scanf("%d", &(n1->data));
	n1->link=NULL;
	p=n1;	
	for(;q==1;)
	{
		struct node *n2=(struct node *) malloc(sizeof(struct node));
		printf("Enter another value: ");
		scanf("%d", &(n2->data));
		n1->link=n2;
		n2->link=NULL;
		n1=n2;
		printf("To insert another node, press 1.\n");
		scanf("%d", &q);
	}
	printf("What do you want to do?\n");
	printf("1. Find the middle of a given linked list\n2. Find the reverse of a given linked list\n3. Remove the duplicate elements from a sorted linked list.\n4. Display the Linked List.\n5. Detect a loop in a Linked List.\n6. Find nth node from the end of the linked list.\n");
	scanf("%d",&x);
	switch(x)
	{
		case 1:		
			middle();
			break;
		case 2:
			reverse();
			break;
		case 3:
			remdup();
			break;
		case 4:
			delgiven();
			break;
		case 5:
			detloop();
			break;
		case 6:
			nthend();
			break;
	}
	display();
}
