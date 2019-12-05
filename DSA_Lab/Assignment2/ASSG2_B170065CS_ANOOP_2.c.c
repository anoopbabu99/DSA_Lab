//RABIN_KARP q2

#include<stdio.h>
#include<string.h> 
#define d 256 

FILE* fp;
FILE* fd;
void search(char pat[], char txt[], int q);
void modifytext();
void modifypattern();

int q = 13;
char text[100];
char realtext[100];
char pattern[100];
char realpattern[100];
int main() 
{ 
	fp=fopen("input.txt","r");
	fd=fopen("output.txt","w");
	char op[2];
	int opnum=0;
	do
	{
		fscanf(fp,"%s",op);
		if(!strcmp(op,"t")) opnum=1;
		if(!strcmp(op,"p")) opnum=2;
		if(!strcmp(op,"pr")) opnum=3;
		if(!strcmp(op,"e")) opnum=4;
		switch(opnum)
		{
			case 1: fscanf(fp,"%[^\n]", text); modifytext(); break;
			case 2: fscanf(fp,"%[^\n]", pattern); modifypattern(); break;
			case 3: search(realpattern, realtext, q); break;
			default: break;
		}

	} while(opnum!=4); 
	
	fclose(fd);
	fclose(fp);
    
    return 0; 
}

void search(char pat[], char txt[], int q) 
{ 
    int M = strlen(pat); 
    int N = strlen(txt); 
    int i, j; 
    int p = 0; 
    int t = 0; 
    int h = 1; 
   
    for (i = 0; i < M-1; i++) 
        h = (h*d)%q; 
  
    for (i = 0; i < M; i++) 
    { 
        p = (d*p + pat[i])%q; 
        t = (d*t + txt[i])%q; 
    }  
    for (i = 0; i <= N - M; i++) 
    { 
        if ( p == t ) 
        { 
            for (j = 0; j < M; j++) 
            { 
                if (txt[i+j] != pat[j]) 
                    break; 
            } 
            if (j == M) 
                fprintf(fd,"%d ", i); 
        } 
        if ( i < N-M ) 
        { 
            t = (d*(t - txt[i]*h) + txt[i+M])%q; 
            if (t < 0) 
            t = (t + q); 
        } 
    } 
	fprintf(fd,"\n");
} 






void modifypattern()
{
	int n,m;
	n=strlen(pattern);
	int i;
	
	
	for(i=1-1; i<n-1; i++)
        {
            pattern[i] = pattern[i + 1];
        }
        n--;
		
	for(i=1-1; i<n-1; i++)
        {
            pattern[i] = pattern[i + 1];
        }
        n--;
        n--;
	
	for(i=0;i<n;i++)
	{
		realpattern[i]=pattern[i];}
		

}


void modifytext()
{
	int n,m;
	n=strlen(text);
	int i;
	
	
	for(i=1-1; i<n-1; i++)
        {
            text[i] = text[i + 1];
        }
        n--;
		
	for(i=1-1; i<n-1; i++)
        {
            text[i] = text[i + 1];
        }
        n--;
        n--;
	
	for(i=0;i<n;i++)
	{
		realtext[i]=text[i];}
		

}
 