//q5.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* fp;
FILE* fd;
int main()
{
	int n, i=0,x,y,flag;
	int j=0;
	char ch;
	int a[100][100];
	fp = fopen("input.txt","r");
	fd = fopen("output.txt","w");
	do
	{
	fscanf(fp,"%c",&ch);
	
		switch(ch)
		{	
			case 'a': getc(fp); getc(fp);
				while(ch!=')')
				{
					fscanf(fp,"%d",&a[i][j]);
					ch = getc(fp);
					i++;
				}
				n=i;
				fprintf(fd,"(");
				for(i=0;i<n;i++)
				{fprintf(fd,"%d ",a[i][j]);}
				i=n+1;
				fscanf(fp,"%d",&a[i][j]);
				fprintf(fd,"%d)",a[i][j]);
				j++;
				i=0;
				fprintf(fd,"\n");
				break;

			case 'c': getc(fp); getc(fp);
				while(ch!=')')
				{
					fscanf(fp,"%d",&a[i][j]);
					ch = getc(fp);
					i++;
				}
				getc(fp); ch=getc(fp);
				while(ch!=')')
				{
					fscanf(fp,"%d",&a[i][j]);
					ch = getc(fp);
					i++;
				}
				n=i;
				fprintf(fd,"(");
				for(i=0;i<n-1;i++)
				{fprintf(fd,"%d ",a[i][j]);}
				fprintf(fd,"%d)",a[n-1][j]);
				j++;
				i=0;
				fprintf(fd,"\n");
				break;
			case 'm': getc(fp); getc(fp);
				while(ch!=')')
				{
					fscanf(fp,"%d",&a[i][j]);
					ch = getc(fp);
					i++;
				}
				n=i;
				fscanf(fp,"%d",&x);
				flag = 0;
				for(i=0;i<n;i++)
				{
					if(a[i][j]==x) flag =1;
				}
				if(flag==1) fprintf(fd,"1");
				else fprintf(fd,"0");
				flag =0;
				j++;
				i=0;
				fprintf(fd,"\n");
				break;
			case 'l': getc(fp); getc(fp);
				while(ch!=')')
				{
					fscanf(fp,"%d",&a[i][j]);
					ch = getc(fp);
					i++;
				}
				n=i;
				fprintf(fd,"%d",n);
				i=0;
				j++;
				fprintf(fd,"\n");
				break;
			case 's': getc(fp); getc(fp);
				while(ch!=')')
				{
					fscanf(fp,"%d",&a[i][j]);
					ch = getc(fp);
					i++;
				}
				fscanf(fp,"%d",&x);
				fscanf(fp,"%d",&y);
				for(i=x-1;i<y;i++)
				{
					if(i==y-1) fprintf(fd,"%d ",a[i][j]);
					else fprintf(fd,"%d ",a[i][j]);
					
				}
				i=0;
				j++;
				fprintf(fd,"\n");
				break;
		}
	}while(ch!='x');


}


