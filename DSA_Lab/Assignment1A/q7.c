#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *root = NULL;

int stack[1000];
int top = -1;

void push(char x)
{
    stack[++top] = x;
}
 
char pop()
{
    if(top == -1)
		printf("\n");
    else
        top--;
}

int find_subtree(char str[], int begin, int last)
{
    if(begin > last) 
        return -1;

    for(int i=begin; i<last; i++)
    {
        if(str[i] == '(')
            push(str[i]);
        else if(str[i] == ')')
        { 
            if(stack[top] == '(')
                pop();

            if(top == -1)
                return i;
        }
    }

    return -1;
}

struct node* tree_logic(char str[], int begin, int last)
{
    if(begin > last)
        return NULL;

    int n= 0;
    int pole=0 ;
    int i=0;

    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->left = NULL;
    temp->right = NULL;

    if(str[begin] == '(' && str[last] == ')')
    {
        for(i = begin+1; i <= last; i++)
        {
            if( isdigit(str[i]) )
            {
                n = n*10 + (str[i]-48);
            }
            else if(str[i] == ' ')
            {}
            
            else if( str[i] == '(' || str[i] == ')')   
                break;
        }

        if( n != 0)
            temp->data = n;
        
        else if( n == 0 )
            return NULL;

        if(str[i] == '(')
        {
            pole = find_subtree(str,i,last);

            if(pole != -1)
            {
                temp->left = tree_logic(str,i,pole);
                temp->right = tree_logic(str,pole+2,last);
            }
        }
        
    }
    return temp;
}



void create_tree()
{
    char s[1000];

    scanf(" %[^\n]s",s);
    root = tree_logic(s,0,strlen(s)-1);   

    
}

void print(struct node *p)
{
	if(p == NULL)
    {
        printf("( ) ");
        return;
    }

	else
	{
		printf("( ");
        printf("%d ",p->data);
        
        if(p->left == NULL && p->right == NULL)
        {
        
        }
        else
        {
            print(p->left);
		    print(p->right);
        }
        printf(") ");
	}
}

struct node* mirror(struct node *p)
{
    if(p ==  NULL || p->left == NULL && p->right == NULL)
        return p;
    
    struct node *temp;

    temp = p->left;
    p->left = p->right;
    p->right = temp;

    mirror(p->left);
    mirror(p->right);

    return p; 
}


int main()
{
    int i = 0;
    char ch;
    struct node *p = NULL;
	struct node *q = NULL;

    while(1)
    {
        scanf("%c",&ch);

        switch(ch)
        {
            case 'c':
                        create_tree();
                        break;
            case 'p':
                        q = root;
                        print(q);
                        printf("\n");
                        break;
            case 'm':
                        q = root;
                        p = mirror(q);
                        root = p;
                        break;
            case 's':
                        return 0;

        }
    }

    return 0;
}