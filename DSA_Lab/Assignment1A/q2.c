#include<stdio.h>
#include <ctype.h>

char stack[20];
int top = -1;

void push(char x);
char pop();
int priority(char x);

int main()
{
    char exp[20];
    char x;
    printf("Enter the expression: ");
    scanf("%s",exp);
	int i =0;
    while(exp[i] != '\0')
    {
        if(isalnum(exp[i]))
            printf("%c",exp[i]);
        else if(exp[i] == '(')
            push(exp[i]);
        else if(exp[i] == ')')
        {
            while((x = pop()) != '(')
                printf("%c", x);
        }
        else
        {
            while(priority(stack[top]) >= priority(exp[i]))
                printf("%c",pop());
            push(exp[i]);
        }
        i++;
    }
    while(top != -1)
    {
        printf("%c",pop());
    }
}

void push(char x)
{
	top = top +1;
    stack[top] = x;
}
 
char pop()
{
    if(top == -1)
        return -1;
    else
	{
		top=top-1;
        return stack[top+1];
	}
}
 
int priority(char x)
{
    if(x == '(')
        return 0;
    if(x == '+' || x == '-')
        return 1;
    if(x == '*' || x == '/')
        return 2;
	if(x == '^')
        return 3;
	
}