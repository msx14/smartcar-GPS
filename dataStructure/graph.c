#include <stdio.h>
#include <stdlib.h>
#define MAXNODE 10 //ͼ�ж���������
#define MAXEDGES 100
#define n 6
#define LEN sizeof(struct VNode)
struct VNode{                //�ڽ����� 
	int data;
	struct VNode *next;
};
typedef struct {
	int stack[n];
	int top;
	int visited[n];
}SeqStack; 
	struct VNode *vnode[n];
int push(SeqStack *s,int x) //��Ԫ��x��ջ
{
	if(s->top >= n-1)
	{
		printf("���磡\n");
		return 0;
	}
	else {
		s->top++;
		s->stack[s->top] = x;
		return 1;
	}
}

int gettop(SeqStack *s) //ȡ����Ԫ�ز���ջ 
{
	int temp=-1;
	if(s->top < 0) 
		{
			printf("����!\n");
			return NULL;
		}
	else {
		temp=s->stack[s->top];
//		s->top--;
//		printf("pop` out %d =>",s->stack[s->top]); 
		return (temp);
	}
}
SeqStack *StackCreate(){   //����һ��ջ 
	SeqStack *p = malloc(sizeof(SeqStack));
	p->top = -1;
	int i;
	for(i=0;i<n;i++)
		p->visited[i]=0;
	return p;
}
SeqStack *visitGraph()     //����ͼ 
{
	SeqStack *stack;
	stack=StackCreate();   //����ջ 
	int count=1;		   //������ÿ�ν�ջ��һ������ʹ�� 
	int i;
	struct VNode *p[n]; 
	int temp;
	push(stack,0);
	stack->visited[0]=count;
	while(count < n)
	{
		temp=gettop(stack);
		p[temp]=vnode[temp];
		while(stack->visited[p[temp]->next->data] != 0 ) 
			{
				p[temp]=p[temp]->next; //��������Ѿ������ʹ���ָ�������� 
				if(p[temp]->next == NULL) 
					break;
			}
		if(p[temp]->next != NULL || (p[temp]->next == NULL && stack->visited[p[temp]->data] == 0))
		{
			push(stack,p[temp]->next->data);
			count++;
			stack->visited[p[temp]->next->data]=count;
		}
		if(p[temp]->next == NULL && stack->visited[p[temp]->data] != 0)
			stack->top--;
		printf("temp:%d stack->stack[top]:%d\n",temp,stack->stack[stack->top]);
	}
//	printf("stack->top:%d\n",stack->top);
	for(i=0;i<n;i++)
		printf("%d ",stack->visited[i]);
	return stack;
}
int init_gavexinfo[n] = {1,2,3,4,5,6};    //������Ϣ 
int init_arcinfo[n][n]={{0,1,1,1,0,0},    //����Ϣ  
						{1,0,0,0,1,0},
						{1,0,0,0,1,0},
						{1,0,0,0,0,1},
						{0,1,1,0,0,0},
						{0,0,0,1,0,0}};
struct VNode *InitVnode(int i)             //����������ӡ 
{
	int j;
	struct VNode *p1,*p2,*head;
	head=p1=p2=(struct VNode *)malloc(LEN);
	p1->data=i;
	for(j=0;j<n;j++)
	{
		if(init_arcinfo[i][j] == 1)
		{
			p1=(struct VNode *)malloc(LEN);
			p1->data=j;
			p2->next=p1;
			p2=p1;
		}
	}
	p2->next=NULL;
	return head;
}
void print(struct VNode *X)
{
	struct VNode *head,*p1;
	head=X;
	printf("the list is ");
	while(head)
	{
		printf("%d->",head->data);
		head=head->next;
	}
	printf("NULL\n");
}
int main(int argc, char *argv[]) {
	int init_gavexinfo[n] = {1,2,3,4,5,6};
	int init_arcinfo[n][n]={{0,1,1,1,0,0},
							{1,0,0,0,1,0},
							{1,0,0,0,1,0},
							{1,0,0,0,0,1},
							{0,1,1,0,0,0},
							{0,0,0,1,0,0}};
	int i;
	for(i=0;i<n;i++)
	{
		vnode[i]=InitVnode(i);
		print(vnode[i]);
	}	
	SeqStack *stack;
	stack=visitGraph();
	return 0;
}
