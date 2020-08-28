#include<stdio.h>
#include<stdlib.h>
// 3 Nodes and Linked Lists
struct node
{
	int data;
	struct node *link;
};
void display(struct node *p)
{
	struct node *a=p;
	printf("The linked list is: ");
	for(;a!=NULL;a=a->link)
		printf("%d	", a->data);
	printf("\n");
}
void insnode(struct node *p, struct node *n1, struct node *n2)
{
	struct node *a=p;
	while(a->link!=NULL)
		a=a->link;	
	n2=(struct node *) malloc(sizeof(struct node));
	printf("Enter the value: ");
	scanf("%d", &(n2->data));
	a->link=n2;
	n2->link=NULL;
	display(p);
}
void findnode()
{
}
void delfnode()
{
}
void dellnode()
{
}
void delmidnode()
{
}
void insbnode()
{
}
void insenode()
{
}
void ins3node()
{
}
void main()
{
	int i,x,q=1;
	struct node *p, *n2;
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
		n2=n1;
		printf("To insert another node, press 1.\n");
		scanf("%d", &q);
	}
	printf("What do you want to do?\n");
	printf("2. Insert a new node.\n3. Find a node.\n4. Display the Linked List.\n5. Delete the first node.\n6. Delete the last node\n7. Delete a middle node.\n8. Insert a node at the beginning.\n9. Insert a node at the end.\n10. Insert a node at the third position.\n");
	scanf("%d", &x);
	switch(x)
	{
		case 2:
			insnode(p,n1,n2);
		case 3:
			findnode();
		case 4:
			display(p);
		case 5:
			delfnode();
		case 6:
			dellnode();
		case 7:
			delmidnode();
		case 8:
			insbnode();
		case 9:
			insenode();
		case 10:
			ins3node();
	}
}	
