//Negative Cycle Detection
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
int n=0;

void make_list(struct adj_list **myList)
{
     *myList = malloc(m * sizeof **myList);
}

struct adj_list* priority_queue[10000];
int front=0;
int rear=0;

void insert(struct adj_list* node);
struct adj_list* extract_min();


void construct_list(int x, int y, int w);
void all(int source);

void initialize();


int main()
{
	int i,x,y,z;
	char c,d,ch;
	fp = fopen("input.txt", "r");
	fd = fopen("output.txt", "w");
	fscanf(fp,"%d",&m);
	fscanf(fp,"%d",&n);
	//printf("%d",m);

	make_list(&list);

	initialize();

	i=0; 
	while(i<n)
	{
		fscanf(fp,"%d",&x);
		fscanf(fp,"%d",&y);
		fscanf(fp,"%d",&z);
		construct_list(x,y,z);
		i++;
	}
	struct adj_list *r;
	for(i=0; i<m; i++)
	{
		r= list[i].link;
		printf("%d->",i);
		while(r!=NULL)
		{
			printf("(D:%d W:%d)->",r->data, r->weight);
			r=r->link;
		}
		printf("nil\n");
	}
//BELLMAN_FORD: 
	struct adj_list* temp,*p;
	int j=0;
	list[j].distance = 0;
	for(i=0;i<m;i++)
	{
		j=0;
		while(j<m)
		{
			temp = list[j].link;
			p = &list[j];
			while(temp!=NULL)
			{
				if((list[temp->data].distance> list[j].distance + temp->weight)&&list[j].distance!=10000)
				{
					list[temp->data].distance = list[j].distance + temp->weight;
					list[temp->data].pred = p;
				}
				temp = temp->link;
			}
			j++;
		}
	}
//checking negative cycle:
	j=0;	
	int indicator = -1;

	while(j<m)
	{
		temp = list[j].link;
		p = &list[j];
		while(temp!=NULL)
		{
			if((list[temp->data].distance> list[j].distance + temp->weight)&&list[j].distance!=10000)
			{
				indicator = 1;
			}
			temp = temp->link;
		}
		j++;
	}

	printf("%d\n", indicator);
	
	
			
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


void construct_list(int x, int y, int w)
{
	char c;
	
		int data;
		struct adj_list* temp;
		temp = (struct adj_list*)malloc(sizeof(struct adj_list)); 

		temp->data=y;
		temp->weight= w;
		temp->link=NULL;

		if(list[x].link == NULL)
		{
			list[x].link=temp;
		}
		else
		{
			struct adj_list* p;
			p=list[x].link;
			while(p->link!=NULL)
			{	
				p=p->link;
			}
			p->link=temp;
		}

	
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
		r= &list[i];
		insert(r);
	}
	
}	


