#include<stdio.h>
#include<stdlib.h>
#include<string.h>




int n;
char s[20];
int a[20];

int main()
{
	int i=0,j=0;
	scanf("%s",s);
	printf("string = %s\n",s);
	n=strlen(s);
	printf("n=%d\n\n",n);
	int c=0;
	while(j<n)
	{
		if(s[j]!=' ')
		{
		a[j]=1;
		i=j+1;
		c++;
		while(i<n)
		{
			if(s[i]==s[j])
			{
				a[j]=a[j]+1;
				s[i]=' ';
				i++;
			}
			else i++;
		} j++;
		}
		else 
		{
			for(i=j;i<n-1;i++)
			{
			s[i]=s[i+1];
			} n--;
			
		}
	}
	i=0;
	
	while(i<c)
	{
		
		printf("%c=%d\n",s[i],a[i]);
		i++;
		
	}
	
	
	
}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	