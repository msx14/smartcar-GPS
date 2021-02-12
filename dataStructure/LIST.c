#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define LEN sizeof(struct node)
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
 struct node{
	int data;
	struct node *next;
};

struct node *Combine(struct node *head1,struct node *head2){
	struct node *p1,*p2,*p3,*head,*x,*y;
	p1=head1;
	p2=head2;
	int count=0;
	p3=(struct node *)malloc(LEN);
	p3->data=0;
	head=p3;
	while(p1)
	{
		if(count %2 == 0)
		{
			p3->next=p1;
			p3=p1;
			p1=p1->next;
		}
		if(count %2 == 1)
		{
			p3->next=p2;
			p3=p2;
			p2=p2->next;
		}
			count++; 
	}

	while(p1)
	{
		p3->next=p1;
		p3=p1;
		p1=p1->next;
	}
	while(p2)
	{
		p3->next=p2;
		p3=p2;
		p2=p2->next;
	}
	return (head)->next;
}
struct node *create(void)
{
    struct node *head, *p1, *p2;
    head=p1=p2= (struct node *)malloc(LEN);
    scanf("%d",&p1->data);
    while (p1->data != 0)
    {
        p2->next = p1;
        p2 = p1;
        p1 = (struct node *)malloc(LEN);
        scanf("%d",&p1->data);
    }
    p2->next = NULL;
    free(p1);
    return (head);
}

void print(struct node *head)
{
	struct node *p; 
	p = head;
	int length=0;
	printf("the list are:\n");
	while (p != NULL)
	{
		length++;
		printf("%d ",p->data);
		p = p->next;
	}
	printf("listLength=%d\n",length);
}
int main(int argc, char *argv[]) {
	struct node *X,*Y,*Z;
	X = create();
	Y = create();
    Z=Combine(X,Y);
    print(Z);
	return 0;
}
