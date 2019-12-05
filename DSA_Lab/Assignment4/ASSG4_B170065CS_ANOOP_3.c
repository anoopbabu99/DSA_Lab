#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) && defined(_MSC_VER)
#pragma warning (disable : 4996)
#endif
FILE * fp;
FILE * fd;

enum { RED, BLACK };

typedef int COLOR;
typedef int valueType;
typedef struct Node {
	valueType value;
	COLOR color;
	struct Node *right, *left, *parent;
}*node;
typedef node* tree;

node initilize(node, valueType);
node grandparent(node);
node uncle(node);
node sibling(node);

node findNode(tree, valueType);

void insertNode(tree, valueType);
void insertUtil(node);

void rotateRight(node);
void rotateLeft(node);

node findNode(tree, valueType);
void replaceNode(tree, node, node);

void printNode(node n);
void inorderInterator(node n, void(*func)(node));
void inorderPrint(tree t);

void vinash(node);
int flag=0;
int i=0;

int main()
{


	fp = fopen("input.txt", "r");
	fd = fopen("output.txt", "w");
	node tree = NULL;
	int x;

	if(fscanf(fp,"%d",&x)==1)
	{
	//fscanf(fp,"%d",&x);
	insertNode(&tree, x);
	inorderPrint(&tree);
	i++;
	}

	node p;

	while(fscanf(fp,"%d",&x)==1)
	{
		//fscanf(fp,"%d",&x);
		//printf("%d\n",x);	
		if(x==0) break;
		insertNode(&tree, x);
		p=findNode(&tree,x);
		replaceNode(&tree, p, p);
		if(flag==1) inorderPrint(&tree);
		i++;
	}

	vinash(tree);
	fclose(fp);

	return 0;
}

node initilize(node p, valueType v)
{
	node tree = (node)malloc(sizeof(struct Node));
	tree->left = tree->right = NULL;
	tree->parent = p;
	tree->value = v;
	tree->color = RED;
	return tree;
}
node grandparent(node n)
{
	if (n == NULL || n->parent == NULL)
		return NULL;
	return n->parent->parent;
}
node uncle(node n)
{
	node g = grandparent(n);
	if (n == NULL || g == NULL)
		return NULL;
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}
node sibling(node n)
{
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}
int colorOf(node n)
{
	return n == NULL ? BLACK : n->color;
}
void insertNode(tree t, valueType v)
{
	int pl = 0;
	node ptr, btr = NULL, newNode;

	for (ptr = *t; ptr != NULL;
	btr = ptr, ptr = ((pl = (ptr->value > v)) ? ptr->left : ptr->right));

		newNode = initilize(btr, v);

	if (btr != NULL)
		(pl) ? (btr->left = newNode) : (btr->right = newNode);
	
	inorderPrint(t);
	flag=0;
	insertUtil(newNode);
	
	
	ptr = newNode;
	for (ptr = newNode; ptr != NULL; btr = ptr, ptr = ptr->parent);
	*t = btr;
}
void insertUtil(node n)
{
	node u = uncle(n), g = grandparent(n), p = n->parent;
	if (p == NULL)
		n->color = BLACK;
	else if (p->color == BLACK)
		return;
	else if (u != NULL && u->color == RED)
	{
		p->color = BLACK;
		u->color = BLACK;
		g->color = RED;
		flag=1;
		insertUtil(g);
	}
	else
	{flag=1;
		if (n == p->right && p == g->left)
		{
			rotateLeft(p);
			n = n->left;
		}
		else if (n == p->left && p == g->right)
		{
			rotateRight(p);
			n = n->right; 
		}

		g = grandparent(n);
		p = n->parent;

		p->color = BLACK;
		g->color = RED;

		if (n == p->left)
			rotateRight(g); 
		else
			rotateLeft(g); 
	}
}
void replaceNode(tree t, node o, node n)
{
	if (o->parent == NULL)
		*t = n;
	else
	{
		if (o == o->parent->left)
			o->parent->left = n;
		else
			o->parent->right = n;
	}

	if (n != NULL)
		n->parent = o->parent;
}

void rotateRight(node tree)
{
	node c = tree->left;
	node p = tree->parent;

	if (c->right != NULL)
		c->right->parent = tree;

	tree->left = c->right;
	tree->parent = c;
	c->right = tree;
	c->parent = p;

	if (p != NULL)
	{
		if (p->right == tree)
			p->right = c;
		else
			p->left = c;
	}
	//printf("rotation %d, right\n", tree->value);
}
void rotateLeft(node tree)
{
	node c = tree->right;
	node p = tree->parent;

	if (c->left != NULL)
		c->left->parent = tree;

	tree->right = c->left;
	tree->parent = c;
	c->left = tree;
	c->parent = p;

	if (p != NULL)
	{
		if (p->left == tree)
			p->left = c;
		else
			p->right = c;
	}
	//printf("rotation %d, left\n", tree->value);
}

node findNode(tree t, valueType v)
{
	node p;
	for (p = *t; p != NULL && p->value != v; p = (p->value > v ? p->left : p->right));
	return p;
}
void printNode(node n)
{
	printf("%d%s", n->value, (n->color == BLACK ? "B" : "R"));
}
void inorderInterator(node n, void(*func)(node))
{
	if (n == NULL)
		return;
	printf("(");
	inorderInterator(n->left, func);
	func(n);
	inorderInterator(n->right, func);
	printf(")");
}
void inorderPrint(tree t)
{
	inorderInterator(*t, printNode);
	if(i!=0) printf("\n");
	i++;
	
}
void vinash(node tree)
{
	if (tree == NULL)
		return;
	vinash(tree->left);
	vinash(tree->right);
	free(tree);
}


