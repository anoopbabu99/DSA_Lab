//q1.c DISJOINT_FOREST.
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

struct forest* disjoint_foresta=NULL; 
struct forest* disjoint_forestb=NULL; 
struct forest* disjoint_forestc=NULL;
struct forest* disjoint_forestd=NULL;

void make_forest_ARRAY(struct forest **myarray)
{
	*myarray = malloc(10000*sizeof**myarray);
}
int makeset();

int link_a(int x, int y);
int findset_a(int x);
int union_a(int x, int y);

int link_b(int x, int y);
int findset_b(int x);
int union_b(int x, int y);

int link_c(int x, int y);
struct forest* findset_c(int x);
int union_c(int x, int y);

int link_d(int x, int y);
struct forest* findset_d(int x);
int union_d(int x, int y);

int finda;
int findb;
int findc;
int findd;

int main()
	
{	
	finda = 0;
	findb = 0;
	findc = 0;
	findd = 0;
	int ax,bx,cx,dx;
	struct forest* c, *d ;
	int x,y;
	char ch;
	fp = fopen("input.txt", "r");	
	fd = fopen("output.txt", "w");
	make_forest_ARRAY(&disjoint_foresta);
	make_forest_ARRAY(&disjoint_forestb);
	make_forest_ARRAY(&disjoint_forestc);
	make_forest_ARRAY(&disjoint_forestd);
	
	//if((fp=fopen("in2.txt","r"))!=NULL){
        while(!feof(fp))
	{
	
	fscanf(fp,"%c", &ch);
	switch(ch)
	{
		case 'm': makeset(); fprintf(fd,"\n");break;
		case 'f': 
					fscanf(fp,"%d", &x); 
					ax=findset_a(x); 
					bx=findset_b(x); 
					c=findset_c(x);
					d=findset_d(x);
					if(ax!=0) 
					{ 
						fprintf(fd,"%d ",ax); fprintf(fd,"%d ",bx); fprintf(fd,"%d ",c->key);  fprintf(fd,"%d",d->key); 
					}
					fprintf(fd,"\n");	   
					break;
		case 'u': 
					fscanf(fp,"%d", &x);
					fscanf(fp,"%d", &y);
					ax= union_a(x,y); 
					bx= union_b(x,y); 
					cx= union_c(x,y);
					dx= union_d(x,y);
					if(ax!=-1) 
					{ 
						fprintf(fd,"%d ",ax); fprintf(fd,"%d ",bx); fprintf(fd,"%d ",cx); fprintf(fd,"%d",dx); 
					}
					
					else fprintf(fd,"ERROR ERROR ERROR ERROR"); 
					fprintf(fd,"\n");	 
					break;
		case 's': fprintf(fd,"%d %d %d %d", finda, findb+1, findc, findd); return 0;
	}	
	}
	        
}	

int makeset()
{
	int x=0;
	fscanf(fp,"%d", &x);

	struct forest* temp;
	temp = &disjoint_foresta[x];
	if(temp->mark==1)
	{
		fprintf(fd,"PRESENT");
		return 0;
	}
	else
	{
		temp->key= x;
		temp->parent=temp;
		temp->rank=0;
		temp->mark=1;
		fprintf(fd,"%d", temp->key);
	}
	temp = &disjoint_forestb[x];
	if(temp->mark!=1)
	{
		temp->key= x;
		temp->parent=temp;
		temp->rank=0;
		temp->mark=1;
		
	}
	temp = &disjoint_forestc[x];
	if(temp->mark!=1)
	{
		temp->key= x;
		temp->parent=temp;
		temp->rank=0;
		temp->mark=1;
		
		
	}
	temp = &disjoint_forestd[x];
	if(temp->mark!=1)
	{
		temp->key= x;
		temp->parent=temp;
		temp->rank=0;
		temp->mark=1;
		
	}
	
	
}

// a. with neither ranked union nor path compression applied.

int link_a(int x, int y)
{
	struct forest* temp_x, *temp_y;
	temp_x = &disjoint_foresta[x];
	temp_y = &disjoint_foresta[y];
		temp_y->parent= temp_x;
}

