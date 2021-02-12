#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100 
#define n 8
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct{
	char data;
	int weight;
	int parent;
	int lchild;
	int rchild;
	int temp;//用来标记weight是否使用过 
}huffnode;
typedef struct
{
	char cd[MAXSIZE];
	int start;
}huffcode;
huffnode ht[2*n-1];
huffcode hc[n+1];
void initBuffertree(char *data,int *weight)
{
	int i;
	for(i=1;i<2*n;i++)
	{
		if(i<n+1)
		{
		ht[i].data=*(data+i-1);
		ht[i].weight=*(weight+i-1);	
		ht[i].temp=ht[i].weight; 
		}
		if(i>n)
		{
			ht[i].data='Z';
			ht[i].weight=-1;   //表明该结点不为叶子节点，初始置位成-1 
			ht[i].temp=ht[i].weight;
		}
		ht[i].parent=0;
		ht[i].lchild=0;
		ht[i].rchild=0;
	}
	while(ht[2*n-1].temp==-1)
		createBuffernode();
	for(i=1;i<2*n;i++)
	printf("ht[%2d].data= %c || ht[%2d].temp= %3d|| ht[%2d].weight= %3d || ht[%2d].parent=%2d || ht[%2d].lchild=%2d || ht[%2d].rchild=%2d\n",i,ht[i].data,i,ht[i].temp,i,ht[i].weight,i,ht[i].parent,i,ht[i].lchild,i,ht[i].rchild);
}
void createBuffernode()
{
	int i=1;
	int min1,min2;
	min1=findmin();
	min2=findmin();
	while(ht[i].temp != -1) i++;
	ht[i].weight=ht[min1].weight+ht[min2].weight;
	ht[i].temp=ht[i].weight;
	ht[i].lchild=min1;
	ht[i].rchild=min2;
	ht[min1].parent=i;
	ht[min2].parent=i;
}
void inithuffcode()
{
	
	int i;
	for(i=1;i<n+1;i++)
		createhuffnode(i);
}
char *change(char *s,int len)
{
	int start=0;
	int end=len-1;
	while(start < end)
	{
		char c=s[start];
		s[start]=s[end];
		s[end]=c;
		start++;
		end--;
	}
	return s;
}
void createhuffnode(int i)
{
	int parent_flag;
	int son_flag=i;
	hc[i].start=0;
	while(ht[son_flag].parent != 0)
	{
		parent_flag=ht[son_flag].parent;
		if(ht[parent_flag].rchild == son_flag)
			hc[i].cd[hc[i].start]='1';
		if(ht[parent_flag].lchild == son_flag)
			hc[i].cd[hc[i].start]='0';
		hc[i].start++;
		son_flag=parent_flag;
	}
	char *s1=change(hc[i].cd,hc[i].start);
//	printf("char %c\n",hc[i].cd[hc[i].start-1]);
	printf("hc[%d].cd=%s\n",i,s1);
}

int findmin()
{
	int i=1;
	int temp;
	while(ht[i].temp == -2 )
		i++;
	temp=ht[i].temp;
	int flagA=i;
	for(i=1;i<2*n;i++)
	{
		if(ht[i].temp<temp && ht[i].temp != -2 && ht[i].temp != -1) 
		{
			temp=ht[i].temp;
			flagA=i;
		}
	}
	ht[flagA].temp=-2;   //-2表示原本有值，因为被构造后将被置为成-1 
//	printf("the min is %d the flag is %d\n",temp,flagA);
	return flagA;
}
int main(int argc, char *argv[]) {
	char data[n]="ABCDEFGH";
	int weight[n]={5,29,7,8,14,23,3,11};
	initBuffertree(data,weight);
	inithuffcode();
	return 0;
}
