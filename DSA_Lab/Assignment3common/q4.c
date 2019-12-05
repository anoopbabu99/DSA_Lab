//q4.c DISJOINT_SET LINKED LIST:
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* fp;
FILE* fd;

struct node
{
	int key;
	int weight;
	struct node* rep;
	struct node* link;
	
};



struct node* disjoint_HEAD[100];
struct node* disjoint_HEAD2[100]; 

int makeset();
int findset1(int x);
int findset2(int x);
int union1(int x, int y);
int union2(int x, int y);

int main()	
{	
	char ch;
	int x,y;
	int p,q;
	fp = fopen("input.txt", "r");	
	fd = fopen("output.txt", "w");

	for(x=0; x< 100; x++)
	{
		disjoint_HEAD[x] = NULL;
		disjoint_HEAD2[x] = NULL;
	}

	do
	{
		fscanf(fp,"%c", &ch);
	
		switch(ch)
		{
			case 'm': 
					makeset(); fprintf(fd,"\n"); break;
			case 'f': 
					fscanf(fp,"%d", &x); 
					p=findset1(x);  
					if(p==-1) 
					{
						break;
					} 
					fprintf(fd,"%d ",p);  
					q=findset2(x);  
					fprintf(fd,"%d ",q); 
					fprintf(fd,"\n");
					break;

			case 'u': 
					fscanf(fp,"%d", &x); 
					fscanf(fp,"%d", &y);  
					p=union1(x,y); 
					if(p==-1) 
					{
						break;
					} 
					fprintf(fd,"%d ",p); 
					q=union2(x,y); 
					fprintf(fd,"%d ",q); 
					fprintf(fd,"\n");
					break;
			case 's': return 0;
		}
	}while(ch!='s');
}
	


int makeset()
{
//part1
	int x;
	fscanf(fp,"%d", &x);
	struct node* temp;
	temp =(struct node*)malloc(sizeof(struct node*));
	if(disjoint_HEAD[x]==NULL)
	{	
		disjoint_HEAD[x]= temp;
		
		temp->key = x;
		temp->rep = temp;
		temp->link = NULL;
		fprintf(fd,"%d",disjoint_HEAD[x]->key);
	}
	else 
	{
		fprintf(fd,"PRESENT");
		return -1;
	}
//part2
	struct node* temp2;
	temp2 =(struct node*)malloc(sizeof(struct node*));
	if(disjoint_HEAD2[x]==NULL)
	{	
		disjoint_HEAD2[x]= temp2;
		
		temp2->key = x;
		temp2->rep = temp;
		temp2->link = NULL;
		temp2->weight = 1;
	}
	
}
//part 1
int findset1(int x)
{
	if(disjoint_HEAD2[x]!=NULL)
	{
		struct node* p, *rep;
		p = disjoint_HEAD[x];
		rep = p->rep;
		return rep->key;
	}
	else 
	{
		fprintf(fd,"NOT FOUND\n");
		return -1;
	}
}
//part2
int findset2(int x)
{
	
	struct node* p, *rep;
	p = disjoint_HEAD2[x];
	rep = p->rep;
	return rep->key;
}
//part1
int union1(int x, int y)
{
if(disjoint_HEAD[x]!=NULL&&disjoint_HEAD[y]!=NULL)
	{
	int p,q;
	struct node* temp, *temp2;
	struct node* rep_main, *rep_waste;
	
	p=findset1(x);
	q=findset1(y);

	rep_main = disjoint_HEAD[p];
	temp = rep_main;
	rep_waste = disjoint_HEAD[q];
	temp2=rep_waste;
	
	while(temp->link!=NULL)
	{
		temp=temp->link;	
	}
	temp->link=rep_waste;
	while(temp2!=NULL)
	{
		temp2->rep = rep_main;
		temp2=temp2->link;
	}

	temp = rep_main;
	while(temp!=NULL)
	{
		temp=temp->link;
	}

	return rep_main->key;
	}
else
	{
	fprintf(fd,"ERROR");
	return -1;
	}
}	
		
//part2

int union2(int x, int y)
{
	int p,q;
	struct node* temp, *temp2;
	struct node* rep_main, *rep_waste;
	
	p=findset2(x);
	q=findset2(y);

	if(disjoint_HEAD2[q]->weight>disjoint_HEAD2[p]->weight)
	{
		rep_main = disjoint_HEAD2[q];
		temp = rep_main;
		rep_waste = disjoint_HEAD2[p];
		temp2=rep_waste;
		disjoint_HEAD2[q]->weight= disjoint_HEAD2[q]->weight + disjoint_HEAD2[p]->weight;
	}
	
	else
	{
		rep_main = disjoint_HEAD2[p];
		temp = rep_main;
		rep_waste = disjoint_HEAD2[q];
		temp2=rep_waste;
		disjoint_HEAD2[p]->weight= disjoint_HEAD2[q]->weight + disjoint_HEAD2[p]->weight;
	}
	
	while(temp->link!=NULL)
	{
		temp=temp->link;	
	}
	temp->link=rep_waste;
	while(temp2!=NULL)
	{
		temp2->rep = rep_main;
		temp2=temp2->link;
	}

	temp = rep_main;
	while(temp!=NULL)
	{
		
		temp=temp->link;
	}


	return rep_main->key;
}	
		




	
	



