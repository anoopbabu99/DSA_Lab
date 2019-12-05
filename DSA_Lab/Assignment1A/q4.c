// Binary Search Tree.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	int data;
	struct node* left;
	struct node* right;
	struct node* parent;
};

void insert(int x);
int search(int key);
void findMIN();
void findMAX();
int predecessor(int key);
int successor(int key);
void delete(int key);
void inorder(struct node* x);
void preorder(struct node* x);
void postorder(struct node* x);


struct node* root = NULL;

FILE* fp;
FILE* fd;

int main()
{
	fp = fopen("input.txt","r");
	fd = fopen("output.txt","w");
	char s[4];
	int sc,p;
	int x=-1;
	while((fscanf(fp,"%s",s))==1)
	{
		if(strcmp(s,"insr")==0)
		{
			fscanf(fp,"%d",&x);
			insert(x);
		}
		if(strcmp(s,"srch")==0)
		{
			fscanf(fp,"%d",&x);
			sc=search(x);
			if(sc==1) fprintf(fd,"FOUND\n");
			if(sc==2) fprintf(fd,"NOT FOUND\n");
		}
		if(strcmp(s,"minm")==0)
		{
			findMIN();
		}
		if(strcmp(s,"maxm")==0)
		{
			findMAX();
		}
		if(strcmp(s,"pred")==0)
		{
			fscanf(fp,"%d",&x);
			p=predecessor(x);
			if(p!=-1&&p!=-2) fprintf(fd,"%d",p);
		}
		if(strcmp(s,"succ")==0)
		{
			fscanf(fp,"%d",&x);
			sc=successor(x);
			if(sc!=-1&&sc!=-2) fprintf(fd,"%d",sc);
		}
		if(strcmp(s,"delt")==0)
		{
			fscanf(fp,"%d",&x);
			delete(x);
		}
		if(strcmp(s,"inor")==0)
		{
			inorder(root);
			fprintf(fd,"\n");
		}
		if(strcmp(s,"prer")==0)
		{
			preorder(root);
			fprintf(fd,"\n");
		}
		if(strcmp(s,"post")==0)
		{
			postorder(root);
			fprintf(fd,"\n");
		}
		if(strcmp(s,"stop")==0)
		{
			
			return 0;
		}
		
	}

	
	fclose(fp);
	fclose(fd);
}

void insert(int x)
{
	struct node* temp, *p;
	temp= (struct node*)malloc(sizeof(struct node));
	temp->data=x;
	temp->left=NULL;
	temp->right=NULL;
	temp->parent = NULL;
	if(root==NULL)
	{
		root=temp;
	}
	else
	{
		p=root;
		struct node* current;
		current = root;
		while(current)
		{
			p=current;
			if(temp->data>current->data)
			{
				current=current->right;
			}
			else
			{
				current=current->left;
			}
		}
			if(temp->data>p->data)
			{
				p->right=temp;
			}
			else
			{
				p->left=temp;
			}
	}
	temp->parent= p;
}

int search(int key)
{
	
	struct node* current, * p;
	current = root;
	p= root; 
	
	while(current)
		{
			p=current;
			
			if(key>current->data)
			{
				current=current->right;
			}
			else if(key<current->data)
			{
				current=current->left;
			}
			else return 1;
		}
		
		if (current==NULL) return 2;
	
}

void findMIN()
{
	struct node* temp;
	temp = root;
	
	if(root==NULL) {fprintf(fd,"NIL\n"); return;}
		
	while(temp->left!=NULL)
	{
		temp= temp->left;
	}
	
	fprintf(fd,"%d\n", temp->data);
	
}


void findMAX()
{
	struct node* temp;
	temp = root;
	
	if(root==NULL) {fprintf(fd,"NIL\n"); return;}
		
	while(temp->right!=NULL)
	{
		temp= temp->right;
	}
	
	fprintf(fd,"%d\n", temp->data);
	
}	

int predecessor(int key)
{
	struct node* current, * p;
	current = root;
	p= root; 
	int c=0;
	
	if(root==NULL) {fprintf(fd,"NOT FOUND\n"); return -1;}
	if(search(key)==2) {fprintf(fd,"NOT FOUND\n"); return -1;}
	while(current)
		{
			p=current;
			
			if(key>current->data)
			{
				current=current->right;
			}
			else if(key<current->data)
			{
				current=current->left;
			}
			else current=NULL;
		}
	
	if(p->left!=NULL)
	{ c++;
		p = p->left;
		while(p->right!=NULL)
	{
		p= p->right;
	} return p->data;
	}
	
	else
	{c++;
		struct node* y;
		if (p->parent==NULL) {fprintf(fd,"NIL\n");return-1 ;}
		y= p->parent;
		while(y!=NULL&&p==y->left)
		{
			p=y;
			y=y->parent;
		}
		if(y) return y->data;
		else {fprintf(fd,"NIL\n");return-2 ;}
	}
	
	if(c==0) return -2;
}

int successor(int key)
{
	struct node* current, * p;
	current = root;
	p= root; 
	if(root==NULL) {fprintf(fd,"NOT FOUND\n"); return -1;}
	if(search(key)==2) {fprintf(fd,"NOT FOUND\n"); return -1;}
	
	while(current)
		{
			p=current;
			
			if(key>current->data)
			{
				current=current->right;
			}
			else if(key<current->data)
			{
				current=current->left;
			}
			else current=NULL;
		}
	
	if(p->right!=NULL)
	{ p = p->right;
		while(p->left!=NULL)
	{
		p= p->left;
	} return p->data;
	}
	
	else
	{
		struct node* y;
		
		y= p->parent;
		while(y!=NULL&&p==y->right)
		{
			p=y;
			y=y->parent;
		}
		if(y) return y->data;
		else {fprintf(fd,"NIL\n");return-1 ;}
	}
}

void inorder(struct node* x) 
{ 
     if (x == NULL) return; 
     inorder(x->left); 
     fprintf(fd,"%d ", x->data);   
     inorder(x->right); 
} 

void preorder(struct node* x) 
{ 
     if (x == NULL) return; 
	 fprintf(fd,"%d ", x->data);
     preorder(x->left);
     preorder(x->right); 
} 

void postorder(struct node* x) 
{ 
     if (x == NULL) return; 
     postorder(x->left);
     postorder(x->right); 
	 fprintf(fd,"%d ", x->data);
} 

void delete(int key)
{
	struct node* current, * z;
	current = root;
	z= root; 
	
	while(current)
		{
			z=current;
			
			if(key>current->data)
			{
				current=current->right;
			}
			else if(key<current->data)
			{
				current=current->left;
			}
			else current = NULL;
		}
		int y_int;
		struct node* y;
		struct node* x;
		
		if(z->left==NULL && z->right==NULL)
		{
			y=z;
		}
		else 
		{	
			y_int = successor(key);
			current = root;
			y= root; 
	
			while(current)
			{
				y=current;
			
				if(y_int>current->data)
				{
					current=current->right;
				}
				else if(y_int<current->data)
				{
					current=current->left;
				}
				else current = NULL;
			}
			
			
		}
		if(y->left!=NULL)
		{
			x=y->left;
		}
		else x=y->right;
		if(x!=NULL)
		{
			x->parent=y->parent;
		}
		if(y->parent==NULL)
		{
			root=x;
		}
		else if(y==y->parent->left)
		{
			y->parent->left=x;
		}
		else y->parent->right = NULL;
		if(y!=z)
		{
			z->data=y->data;
			z->parent = y->parent;
		}
		free(y);
}
		
	





	
	

