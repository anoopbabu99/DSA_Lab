//AVL_TREE 

 
#include<stdio.h> 
#include<stdlib.h> 

FILE *fp;
FILE *fd;
  

struct Node 
{ 
    int key; 
    struct Node *left; 
    struct Node *right; 
    int height; 
}; 
int flag=0;
int max(int a, int b); 

FILE* fp;
FILE* fd;
  
 
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 
  
 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
  

struct Node* newNode(int key) 
{ 
    struct Node* node = (struct Node*) 
                        malloc(sizeof(struct Node)); 
    node->key   = key; 
    node->left   = NULL; 
    node->right  = NULL; 
    node->height = 1;   
    return(node); 
} 
  
 
struct Node *rightRotate(struct Node *y) 
{ 
    struct Node *x = y->left; 
    if(x==NULL) return y;
    struct Node *T2 = x->right; 
  
    
    x->right = y; 
    y->left = T2; 
  
    
    y->height = max(height(y->left), height(y->right))+1; 
    x->height = max(height(x->left), height(x->right))+1; 
  
    
    return x; 
} 
  
 
struct Node *leftRotate(struct Node *x) 
{ 
    struct Node *y = x->right; 
	if(y==NULL) return x;
    struct Node *T2 = y->left; 
  
    
    y->left = x; 
    x->right = T2;
  
   
    x->height = max(height(x->left), height(x->right))+1; 
    y->height = max(height(y->left), height(y->right))+1; 
  
    
    return y; 
} 
  
 
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
}

 
  
struct Node* insert(struct Node* node, int key) 
{ 
    
    if (node == NULL) 
        return(newNode(key)); 
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
    else 
        return node; 
  
    
    node->height = 1 + max(height(node->left), 
                           height(node->right)); 
  
 
    int balance = getBalance(node); 
  
    
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 
  
     
    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 
  
    
    if (balance > 1 && key > node->left->key) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
  
    
    if (balance < -1 && key < node->right->key) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
  
    
    return node; 
} 
  
struct Node * minValueNode(struct Node* node) 
{ 
    struct Node* current = node; 
  
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 
  
struct Node* deleteNode(struct Node* root, int key) 
{ 
    
  
    if (root == NULL) 
        return root; 
    if ( key < root->key ) 
        root->left = deleteNode(root->left, key); 
  
    
    else if( key > root->key ) 
        root->right = deleteNode(root->right, key); 
  
    
    else
    { 
        
        if( (root->left == NULL) || (root->right == NULL) ) 
        { 
            struct Node *temp = root->left ? root->left : 
                                             root->right; 
  
            
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else  
             *root = *temp;  
            free(temp); 
        } 
        else
        { 
            
            struct Node* temp = minValueNode(root->right); 
  
            
            root->key = temp->key; 
  
            
            root->right = deleteNode(root->right, temp->key); 
        } 
    } 
   
    if (root == NULL) 
      return root; 
  
     
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
  
    
    int balance = getBalance(root); 
  
    
    if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
 
    if (balance > 1 && getBalance(root->left) < 0) 
    { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    
    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    if (balance < -1 && getBalance(root->right) > 0) 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
  
    return root; 
}


void preOrder(struct Node* root) 
{
	if (root == NULL) 
	{
		fprintf(fd,"()");
		return;
	} 

	fprintf(fd,"(%d", root->key); 
	if (root->left==NULL&&root->right==NULL){}
	else 
    	{	
		preOrder(root->left); 
		preOrder(root->right);
	}
	 
	 fprintf(fd,")");
}

void preOrder2(struct Node* root) 
{
	if(getBalance(root)<-1||getBalance(root)>1)  flag =1;
	
	if (root == NULL) 
	{
		//printf("()");
		return;
	} 
	//printf("(%d", root->key); 
	if (root->left==NULL&&root->right==NULL){}
	else 
    	{	
		preOrder2(root->left); 
		preOrder2(root->right);
	}
	 
	 //printf(")");
}





struct Node* searchp(struct Node* root, int x)
{

struct Node* curr;
struct Node* p;
	if(root->key==x) {flag =1; return root; }
	else
	{
		
		curr = root;
		while(curr)
		{
			if(x>curr->key)
			{
				p=curr;
				curr=curr->right;
			}
			else if(x<curr->key)
			{
				p=curr;
				curr=curr->left;
				
			}
			else if (x==curr->key)
			{
				break;
			}
			
		}
	return p;
	}	
}

struct Node* search(struct Node* root, int x)
{

struct Node* curr;
struct Node* p;
	if(root->key==x) return root;
	else
	{
		
		curr = root;
		while(curr)
		{
			p=curr;
			if(x>curr->key)
			{
				curr=curr->right;
			}
			else if(x<curr->key)
			{
				
				curr=curr->left;	
				
			}
			else if (x==curr->key)
			{
				break;
			}
			
			
		}
	return p;
	}	
}



int main() 
{ 
struct Node *root = NULL; 
struct Node *temp,*c,*p;
int op,x;
fp= fopen("input.txt", "r");
fd= fopen("output.txt", "w");
  do
	{
		fscanf(fp,"%d", &op);
		switch(op)
		{
			case 1: fscanf(fp,"%d", &x); root = insert(root,x);break;
			case 2: fscanf(fp,"%d", &x); root = deleteNode(root,x);break;
			case 3: flag=0;
				fscanf(fp,"%d", &x);
				p= searchp(root,x);
				

				if(flag==0)
				{
					if(p->left!=NULL)
					{
						if(p->left->key==x) p->left = leftRotate(p->left);
					}
					if(p->right!=NULL)
					{
						if(p->right->key==x) p->right = leftRotate(p->right);
					}	
				}
				else {root = leftRotate(root); flag=0; }
				fprintf(fd,"\n");
				break;
			case 4: flag=0;
				fscanf(fp,"%d", &x);
				p= searchp(root,x);
				

				if(flag==0)
				{
					if(p->left!=NULL)
					{
						if(p->left->key==x) p->left = rightRotate(p->left);
					}
					if(p->right!=NULL)
					{
						if(p->right->key==x) p->right = rightRotate(p->right);
					}	
				}
				else {root = rightRotate(root); flag=0;}
				fprintf(fd,"\n");
				break;
			
			case 5: fscanf(fp,"%d", &x);
				c = search(root,x);
				x=getBalance(c); 
				fprintf(fd,"%d",x);
				fprintf(fd,"\n");
				break;
			case 6: preOrder(root); fprintf(fd,"\n");break;
			case 7: preOrder2(root);
				if(flag==1) fprintf(fd,"FALSE"); 
				else fprintf(fd,"TRUE"); 
				flag=0;
				fprintf(fd,"\n");
				break;
			case 8: fscanf(fp,"%d", &x); 
				c=search(root,x); 
				if(c->key==x) fprintf(fd,"TRUE");
				else fprintf(fd,"FALSE");
				fprintf(fd,"\n");
				break;
			case 9: return 0; break;
		}
		
	}while(op!='9');
  
  
    return 0; 
} 

