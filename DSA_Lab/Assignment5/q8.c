#include<stdio.h>
#include<stdlib.h>
struct list
{
	int data;
	struct list *left,*right,*parent;
};
typedef struct list node;
node *root=NULL;

node *createTree(node *temp,int a[],int p,int n)
{
	if(p<n)
	{
		node *temp2;
		temp2=(node*)malloc(sizeof(node));
		temp2->data=a[p];
		temp2->left=NULL;temp2->right=NULL;temp2->parent=NULL;
		temp=temp2;
		temp->left=createTree(temp->left,a,2*p+1,n);
		temp->right=createTree(temp->right,a,2*p+2,n);
	}
	return temp;
}

void inorder(node *temp)
{
	if(temp!=NULL)
	{
		inorder(temp->left);
		printf("%d ",temp->data);
		inorder(temp->right);
	}
}

void preorder(node *temp)
{
	if(temp!=NULL)
	{
		printf("%d ",temp->data);
		preorder(temp->left);
		preorder(temp->right);
	}
}

void postorder(node *temp)
{
	if(temp!=NULL)
	{
		postorder(temp->left);
		postorder(temp->right);
		printf("%d ",temp->data);	
	}
}
		
	
	
int main()
{
	int n,a[100],i;
	printf("Enter the size of the array:");
	scanf("%d",&n);
	printf("\nEnter the array elements:");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
        root=createTree(root,a,0,n);
	printf("\nInorder traversal:");
	inorder(root);
	printf("\nPreorder traversal:");
	preorder(root);
	printf("\nPostorder traversal:");
	postorder(root);
	return 0;
}
	