int findset_a(int x)
{
	
	struct forest* temp;
	temp = &disjoint_foresta[x];
	
	if(temp->mark==1)
	{
	while(temp->parent!=temp)
	{ finda++;	
		
		temp=temp->parent;
	}
	return temp->key;
	}
	
	else 
	{
		fprintf(fd,"NOT FOUND NOT FOUND NOT FOUND NOT FOUND");
		return 0;
	}
}

int union_a(int x, int y)
{
	
	
	fscanf(fp,"%d", &x);
	fscanf(fp,"%d", &y);
	
	struct forest* temp_x, *temp_y;
	temp_x = &disjoint_foresta[x];
	temp_y = &disjoint_foresta[y];
	
	if(temp_x->mark==1&&temp_y->mark==1)
	{
		

	if(findset_a(x)==findset_a(y))
	{
		
		return findset_a(x);
	}
	
	else
	{
		
		link_a(findset_a(x),findset_a(y));
		return findset_a(x);
	}
	}
	else return -1;
	
}


//b. with only ranked union applied.

int link_b(int x, int y)
{
	struct forest* temp_x, *temp_y;
	temp_x = &disjoint_forestb[x];
	temp_y = &disjoint_forestb[y];
	
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

int findset_b(int x)
{
	struct forest* temp;
	temp = &disjoint_forestb[x];
	
	if(temp->mark==1)
	{
	
	while(temp->parent!=temp)
	{
		findb++;
		temp=temp->parent;
	}
	
	return temp->key;
	}
	
	else return 0;
	
}

int union_b(int x, int y)
{
	struct forest* temp_x, *temp_y;
	temp_x = &disjoint_forestb[x];
	temp_y = &disjoint_forestb[y];
	
	if(temp_x->mark==1&&temp_y->mark==1)
	{
	if(findset_b(x)==findset_b(y))
	{  
		return findset_b(x);
	}
	else
	{
		
		link_b(findset_b(x),findset_b(y));
		return findset_b(x);
	}
	}
	else return -1;
}

// c. with only path compression applied.
int link_c(int x, int y)
{
	struct forest* temp_x, *temp_y;
	temp_x = &disjoint_forestc[x];
	temp_y = &disjoint_forestc[y];
		temp_y->parent= temp_x;
}

struct forest* findset_c(int x)
{
	int y; 
	struct forest* temp;
	struct forest* temp_2;

	temp = &disjoint_forestc[x];
	
	if(temp->mark==1)
	{findc++;
	
		if(temp->parent == temp)
		{
			
			return temp;
		}
		else	
		{
			
			temp->parent=findset_c(temp->parent->key);
			return temp->parent;
		}
	}
	
	else return 0;
}

int union_c(int x, int y)
{	
	struct forest* temp_x, *temp_y,*p ,*q;
	temp_x = &disjoint_forestc[x];
	temp_y = &disjoint_forestc[y];
	
	if(temp_x->mark==1&&temp_y->mark==1)
	{

	p = findset_c(x);
	q = findset_c(y);

	

	if(p->key==q->key)
	{
		return p->key;
	}
	else
	{
		
		link_c(p->key,q->key);
		return p->key;
	}
	}
	else return -1;
	
}

//d. with both ranked union and path compression applied.

int link_d(int x, int y)
{
	struct forest* temp_x, *temp_y;
	temp_x = &disjoint_forestd[x];
	temp_y = &disjoint_forestd[y];
	
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
struct forest* findset_d(int x)
{
	int y; 
	struct forest* temp;
	struct forest* temp_2;

	temp = &disjoint_forestd[x];
	
	if(temp->mark==1)
	{findd++;
	
		if(temp->parent==temp)
		{
			return temp;
		}
		else	
		{
			temp->parent=findset_d(temp->parent->key);
			return temp->parent;
		}
	}
	
	else return 0;
}

int union_d(int x, int y)
{	
	struct forest* temp_x, *temp_y,*p ,*q;
	temp_x = &disjoint_forestd[x];
	temp_y = &disjoint_forestd[y];
	
	if(temp_x->mark==1&&temp_y->mark==1)
	{

	p = findset_d(x);
	q = findset_d(y);

	

	if(p->key==q->key)
	{ 
		return p->key;
	}
	else
	{
		
		link_d(p->key,q->key);
		if(p->rank>=q->rank)
			return p->key;
		else
			return q->key;
	}
	}
	else return -1;
}




	

	

	





	


