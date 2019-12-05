#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	int occur;
	struct node* link;
};

struct node* root = NULL;

void create(int a);
void print();
void h_occur();
void add_node(int a);

FILE* fp;
FILE* fd;

int main()
{
	char ch;
	fp = fopen("input.txt","r");
	fd = fopen("output.txt","w");
	int n=6;
	int c=0;
	int d;
	int a;
	do
	{
	n=6;
	c=0;
	fscanf(fp,"%c",&ch);

	if(ch=='c') n=1;
	if(ch=='p') n=2;
	if(ch=='h') n=3;
	if(ch=='a') n=4;
	if(ch=='s') n=5;
	switch(n)
	{
		case 1: fscanf(fp,"%d",&c);
				d=0;
				while(d<c)
				{
				fscanf(fp,"%d",&a);
				create(a);
				d++;
				}
				break;
		case 2: print();
				break;
		case 3: h_occur();
				break;
		case 4: fscanf(fp,"%d",&a);
				add_node(a);
				break;
		case 5: return 0;
		
		default: break;
	}
	
	}while(n!=5);
	
	
	
	
	fclose(fp);
}	

void create(int a)
{
	struct node* temp = NULL;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->data = a;
	temp->occur = 0;
	temp->link = NULL;
	if(root==NULL)
	{
		root = temp;
	}
	else
	{
		struct node* p = root; 
		while(p->link!=NULL)
		{
			p=p->link;
		}
		p->link=temp;
	}
}

void print()
{
	struct node* temp = root;
	if (root==NULL) printf("Empty\n");
	else
	{
	while(temp!=NULL)
	{
		fprintf(fd,"%d ",temp->data);
		temp=temp->link;
	}
	}fprintf(fd,"\n");
}

void add_node(int a)
{
	struct node* temp = NULL;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->data = a;
	temp->occur = 0;
	temp->link = NULL;
	if(root==NULL)
	{
		root = temp;
	}
	else
	{
		struct node* p = root; 
		while(p->link!=NULL)
		{
			p=p->link;
		}
		p->link=temp;
	}
}

void h_occur()
{
	struct node* temp = root;
	struct node* p = root;
	
	while(temp!=NULL)
	{
		p = temp->link;
		while(p!=NULL)
		{
			if(p->data==temp->data)
			{
				p->occur=-99;
				temp->occur++;
				p=p->link;
			}
			else p=p->link;
			
		} temp = temp->link;
	}
	
	
	int max=0;
	int max_data=0;
	temp = root;
	
	
	if (root==NULL) fprintf(fd,"Empty\n");
	else
	{
	while(temp!=NULL)
	{
		if(temp->occur>max) {max_data = temp->data; max= temp->occur;temp=temp->link;}
		else {temp=temp->link;}
		

	}
	}
	fprintf(fd,"%d",max_data);
	temp=root;
	while(temp!=NULL)
	{
		
		temp->occur=0;
		temp=temp->link;
	}
	
	fprintf(fd,"\n");
	
}
		
		
		
	
	