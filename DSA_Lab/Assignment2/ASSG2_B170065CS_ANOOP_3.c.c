//SYMMETRIC PAIRS q3
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE* fp;
FILE* fd;
int array1[100];
int array2[100];
int k=0;
int n=0;
int store();
int print();

int main()
{
	char op;
	char ch;
	fp=fopen("input.txt","r");
	fd=fopen("output.txt","w");
	do{
		fscanf(fp,"%s",&op);
		getc(fp);
		ch=getc(fp);
		
	switch(op)
	{
		case 's': store(); break;
		case 'p': print(); 
				  if(ch=='e') return 0;
				  break;
		default: return 0; 
	}
	}while(op!='e');
	
}

int store()
{
	int x,y;
	fscanf(fp,"%d",&x);
	getc(fp);
	fscanf(fp,"%d",&y);
	getc(fp);
	array1[k]=x;
	array2[k]=y;
	k++;
	n=k;
}

int print()
{
	
   int i, j; 
   int p=0;
   int brr1[100];
   int brr2[100];
   for (i = 0; i < n; i++)       
   {
       for (j = i+1; j < n; j++)  
	   {
           if (array1[i] == array2[j]) 
		   {
			   brr1[p]=i;
			   brr2[p]=j;
			   p++;
		   }
	   }
   }
   
   
   
  for(i=0;i<p;i++)
   {
	   if(array1[brr2[i]]==array2[brr1[i]])
	   {
		   fprintf(fd,"(%d,%d)\n",array1[brr1[i]],array1[brr2[i]]);
		   
	   }
   }
   
   
}
	   
	   
				
			   
         
		
		


			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
	