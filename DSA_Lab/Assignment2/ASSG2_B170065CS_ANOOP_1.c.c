//HASH TABLE q1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct hashNODE
{
	int data;
	int deleted;
	int occupied;
	struct hashNODE* link;
};

int m,m2;
int c1,c2;

struct hashNODE* hashARR = NULL;

void hashTable(struct hashNODE **myArray)
{
     *myArray = malloc(m * sizeof **myArray);
}

FILE* fp;
FILE* fd;

int linear();
int insertl();
int searchl();
int deletel();
int print();

int quadratic();
int insertq();
int searchq();
int deleteq();

int doubleh();
int insertd();
int searchd();
int deleted();

int linkedlist();
int insertc();
int searchc();
int deletec();
int printc();

int main()
{
	char type;
	fp=fopen("input.txt","r");
	fd=fopen("output.txt","w");
	fscanf(fp,"%s",&type);
	switch(type)
	{
		case 'a': linear(); break;
		case 'b': quadratic(); break;
		case 'c': doubleh(); break;
		case 'd': linkedlist(); break;
		default: return 0;
	}
}
//array of linked lists
int linkedlist()
{int i;
	fscanf(fp,"%d",&m);
	hashTable(&hashARR);

	for(i=0;i<m;i++)
	hashARR[i].link = NULL;
	

	char op;
	do 
	{
		fscanf(fp,"%s",&op);
		switch(op)
		{
			case 'i': insertc(); break;
			case 's': searchc(); break;
			case 'd': deletec(); break;
			case 'p': printc();break;
			default: return 0;
		}

	} while(op!='t');
}


int insertc()
{
	int data;
	fscanf(fp,"%d",&data);
	int key=data%m;
	struct hashNODE* temp;
	temp = (struct hashNODE*)malloc(sizeof(struct hashNODE*)); 
	temp->data=data;
	temp->link=NULL;
	if(hashARR[key].link == NULL)
	{
		hashARR[key].link=temp;
	}
	else
	{
		struct hashNODE* p;
		p=hashARR[key].link;
		while(p->link!=NULL)
		{	
			p=p->link;
		}
		p->link=temp;
	}
}

int searchc()
{
int data,key;
fscanf(fp,"%d",&data);
key = data%m;
struct hashNODE* p;
p=hashARR[key].link;

int flag=0;

while(p!=NULL)
	{
		if(p->data==data)
		{	
			flag=1;
		}p=p->link;
	}

if(flag==1) fprintf(fd,"1\n");
else fprintf(fd,"-1\n");

}


int deletec()
{

int data,key;
fscanf(fp,"%d",&data);
key = data%m;
struct hashNODE* p;
p=hashARR[key].link;

int flag=0;

while(p!=NULL)
	{
		if(p->data==data)
		{	
			flag=1;
		}p=p->link;
	}
//only delete if found
if(flag==1) 
{
	p=hashARR[key].link;
	struct hashNODE* q=p->link;
	while(q!=NULL)
	{	
		if(q->data==data)
		{
			p->link=q->link;
			q->link=NULL;
			free(q);
			}
		p=p->link;
		q=q->link;
	}
//deletion if it is the first node
	p=hashARR[key].link;
	if(p->data==data)
	{
		hashARR[key].link=p->link;
		p->link=NULL;
		free(p);
	}


}

else return 0;
}



int printc()
{
int i;
struct hashNODE* p;

for(i=0;i<m;i++)
{fprintf(fd,"%d (",i);
p=hashARR[i].link;
	while(p!=NULL)
	{
		if(p->link==NULL)
		fprintf(fd,"%d", p->data);
		else fprintf(fd,"%d ", p->data);
		p=p->link;
	}
	fprintf(fd,")\n");
}

}
		
		

//double
int doubleh()
{int i;
	fscanf(fp,"%d",&m);
	hashTable(&hashARR);

	for(i=0;i<m;i++){
	hashARR[i].occupied = 0;
	hashARR[i].deleted = 0;
	}
	

	char op;
	do 
	{
		fscanf(fp,"%s",&op);
		switch(op)
		{
			case 'i': insertd(); break;
			case 's': searchd(); break;
			case 'd': deleted(); break;
			case 'p': print();break;
			default: return 0;
		}

	} while(op!='t');
}


int insertd()
{
int data,key,flag=0;
fscanf(fp,"%d",&data);
int keyM = data%m;
key = keyM;
//finding prime
int i,j;
for(i=m-1;i>1;i--)
	{
        	for(j = 2; j <= i/2; ++j)
        	{
           		if(i % j == 0)
            		{
               			flag = 1;
               			break;

			}
            	}
        

        	if (flag == 0)
            	{m2=i; break;}
		flag=0;
	}
//found
int keyM2=m2-data%m2;

i=0;

while(hashARR[key].occupied==1&&i<m)
{
	key= (keyM+i*keyM2)%m;
	i++;
}

hashARR[key].data=data;
hashARR[key].occupied=1;
hashARR[key].deleted=0;
}

