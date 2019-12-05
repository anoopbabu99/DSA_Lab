//KRUSKAL's algorithm:
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* fp;
FILE* fd;

struct forest
{
	struct forest* parent;
	int key;
	int rank;
	int mark;
};

struct adj_list
{
	int data;
	int distance;
	int weight;
	char color;
	struct adj_list* pred;
	struct adj_list* link; 
};

struct forest* disjoint_forest=NULL; 
struct adj_list* list=NULL;

/* size of list: */  
int m=0;

void make_list(struct adj_list **myList)
{
     *myList = malloc(m * sizeof **myList);
}

void make_forest_ARRAY(struct forest **myarray)
{
	*myarray = malloc(10000*sizeof**myarray);
}

void construct_list(int i);
void weight(int i);
void initialize();

int makeset(int x);
int link(int x, int y);
struct forest* findset(int x);
int union_k(int x, int y);


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
	make_forest_ARRAY(&disjoint_forest);
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
//KRUSKAL's algorithm:
	
	for(i=0;i<m;i++)
	{
		makeset(i);
	}
	
	

	

fclose(fp);
printf("\n");
}

int makeset(int x)
{

	struct forest* temp;
	temp = &disjoint_forest[x];
	
	temp->key= x;
	temp->parent=temp;
	temp->rank=0;
	printf("%d", temp->key);
	
}


int link(int x, int y)
{
	struct forest* temp_x, *temp_y;
	temp_x = &disjoint_forest[x];
	temp_y = &disjoint_forest[y];
	
	if(temp_x->rank<temp_y->rank)
	{
		temp_x->parent=temp_y;
	}
	else
	{
		temp_y->parent= temp_x;
		if(temp_x->rank==temp_y->rank)
		{
			temp_x->rank++;
		}
	}
}
struct forest* findset(int x)
{
	int y; 
	struct forest* temp;
	struct forest* temp_2;

	temp = &disjoint_forest[x];
	
	if(temp->mark==1)
	{
		if(temp->parent==temp)
		{
			return temp;
		}
		else	
		{
			temp->parent=findset(temp->parent->key);
			return temp->parent;
		}
	}
	
	else return 0;
}

int union_k(int x, int y)
{	
	struct forest* temp_x, *temp_y,*p ,*q;
	temp_x = &disjoint_forest[x];
	temp_y = &disjoint_forest[y];
	
	if(temp_x->mark==1&&temp_y->mark==1)
	{

	p = findset(x);
	q = findset(y);

	//printf("pkey = %d\n", p->key);		

	if(p->key==q->key)
	{ 
		return p->key;
	}
	else
	{
		
		link(p->key,q->key);
		if(p->rank>=q->rank)
			return p->key;
		else
			return q->key;
	}
	}
	else return -1;
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
	}
	
}

