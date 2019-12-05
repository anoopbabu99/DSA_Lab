#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int stack[100];
int top = -1;

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

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

int findIndex(char str[], int begin, int last)
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


struct node* createTree(char str[], int begin, int last)
{
    if(begin > last)
        return NULL;

    int n = 0;
    int flag = 1;
    int index = -1;
    int i;

    struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
    temp->left = NULL;
    temp->right = NULL;

    if(str[begin] == '(' && str[last] == ')')
    {
        for(i = begin+1; i <= last; i++)
        {
            if( isdigit(str[i]) || str[i] == '-')
            {
                if(isdigit(str[i]))
                    n = n*10 + (str[i]-48);
                else if(str[i] == '-')
                    flag = -1;
            }
            else if(str[i] == ' ')
            {}
            
            else if( str[i] == '(' || str[i] == ')')   
                break;
        }

        if( n != 0)
        {
            temp->data = flag*n;
            flag = 1;
        }

        else if( n == 0 )
            return NULL;

        if(str[i] == '(')
        {
            index = findIndex(str,i,last);

            if(index != -1)
            {
                temp->left = createTree(str,i,index);
                temp->right = createTree(str,index+2,last);
            }
        }
        
    }

    return temp;
    
}

int max(int a, int b)
{
    if(a > b)
        return a;
    
    if (a < b)
        return b;
}

int height(struct node* temp) 
{ 
    if (temp==NULL) 
	    return -1; 
    
    int h1 = height(temp->left);
    int h2 = height(temp->right);

    return max(h1,h2) + 1;
}

int diameter(struct node *temp)
{
    if(temp == NULL)
        return 0;
    
    int d1 = height(temp->left) + height(temp->right)+3;
    int d2 = diameter(temp->left);
    int d3 = diameter(temp->right);

    return max(d1, max(d2,d3));
}

int width(struct node *temp, int level)
{
    if(temp == NULL)
        return 0;

    if(level == 1)
        return 1;
    
    else if(level  > 1)
        return width(temp->left, level-1) + width(temp->right, level-1);
}

int main()
{
    FILE *fp;
    FILE *fout;

    fp = fopen("input.txt","r");
    fout = fopen("output.txt","w");
    if(fp == NULL)
    {
        printf("FILE EMPTY\n");
        return 0;
    }

    char s[1000];
    struct node* ROOT = NULL;
    int count = 0;
    int max = -1;

    fscanf(fp,"%[^\n]s",s);

    ROOT = createTree(s,0,strlen(s)-1);

    

    fprintf(fout,"%d ",height(ROOT));
    fprintf(fout,"%d ",diameter(ROOT));

    for(int i=1; i<=height(ROOT)+1; i++)
    {
        int w = width(ROOT, i);
        if(w  > max)
            max = w;
    }

    fprintf(fout,"%d",max);

    fclose(fp);

    return 0;
}