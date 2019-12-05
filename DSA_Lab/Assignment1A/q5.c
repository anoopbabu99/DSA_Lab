#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	int data;
	struct node* left;
	struct node* right;
};

struct node* root= NULL;

void insert(int x);
void preorder(struct node* x);

FILE* fp;
int main()
{
	int n, i=0,x;
	fp = fopen("input.txt","r");
	fscanf(fp,"%d",&n);
	while(i<n)
	{
		fscanf(fp,"%d",&x);
		insert(x);
		i++;
	}
	preorder(root);
	
}

void insert(int x)
{
	struct node* temp, *p;
	temp= (struct node*)malloc(sizeof(struct node));
	temp->data=x;
	temp->left=NULL;
	temp->right=NULL;
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
}

void preorder(struct node* x) 
{
     if (x == NULL) return; 
	 
	 printf("( %d ", x->data);
     if(x->left!=NULL) preorder(x->left);
	 else printf("( )");
     if(x->right!=NULL) preorder(x->right); 
	 else printf("( )");
	 
	 printf(") ");
}

