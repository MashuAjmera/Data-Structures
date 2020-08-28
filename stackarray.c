#include<stdio.h>
int i=-1, a[100];
void push()
{
    i++;
    printf("Enter %dth element: ", i);
    scanf("%d", &a[i]);
}
void pull()
{
    printf("Element in position %d is deleted.\n", i);
    a[i]=0;
    i--;
}
void display()
{
    int j;
    printf("The stack is: ");
    for(j=0;j<=i;j++)
        printf("%d ", a[j]);
}
void main()
{
    int x,y=0;
    do
    {
    printf("What to do?\nPush: press 1\nPull: press 0\n");
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
    printf("To continue, press 0: ");
    scanf("%d", &y);
    }while(y==0);
    display();
}