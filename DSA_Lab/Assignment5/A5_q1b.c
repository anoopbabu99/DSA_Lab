//1b PRIMS algorithm

#include<stdio.h>
#include<stdlib.h>
FILE* fp;
FILE* fd;

struct adj_list
{
	int data;
	int distance;
	int weight;
	char color;
	struct adj_list* pred;
	struct adj_list* link; 
};

struct adj_list* list=NULL;
/* size of list: */  
int m=0;

void make_list(struct adj_list **myList)
{
     *myList = malloc(m * sizeof **myList);
}

struct adj_list* priority_queue[10000];
int front=0;
int rear=0;

void insert(struct adj_list* node);
struct adj_list* extract_min();


void construct_list(int i);
void weight(int i);
void initialize();

int main()
{
	int i,j,x;
	char c, ch;
	fp = fopen("input.txt", "r");
	fd = fopen("output.txt", "w");
	fscanf(fp,"%d",&m);
	//printf("%d",m);
	getc(fp);
	make_list(&list);

	initialize();

	i=0;
	printf("ADJACENCY LIST:\n");
//adjacency list construction
	while(i<m)
	{	
		c= getc(fp);
		if(c=='\n') 
		{
			printf("%d->nil\n", i);
			i++; 
			continue;
		}
			
		else if(c>47&&c<58) 
		{	
			ungetc(c, fp);
			printf("%d->", i);
			construct_list(i);
			i++;
		}
		else 
		{
			ungetc(c, fp);
			break;
		}
			
	}
printf("\n");
//addition of weights to edges:

	i=0;
	printf("WEIGHT Incorporation:\n");

	while(i<m)
	{	
		c= getc(fp);
		if(c=='\n') 
		{
			//printf("%d->nil\n", i);
			i++; 
			continue;
		}
			
		else if(c>47&&c<58) 
		{	
			ungetc(c, fp);
			printf("%d->", i);
			weight(i);
			i++;
		}
		else 
		{
			ungetc(c, fp);
			break;
		}
			
	}
fclose(fp);
printf("\n");
// PRIMS algorithm: 

	int start=0;
	list[start].pred=NULL;
	list[start].distance = 0;
	struct adj_list* p,*q;
	i=0;
	while(i<m)
	{
		p=extract_min();
		list[p->data].color = 'b';

		q=list[p->data].link;
		while(q!=NULL)
		{
			
			if(list[q->data].color!='b')
			{
				if(q->weight<list[q->data].distance)
				{
					list[q->data].distance = q->weight;
					list[q->data].pred = p;
				}
				q=q->link;
				
			}
			else
			{
				q=q->link;
			}
		}
		i++;
	}

//calculating final MST length: 
	int sum = 0;
	for(i=0; i<m; i++)
	{
		sum = sum +list[i].distance;
		if(list[i].pred==NULL)
		{
			printf("%d-> root node, no predecessor, and distance = 0\n", i);
		}
		else
		{
			printf("%d-> predecessor: %d AND distance = %d  \n",i,list[i].pred->data, list[i].distance);
		}
			
	}
printf("\n");
	printf("total sum: %d\n", sum);

fclose(fd);	
}




void insert(struct adj_list* node)
{
	int i,j;
        priority_queue[rear++]=node;
}

struct adj_list* extract_min()
{
	int min, min_index=front;
	min=10000;
	int i= front;
	int j= rear;
	while(i<j)
	{
		if(list[i].distance<min&&list[i].color!='b')
		{
			min = list[i].distance;
			min_index = i; 
			i++;
		}
		else i++;
	}
	
	return priority_queue[min_index];
	
}

void weight(int i)
{
	char c;
	struct adj_list* temp;
	temp=list[i].link;
	while(temp!=NULL)
	{
		int data;
		fscanf(fp,"%d",&data);
		temp->weight=data;
		printf("(%d,%d)->", temp->weight, temp->data);

		temp=temp->link;
		c= getc(fp);
		if(c=='\n') {break;}
		else {ungetc(c, fp);}
	}
	printf("nil\n");
		
}

void construct_list(int i)
{
	char c;
	while(1)
	{
		int data;
		fscanf(fp,"%d",&data);
		struct adj_list* temp;
		temp = (struct adj_list*)malloc(sizeof(struct adj_list)); 

		temp->data=data;
		temp->link=NULL;

		if(list[i].link == NULL)
		{
			list[i].link=temp;
		}
		else
		{
			struct adj_list* p;
			p=list[i].link;
			while(p->link!=NULL)
			{	
				p=p->link;
			}
			p->link=temp;
		}
		printf("%d->", temp->data);
		c= getc(fp);
		if(c=='\n') {break;}
		else {ungetc(c, fp);}
	}
	printf("nil\n");
}

void initialize()
{
int i;
struct adj_list *r;
	for(i=0;i<m;i++)
	{
		list[i].data = i;
		list[i].color='w';
		list[i].distance = 10000;
		list[i].pred=NULL;
		r=&list[i];
		insert(r);
	}
	
}


	

