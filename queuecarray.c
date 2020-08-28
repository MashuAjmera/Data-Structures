#include <stdio.h>
int i=-1, j=0, a[6];
void push()
{
    i++;
    i=i%6;
    printf("Enter %dth element: ", i);
    scanf("%d", &a[i]);
}
void pull()
{
    printf("Element at position %d is deleted.\n", j);
    j++;
    j=j%10;
}
void display()
{
    int k;
    printf("The queue is: ");
    for(k=j;k<=i;k++)
        printf("%d ", a[k]);
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
    printf("To continue, press 0:");
    scanf("%d", &y);
    }while(y==0);
    display();
}