//DFS and BFS (ascending order priority, both in columns {of adj_list(obviously)} and rows.)

//color notion: 
//BLACK: visited and expanded
//WHITE: not visited
//GREY: visited

#include<stdio.h>
#include<stdlib.h>
FILE* fp;
FILE* fd;

struct adj_list
{
	int data;
	int distance;
	int start;
	int finish;
	char color;
	struct adj_list* pred;
	struct adj_list* link; 
};

struct adj_list* list=NULL;

/* size of list: */  
int m=0, time=0;

void make_list(struct adj_list **myList)
{
     *myList = malloc(m * sizeof **myList);
}

void construct_list(int i);
void reset();

void enqueue(struct adj_list* node);
struct adj_list* dequeue();


void BFS(int start, int key);
void DFS(int start, int key);
//int check(struct adj_list* node, int key);
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

	reset();

	i=0;
	//printf("ADJACENCY LIST:\n");

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
			//printf("%d->", i);
			construct_list(i);
			i++;
		}
		else 
		{
			ungetc(c, fp);
			break;
		}
			
	}

//BFS and DFS:
	int start, key;
	
	while(!feof(fp))
	{	
		c= getc(fp);
		if(c=='b')
		{	
			getc(fp); getc(fp);
			fscanf(fp,"%d %d", &start, &key);
			BFS(start, key);
			reset();
		}
		if(c=='d')
		{	
			getc(fp); getc(fp);
			fscanf(fp,"%d %d", &start, &key);
			DFS(start, key);
			printf("\n");
			reset();
		}
		if(c=='s')
		{	
			break;
		}
	}
fclose(fp);
fclose(fd);	
}

//stack:
//DFS (not shortest path) RECURSIVE:
void DFS(int start, int key)
{
	struct adj_list* p,*q,*r;
	int n=-1;
	time=time+1;
	r=&list[start];
	r->start = time;
	r->color = 'g';

	q=&list[r->data];
	printf("%d ", q->data);
	if(q->data==key) return;

	while(q!=NULL)
	{
		//n=check(q,key);
		//if(n==1) {printf("%d", key); return;}
		if(list[q->data].color=='w')
		{
			list[r->data].pred=q;
			DFS(q->data,key);
			if(q->data==key) return;
			q=q->link;
		}
		else q=q->link;
	}
	list[r->data].color='b';
	time++;
	list[r->data].finish = time;
	
}

/*
int check(struct adj_list* node, int key)
{
	struct adj_list* p = node;
	while(p!=NULL)
	{
		if(p->data == key) return 1;
		else p=p->link;
	}
	
	return 0;
}
*/

//queue:
struct adj_list* queue[10000];
int rear  = 0;
int front = 0;
//BFS ITERATIVE:
void BFS(int start, int key)
{
	list[start].color='g';
	list[start].distance=0;
	list[start].pred=NULL;
	struct adj_list*p,*q, *r;
	r=&list[start];
	enqueue(r);

	while(front!=rear)
	{
		p=dequeue();
		if(list[p->data].color=='b') break;
		printf("%d ", p->data);
		if(p->data==key) break;
		q=list[p->data].link;
		while(q!=NULL)
		{
			if(list[q->data].color=='w')
			{
				list[q->data].pred= p;
				list[q->data].distance = list[p->data].distance + 1;
				list[q->data].color = 'g';
				enqueue(q);
				//printf("child :%d ", q->data);
				q=q->link;
			}
			else
			{
				q=q->link;
			}
		}
		list[p->data].color='b';
	}
	printf("\n");
	
}

void enqueue(struct adj_list* node)
{
        queue[rear++]=node;
}


struct adj_list* dequeue()
{
        return queue[front++];
    
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
		//printf("%d->", temp->data);
		c= getc(fp);
		if(c=='\n') {break;}
		else {ungetc(c, fp);}
	}
	//printf("nil\n");
}

void reset()
{
int i;
	for(i=0;i<m;i++)
	{
		list[i].data = i;
		list[i].color='w';
		list[i].distance = m+1;
		list[i].pred=NULL;
		list[i].start= m+1;
		list[i].finish = m+1;
	}
	front=0;
	rear=0;
	time=0;
}
	


