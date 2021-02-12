#include <stdio.h>
#include <stdlib.h>
#define n 6
#define LEN sizeof(struct VNode) 
struct VNode{                //�ڽ����� 
	int count; //������¼���������� 
	int data;
	struct VNode *next;
};
typedef struct {
	int stack[n];
	int top;
	int visited[n];
}SeqStack; 
int init_gavexinfo[n] = {1,2,3,4,5,6};    //������Ϣ 
int init_arcinfo[n][n]={{0,0,1,1,0,0},    //����Ϣ  
						{0,0,0,1,1,0},
						{0,0,0,1,0,1},
						{0,0,0,0,0,1},
						{0,0,0,0,0,1},
						{0,0,0,0,0,0}};
struct VNode *vnode[n];
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct VNode *InitVnode(int i)             //����������ӡ 
{
	int j;
	struct VNode *p1,*p2,*head;
	head=p1=p2=(struct VNode *)malloc(LEN);
	head->count=0;
	p1->data=i;
	for(j=0;j<n;j++)
	{
		if(init_arcinfo[j][i] == 1)
		{
			head->count++;
		}
	}
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
		s->top--;
//		printf("pop` out %d =>",s->stack[s->top]); 
		return (temp);
	}
}
SeqStack *StackCreate(){   //����һ��ջ 
	SeqStack *p = malloc(sizeof(SeqStack));
	p->top = -1;
	int i;
	for(i=0;i<n;i++) p->visited[i]=0;
	return p;
}
void StackPrint(SeqStack *stack){
	SeqStack *p;
	p=stack;
	int init_ptop = p->top;
	printf("the elements are ");
	while(p->top != -1){
		printf("%d ",p->stack[p->top]);
		p->top--;
	}
	printf("in the stack.\n");
	p->top = init_ptop;
}
SeqStack *visitAOV()
{
	SeqStack *stack;     //ջ�������в��� 
	stack=StackCreate();
	int sort[n]={};      //�����洢���е���Ϣ 
	int sortTop=0;
	struct VNode *p[n];
	
	int i;
	for(i=0;i<n;i++) 
	{
		sort[i]=-1;
		p[i]=vnode[i];
	}
	for(i=0;i<n;i++)
	{
		if(vnode[i]->count == 0)
			{
				push(stack,i);
				stack->visited[i]=1;
			}
	}
//	StackPrint(stack);
	while(stack->top != -1)
	{
		int temp;
		temp=gettop(stack);
		sort[sortTop]=temp;
		sortTop++;
		stack->visited[temp]=1;
		vnode[temp]=vnode[temp]->next;
		while(vnode[temp])
		{
			vnode[vnode[temp]->data]->count--;
			vnode[temp]=vnode[temp]->next;
		}
		for(i=0;i<n;i++)
		{
			if(p[i]->count == 0 && stack->visited[i]==0)
			push(stack,i);
		}
//		for(i=0;i<n;i++) printf("the count of %d is %d\n",i,p[i]->count);
//		StackPrint(stack);
//		printf("the sort of the AOV is:"); 
//		for(i=0;i<n;i++) printf(" %d",sort[i]);
	}
	printf("the sort of the AOV is:"); 
	for(i=0;i<n;i++) printf("%d->",sort[i]);
	printf("NULL");
}
int main(int argc, char *argv[]) {
	SeqStack *stack;
	int i;
	for(i=0;i<n;i++)
	{
		vnode[i]=InitVnode(i);
		print(vnode[i]);
	}	
	for(i=0;i<n;i++) printf("the count of %d is %d\n",i,vnode[i]->count);
	stack=visitAOV();
	return 0;
}

