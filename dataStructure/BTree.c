#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof( node)
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct node{
	char data;
	struct node *rchild;
	struct node *lchild;
};
typedef struct node node;
node *CreateBT1(char *pre,char *in,int n)
{

	node *bt;
	bt=(node *)malloc(LEN);
	int i=0;
	char c=pre[0];
	while(in[i] != c )i++;
	int leftNumber=i;
	int rightNumber = n-1-leftNumber;
	bt->data=c;
	if(n == 1) 
	{
		bt->lchild = NULL;
		bt->rchild = NULL;
	}
	else{
		if(leftNumber == 0)
		{
			bt->lchild = NULL;
			bt->rchild=CreateBT1(&pre[leftNumber+1],&in[leftNumber+1],rightNumber);
		}
		if(rightNumber == 0)
		{
			bt->rchild = NULL;
			bt->lchild=CreateBT1(&pre[1],&in[0],leftNumber);
		}
		if(leftNumber != 0 && rightNumber != 0)
		{
			bt->rchild=CreateBT1(&pre[leftNumber+1],&in[leftNumber+1],rightNumber);
			bt->lchild=CreateBT1(&pre[1],&in[0],leftNumber);
		}
	}
	return bt;
	
}
void DispBTree(node *b)
{
	if(b!=NULL)
	{
		printf("%c",b->data);
		if(b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DispBTree(b->lchild);
			if(b->rchild!=NULL) printf(",");
			DispBTree(b->rchild);
			printf(")");
		}
	}
}
int main(int argc, char *argv[]) {
	node *X;
//	char pre[]="AB";
//	char in[]="AB";
	char pre[]="ABDEHJKLMNCFGI";
	char in[]="DBJHLKMNEAFCGI";
	X=CreateBT1(pre,in,14);
	DispBTree(X);
	return 0;
}
