//q6.c Dynamic Binary Search
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* fp;
FILE* fd;

int *row[30];
int lastrow=0;
void dbs_insert(int v);
void dbs_search(int v);
int *dbs_merge(int *a, int *b, int len);
void dbs_print();
int power(int a, int b);
void dbs_search(int v);
int binarySearch(int arr[], int l, int r, int x);

int main()
{
char ch; int x;
fp =fopen("input.txt", "r");
fd =fopen("output.txt", "w");
	do
	{
	
	fscanf(fp,"%c", &ch);
		switch(ch)
		{
			case 'i': fscanf(fp,"%d", &x); dbs_insert(x); break;
			case 's': fscanf(fp,"%d", &x); dbs_search(x); fprintf(fd,"\n"); break;
			case 'p': dbs_print(); fprintf(fd,"\n"); break;
			case 'x': fprintf(fd,"\n"); break;
		}
	}while(ch!='x');


}

void dbs_search(int v)
{int i,x=-1;
	for(i=0; i<=lastrow; i++)
	{
		if(row[i] == NULL) continue;
		else
		{
			x=binarySearch(row[i], 0, power(2,i), v);
			if(x!=-1) break;
			if(x==-1) continue;
		}
	}
	if(x!=-1) fprintf(fd,"1");
	else fprintf(fd,"NIL");
}





// A iterative binary search function. It returns 
// location of x in given array arr[l..r] if present, 
// otherwise -1 
int binarySearch(int arr[], int l, int r, int x) 
{ 
    while (l <= r) { 
        int m = l + (r - l) / 2; 
  
        // Check if x is present at mid 
        if (arr[m] == x) 
            return m; 
  
        // If x greater, ignore left half 
        if (arr[m] < x) 
            l = m + 1; 
  
        // If x is smaller, ignore right half 
        else
            r = m - 1; 
    } 
  
    // if we reach here, then element was 
    // not present 
    return -1; 
} 

//search





void dbs_print() {
int i, j;
	for(i=0; i<=lastrow; i++)
	{
		if(row[i] == NULL) continue;
		else
		{
			for(j=0;j<power(2,i);j++)
			{	
				fprintf(fd,"%d ", *(row[i]+j));
			}
		}
	}
}

int power(int a, int b)
{int x=a,i;
if(b!=0)
{
	for(i=0;i<b;i++)
	{
		a=x;
		x=2*a;
	}
	return a;
}
if(b==0) return 1;
}

void dbs_insert(int v) {
    int *new_row;
    int i;
    new_row=malloc(sizeof(int));
    new_row[0]=v;
    i=0;
    while (row[i]!=NULL) {
        new_row=dbs_merge(row[i],new_row,1<<i);
        row[i]=NULL;
        i++;
    }
    row[i]=new_row;
    if (i>lastrow) lastrow=i;
}

int *dbs_merge(int *a, int *b, int len) {
    int ai=0;
    int bi=0;
    int ci=0;
    int *c;
    c=malloc((2*len)*sizeof(int));
    while (ai <len && bi < len) {
        if (a[ai]<=b[bi]) {
            c[ci++]=a[ai++];
        } else {
            c[ci++]=b[bi++];
        }
    }
    while (ai<len)
        c[ci++]=a[ai++];
    while (bi<len)
        c[ci++]=b[bi++];
    free(a);
    free(b);
    return c;
}
