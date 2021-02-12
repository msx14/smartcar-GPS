#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 10 
#define FALSE 0
#define TRUE 1
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct{
	int stack[MAXNUM];    //定义SeqStack结构体由栈和栈顶元素组成 
	int top;
}SeqStack;
int push(SeqStack *s,int x) //把元素x入栈
{
	if(s->top >= MAXNUM-1)
	{
		printf("上溢！\n");
		return FALSE;
	}
	else {
		s->top++;
		s->stack[s->top] = x;
		return TRUE;
	}
}

int gettop(SeqStack *s) //栈顶元素出栈赋给指定 
{
	int temp=-1;
	if(s->top < 0) 
		{
			printf("下溢!\n");
			return FALSE;
		}
	else {
		temp=s->stack[s->top];
		s->top--;
//		printf("pop out %d =>",s->stack[s->top]); 
		return (temp);
	}
}
SeqStack *StackCreate(){   //创建一个栈 
	SeqStack *p = malloc(sizeof(SeqStack));
	p->top = -1;
	return p;
}
void StackInit(SeqStack *p,int Init[MAXNUM],int num){ //导入初始化的元素 
	int i;
	for(i=0;i<num;i++)
		push(p,Init[i]);
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
SeqStack *StackSort(SeqStack *stack)   //用来存放栈排序的方法 
{
	SeqStack *temp_stack;
	int temp; 
	int compare; //用来承载栈顶元素 
	temp_stack=StackCreate();
    push(temp_stack,gettop(stack));
	while(temp_stack->top < 3){
			temp=gettop(stack);
			while(temp < temp_stack->stack[temp_stack->top]) push(stack,gettop(temp_stack));
			push(temp_stack,temp);
				
			
	}

	return temp_stack;
}
int main(int argc, char *argv[]) {
	SeqStack *X,*Y;
	int temp;
	X=StackCreate();
	int InitArray[MAXNUM]={2,4,3,1};
	SeqStack st2;
	st2.stack={2,4,3,1};
	StackInit(X,InitArray,4);
	StackPrint(X);
	Y=StackSort(X);
	StackPrint(Y);
	return 0;
}
