#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
//	int data;
	struct node *lchild,*rchild;
 }BSTNode;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
BSTNode *SearchBST(BSTNode *bt,int k)
{
	if(bt==NULL || bt->key==k)
		return bt;
	if(k<bt->key)
		return SearchBST(bt->lchild,k);
	else 
		return SearchBST(bt->rchild,k);
}
BSTNode *InsertBST(BSTNode *p,int k)
{
	BSTNode *p1;
	if(p==NULL)
	{
		
		p1=p=(BSTNode *)malloc(sizeof(BSTNode));
		p->key=k;
		p->rchild=NULL;
		p->lchild=NULL;
	}
//	if (k==p->key)
//		return 0;
	if (k<p->key)
	{
		p->lchild=InsertBST(p->lchild,k);
	}

	if (k>p->key) 
	{
		p->rchild=InsertBST(p->rchild,k);
	}

	return p;
}

void DispBTree(BSTNode *b)
{
	if(b!=NULL)
	{
		printf("%d",b->key);
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
void Print(BSTNode *b)
{
	if(b!=NULL)
	{
		if(b->lchild)
			Print(b->lchild);
		printf("%d ",b->key);
		if(b->rchild)
			Print(b->rchild);
		
	}
}
int main(int argc, char *argv[]) {
	int a[12]={25,18,46,2,53,39,32,4,74,67,60,11};
	BSTNode *X=NULL;
	int i;
	for(i=0;i<12;i++)X=InsertBST(X,a[i]);
	Print(X);
	return 0;
}
