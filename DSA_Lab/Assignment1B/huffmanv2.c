//HUFFMAN TREE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char t[1000];
int stat=0;
FILE* fp;
FILE* fd;
int wildcard=1;

#define MAX_TREE_HT 100 
  

struct MinHeapNode { 
  
   
    char data; 
	int wildcard;
    unsigned freq; 
    struct MinHeapNode *left, *right; 
}; 
  

struct MinHeap { 

    unsigned size; 
    unsigned capacity; 
    struct MinHeapNode** array; 
}; 
  
struct MinHeapNode* newNode(char data,int wildcard, unsigned freq) 
{ 
    struct MinHeapNode* temp 
        = (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 
  
    temp->left = temp->right = NULL; 
    temp->data = data; 
    temp->freq = freq; 
  
    return temp; 
}
 
struct MinHeap* createMinHeap(unsigned capacity) 
  
{ 
  
    struct MinHeap* minHeap 
        = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
   
    minHeap->size = 0; 
  
    minHeap->capacity = capacity; 
  
    minHeap->array 
        = (struct MinHeapNode**)malloc(minHeap-> 
capacity * sizeof(struct MinHeapNode*)); 
    return minHeap; 
} 
  
void swapMinHeapNode(struct MinHeapNode** a, 
                     struct MinHeapNode** b) 
  
{ 
  
    struct MinHeapNode* t = *a; 
    *a = *b; 
    *b = t; 
} 
  
void minHeapify(struct MinHeap* minHeap, int idx) 
{
    int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
	
  
    if (left < minHeap->size && minHeap->array[left]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = left; 
  
    if (right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
        smallest = right; 
			
  
    if (smallest != idx) { 
        swapMinHeapNode(&minHeap->array[smallest], 
                        &minHeap->array[idx]); 
        minHeapify(minHeap, smallest); 
    } 
	
} 
  

int isSizeOne(struct MinHeap* minHeap) 
{ 
  
    return (minHeap->size == 1); 
} 
  

struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
  
{  
    struct MinHeapNode* temp = minHeap->array[0]; 
	
    minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
  
    --minHeap->size; 
    minHeapify(minHeap, 0); 
	
    return temp;
} 

void sort(struct MinHeap* minHeap)
{
	int i,j;
	for (i = 0 ; i < minHeap->size ; i++)
  {
    for (j = i+1 ; j < minHeap->size; j++)
    {
	if(minHeap->array[i]-> wildcard==0&&minHeap->array[j]-> wildcard==0)
	{
	  if((minHeap->array[i]-> freq==minHeap->array[j]-> freq)&& (minHeap->array[i]-> data>minHeap->array[j]-> data))
	  
	  {
		  swapMinHeapNode(&minHeap->array[i],  &minHeap->array[j]); 
	  }
    }
	}
  }
  
  for (i = 0 ; i < minHeap->size ; i++)
  {
    for (j = i+1 ; j < minHeap->size; j++)
    {
	if(minHeap->array[i]-> wildcard!=0&&minHeap->array[j]-> wildcard!=0)
	{
	  if(minHeap->array[i]-> wildcard>minHeap->array[j]-> wildcard)
	  
	  {
		  swapMinHeapNode(&minHeap->array[i],  &minHeap->array[j]); 
	  }
    }
	}
  }
}
	
 

void insertMinHeap(struct MinHeap* minHeap, 
                   struct MinHeapNode* minHeapNode) 
  
{ 
  
    ++minHeap->size; 
    int i = minHeap->size - 1; 
  
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
  
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    minHeap->array[i] = minHeapNode; 
} 


void buildMinHeap(struct MinHeap* minHeap) 
  
{ 
  
    int n = minHeap->size - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i) 
        minHeapify(minHeap, i); 
} 
  

void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        fprintf(fd,"%d", arr[i]); 
  
    fprintf(fd," "); 
} 
  

int isLeaf(struct MinHeapNode* root) 
  
{
    return !(root->left) && !(root->right); 
} 
  

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
  
{ 
  
    struct MinHeap* minHeap = createMinHeap(size); 
  
    for (int i = 0; i < size; ++i) 
        minHeap->array[i] = newNode(data[i], 0,freq[i]); 
  
    minHeap->size = size; 
    buildMinHeap(minHeap); 
  
    return minHeap; 
} 
  

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 
  
{ 
    struct MinHeapNode *left, *right, *top; 
  

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 
  
    while (!isSizeOne(minHeap)) { 
	sort(minHeap);
  
        left = extractMin(minHeap); 
        right = extractMin(minHeap); 
		
		
  
	top = newNode('}', wildcard, left->freq + right->freq); 
	wildcard++;
  
        top->left = left; 
        top->right = right; 
  
        insertMinHeap(minHeap, top); 
    }
  
    
    return extractMin(minHeap); 
} 
  

void printCodes(struct MinHeapNode* root, int arr[], int top) 
  
{ 

  
    
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
  
    
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 
  
   
    if (isLeaf(root)) { 
		if(root->data==t[stat])
		{
        
        printArr(arr, top); 
		stat++;
		}
		
    } 
} 
  

void HuffmanCodes(char data[], int freq[], int size) 
  
{ 
  
    struct MinHeapNode* root 
        = buildHuffmanTree(data, freq, size); 
  
    
    int arr[MAX_TREE_HT], top = 0; 
  
    printCodes(root, arr, top); 
} 
  
	

int main()
{
	int c=0;
	int n, tlen;
	int a[1000];
	char s[1000];
	int i=0,j=0;
	
	fp=fopen("input.txt","r");
	fd=fopen("output.txt","w");
	
	fscanf(fp,"%s",s);
	
	
	n=strlen(s);
	
	for(i=0;i<n;i++)
	{ t[i] = s[i]; }
	tlen=strlen(t);
	
	i=0;
	
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
	
	
	
	
	int temp1;
	char temp2;
	for (i = 0 ; i < c ; i++)
  {
    for (j = i+1 ; j < c; j++)
    {
      if (a[i] > a[j]) 
      {
        temp1       = a[j];
        a[j]   = a[i];
        a[i] = temp1;
		temp2       = s[j];
        s[j]   = s[i];
        s[i] = temp2;
      }
	  if(a[i]==a[j]&&s[i]>s[j])
	  {
		 temp1       = a[j];
        a[j]   = a[i];
        a[i] = temp1;
		temp2       = s[j];
        s[j]   = s[i];
        s[i] = temp2;
	  }
    }
  }
	
	
	
	
	int size = c;
	
  
	for(i=0;i<tlen;i++)
	{
	HuffmanCodes(s, a, size);
	}
	
	fprintf(fd,"\n");
  
    return 0; 



}
	
	
	
	
	
	
	
