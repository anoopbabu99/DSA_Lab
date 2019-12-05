#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* fp;
FILE* fd;


int main() 
{ 
	fp=fopen("input.txt","r");
	fd=fopen("output.txt","w");
	char op[2];
	int opnum=0;
	fscanf(fp,"%s",op);
}