int searchd()
{
int data,key;
fscanf(fp,"%d",&data);
int keyM = data%m;
key = keyM;
int keyM2=m2-data%m2;

int i=0;

while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
{
	key= (keyM+i*keyM2)%m;
	i++;
	if(i==m) break;
}

if(hashARR[key].data==data) {fprintf(fd,"1\n"); return 1;}
else {fprintf(fd,"-1\n"); return -1;}
}

int deleted()
{

int data,key;
fscanf(fp,"%d",&data);
int keyM = data%m;
key = keyM;
int keyM2=m2-data%m2;
int i=0;

while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
{
	key= (keyM+i*keyM2)%m;
	i++;
	if(i==m) break;
}

if(hashARR[key].data==data)
{
	hashARR[key].data=0;
	hashARR[key].occupied=0;
	hashARR[key].deleted=1;
}
else return 0; 
}


//quadratic
int quadratic()
{int i;
	fscanf(fp,"%d",&m);
	hashTable(&hashARR);

	for(i=0;i<m;i++){
	hashARR[i].occupied = 0;
	hashARR[i].deleted = 0;
	}
	fscanf(fp,"%d",&c1);
	fscanf(fp,"%d",&c2);
	

	char op;
	do 
	{
		fscanf(fp,"%s",&op);
		switch(op)
		{
			case 'i': insertq(); break;
			case 's': searchq(); break;
			case 'd': deleteq(); break;
			case 'p': print();break;
			default: return 0;
		}

	} while(op!='t');
}

int insertq()
{
int data,key;
fscanf(fp,"%d",&data);
int keyM = data%m;
key = keyM;

int i=0;

while(hashARR[key].occupied==1&&i<m)
{
	key= (keyM+i*c1+i*i*c2)%m;
	i++;
}

hashARR[key].data=data;
hashARR[key].occupied=1;
hashARR[key].deleted=0;
}

int searchq()
{
int data,key;
fscanf(fp,"%d",&data);
int keyM = data%m;
key = keyM;

int i=0;

while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
{
	key= (keyM+i*c1+i*i*c2)%m;
	i++;
	if(i==m) break;
}

if(hashARR[key].data==data) {fprintf(fd,"1\n"); return 1;}
else {fprintf(fd,"-1\n"); return -1;}
}

int deleteq()
{

int data,key;
fscanf(fp,"%d",&data);
int keyM = data%m;
key = keyM;

int i=0;

while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
{
	key= (keyM+i*c1+i*i*c2)%m;
	i++;
	if(i==m) break;
}

if(hashARR[key].data==data)
{
	hashARR[key].data=0;
	hashARR[key].occupied=0;
	hashARR[key].deleted=1;
}
else return 0; 
}




//linear
int linear()
{int i;
	fscanf(fp,"%d",&m);
	hashTable(&hashARR);

	for(i=0;i<m;i++){
	hashARR[i].occupied = 0;
	hashARR[i].deleted = 0;
	}

	

	char op;
	do 
	{
		fscanf(fp,"%s",&op);
		switch(op)
		{
			case 'i': insertl(); break;
			case 's': searchl(); break;
			case 'd': deletel(); break;
			case 'p': print();break;
			default: return 0;
		}

	} while(op!='t');
}

int insertl()
{
int data,key;
fscanf(fp,"%d",&data);
int keyM = data%m;
key = keyM;

int i=0;

while(hashARR[key].occupied==1)
{
	key= (keyM+i)%m;
	i++;
}

hashARR[key].data=data;
hashARR[key].occupied=1;
hashARR[key].deleted=0;
}

int searchl()
{
int data,key;
fscanf(fp,"%d",&data);
int keyM = data%m;
key = keyM;

int i=0;

while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
{
	key= (keyM+i)%m;
	i++;
}

if(hashARR[key].data==data) {fprintf(fd,"1\n"); return 1;}
else {fprintf(fd,"-1\n"); return -1;}
}

int deletel()
{

int data,key;
fscanf(fp,"%d",&data);
int keyM = data%m;
key = keyM;

int i=0;

while(hashARR[key].data!=data&&(hashARR[key].occupied==1||hashARR[key].deleted==1))
{
	key= (keyM+i)%m;
	i++;
}

if(hashARR[key].data==data)
{
	hashARR[key].data=0;
	hashARR[key].occupied=0;
	hashARR[key].deleted=1;
}
else return 0; 
}

int print()
{int i;
for(i=0;i<m;i++)
{
	if(hashARR[i].occupied==0)
	{ fprintf(fd,"%d ()\n",i);}
	else fprintf(fd,"%d (%d)\n", i, hashARR[i].data);
}
}










