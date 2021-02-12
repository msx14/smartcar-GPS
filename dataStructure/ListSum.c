#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define LEN sizeof(struct node) 
#define NULL 0
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct node{
	int coef; //多项式的系数
	int exp; //多项式的指数
	struct node *next; 
};
struct node *create()
{
	struct node *head,*p1,*p2;
	p1=p2=(struct node *)malloc(sizeof(LEN));
	head=(struct node *)malloc(sizeof(LEN));
	head->coef=0;
	head->exp=0;
	head->next=p1;
	scanf("%d,%d",&p1->coef,&p1->exp);
	while(p1->coef != 0 || p1->exp != 0)
	{
		p2->next=p1;
		p2=p1;
		p1=(struct node *)malloc(sizeof(LEN));
		scanf("%d,%d",&p1->coef,&p1->exp);
	}
	p2->next = NULL;
	return (head);
}
void print(struct node *head)
{
	struct node *p;
	p=head;
	while(p)
	{
		if(p->next != NULL)
			printf("%dxexp(%d) + ",p->coef,p->exp);
		else printf("%dxexp(%d) = \n",p->coef,p->exp);
		p = p->next;
	}
}
int calculate(struct node *head,int x)
{
	int sum=0;
	int item_sum=1;
	int i;
	struct node *p;
	p=head;
	while(p)
	{
		item_sum *= p->coef;
		for(i=1;i<p->exp+1;i++){
			item_sum *= x;
		}
		sum += item_sum;
		item_sum = 1;
		p= p->next;
	}
	return sum;
}
struct node *Item_Sum(struct node *x,struct node *y) //多项式求和 
{
	struct node *p1,*p2,*p3,*header;
	p1=x->next;
	p2=y->next;
	header=p1;
	while(p1 && p2 )
	{
		if(p1->next->exp > p2->exp && p1->exp < p2->exp)
		{
			p3=p2->next;
			p2->next=p1->next;
			p1->next=p2;
			p2=p3;
			p1=p1->next;
			if(p2 == NULL || p1 == NULL) break;
		}
		if(p1->next->exp < p2->exp )
		{
			p1=p1->next;
			cout = cout+10;
			if(p1->next == NULL) break;
			else{
				p1=p1->next;
				if(p2 == NULL || p1 == NULL) break;
			}
		}
		if(p1->exp == p2->exp)
		{
			p1->coef += p2->coef;
			p2=p2->next;
			p1=p1->next;
			if(p2 == NULL || p1 == NULL) break;
		}		
	}
	while(p2)
	{
		p1->next=p2;
		p1=p2;
		p2=p2->next;
	}
	return (header);
}
int main(int argc, char *argv[]) {
	struct node *X,*Y,*Z;
	int sum=0;
	X=create();
	Y=create();
	Z=Item_Sum(X,Y);
	print(Z);
	sum=calculate(X,1);
	printf("sum= %d",sum);
	return 0;
	
}
