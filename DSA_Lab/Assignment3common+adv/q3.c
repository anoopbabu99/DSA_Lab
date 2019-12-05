#include <stdio.h>
#include <stdlib.h>
 
  
// Structure of node 
int garb;
int a,b=10;

int size=0;

typedef struct node node;
struct node 
{ 
    int data, degree; 
    node *parent, *child, *sibling; 
}; 
  
// Making root global to avoid one extra 
// parameter in all functions. 
node *root = NULL; 
  
// link two heaps by making h1 a child 
// of h2. 
int binomialLink(node *h1, node *h2) 
{ 
    h1->parent = h2; 
    h1->sibling = h2->child; 
    h2->child = h1; 
    h2->degree = h2->degree + 1; 
} 
  
// create a node 
node *createNode(int n) 
{ 
    node *new_node =(struct node*)malloc(sizeof(struct node)); 
    
    new_node->data = n; 
    new_node->parent = NULL; 
    new_node->sibling = NULL; 
    new_node->child = NULL; 
    new_node->degree = 0; 
    return new_node; 
} 
  
// This function merge two Binomial Trees 
node *mergeBHeaps(node *h1, node *h2) 
{ 
    if (h1 == NULL) 
        return h2; 
    if (h2 == NULL) 
        return h1; 
  
    // define a node 
    node *res = NULL; 
  
    // check degree of both node i.e. 
    // which is greater or smaller 
    if (h1->degree <= h2->degree) 
        res = h1; 
  
    else if (h1->degree > h2->degree) 
        res = h2; 
  
    // traverse till if any of heap gets empty 
    while (h1 != NULL && h2 != NULL) 
    { 
        // if degree of h1 is smaller, increment h1 
        if (h1->degree < h2->degree) 
            h1 = h1->sibling; 
  
        // Link h1 with h2 in case of equal degree 
        else if (h1->degree == h2->degree) 
        { 
            node *sib = h1->sibling; 
            h1->sibling = h2; 
            h1 = sib; 
        } 
  
        // if h2 is greater 
        else
        { 
            node *sib = h2->sibling; 
            h2->sibling = h1; 
            h2 = sib; 
        } 
    } 
    return res; 
} 
  
// This function perform union operation on two 
// binomial heap i.e. h1 & h2 
node *unionBHeaps(node *h1, node *h2) 
{ 
    if (h1 == NULL && h2 == NULL) 
       return NULL; 
  
    node *res = mergeBHeaps(h1, h2); 
  
    // Traverse the merged list and set 
    // values according to the degree of 
    // Nodes 
    node *prev = NULL, *curr = res, 
         *next = curr->sibling; 
    while (next != NULL) 
    { 
        if ((curr->degree != next->degree) || 
                ((next->sibling != NULL) && 
                 (next->sibling)->degree == 
                 curr->degree)) 
        { 
            prev = curr; 
            curr = next; 
        } 
  
        else
        { 
            if (curr->data <= next->data) 
            { 
                curr->sibling = next->sibling; 
                binomialLink(next, curr); 
            } 
            else
            { 
                if (prev == NULL) 
                    res = next; 
                else
                    prev->sibling = next; 
                binomialLink(curr, next); 
                curr = next; 
            } 
        } 
        next = curr->sibling; 
    } 
    return res; 
} 
  
// Function to insert a node 
void binomialHeapInsert(int x) 
{ 
    // Create a new node and do union of 
    // this node with root 
    root = unionBHeaps(root, createNode(x)); 
    size++;
} 
  
// Function to display the Nodes 
void display(node *h) 
{ 
    while (h) 
    { 
    
      printf("%d ",h->data); 
      display(h->child);       
      h = h->sibling; 
    } 

} 
  
// Function to reverse a list 
// using recursion. 
int revertList(node *h) 
{ 
    if (h->sibling != NULL) 
    { 
        revertList(h->sibling); 
        (h->sibling)->sibling = h; 
    } 
    else
        root = h; 
} 



node *getMinBHeap(node *h) 
{ 
    if (h == NULL) 
       return NULL; 
  
    node *min_node_prev = NULL; 
    node *min_node = h; 
  
    // Find minimum value 
    int min = h->data; 
    node *curr = h; 
    while (curr->sibling != NULL) 
    { 
        if ((curr->sibling)->data < min) 
        { 
            min = (curr->sibling)->data; 
            min_node_prev = curr; 
            min_node = curr->sibling; 
        } 
        curr = curr->sibling; 
    } 
  	return min_node;
    
} 





  
// Function to extract minimum value 
node *extractMinBHeap(node *h) 
{ 
    if (h == NULL) 
       return NULL; 
  
    node *min_node_prev = NULL; 
    node *min_node = h; 
  
    // Find minimum value 
    int min = h->data; 
    node *curr = h; 
    while (curr->sibling != NULL) 
    { 
        if ((curr->sibling)->data < min) 
        { 
            min = (curr->sibling)->data; 
            min_node_prev = curr; 
            min_node = curr->sibling; 
        } 
        curr = curr->sibling; 
    } 
  
    // If there is a single node 
    if (min_node_prev == NULL && 
        min_node->sibling == NULL) 
        h = NULL; 
  
    else if (min_node_prev == NULL) 
        h = min_node->sibling; 
  
    // Remove min node from list 
    else
        min_node_prev->sibling = min_node->sibling; 
  
    // Set root (which is global) as children 
    // list of min node 
    if (min_node->child != NULL) 
    { 
        revertList(min_node->child); 
        (min_node->child)->sibling = NULL; 
    } 
  size--;
    // Do union of root h and children 
    if(root->sibling!=h || h==NULL)
    		return unionBHeaps(h, root); 
   else
   		return h;
} 
  
// Function to search for an element 
node *findNode(node *h, int data) 
{ 
    if (h == NULL) 
      return NULL; 
  
     // check if key is equal to the root's data 
    if (h->data == data) 
        return h; 
  
    // Recur for child 
    node *res = findNode(h->child, data); 
    if (res != NULL) 
       return res; 
  
    return findNode(h->sibling, data); 
} 
  
// Function to decrease the value of old_val 
// to new_val 
void decreaseKeyBHeap(node *H, int old_val, 
                               int new_val) 
{ 
    // First check element present or not 
    node *node1 = findNode(H, old_val); 
  
    // return if node is not present 
    if (node1 == NULL) 
        return; 
  
    // Reduce the value to the minimum 
    node1->data = new_val; 
        for(garb=0;garb<10;garb++){
    	
    }
    node *parent = node1->parent; 
  
    // Update the heap according to reduced value 
    while (parent != NULL && node1->data < parent->data) 
    { 
        int tmp=node1->data;
        node1->data=parent->data;
        parent->data=tmp;
        node1 = parent; 
        parent = parent->parent; 
    } 
} 

  
// Function to delete an element 
node *binomialHeapDelete(node *h, int data) 
{ 
    if (h == NULL){
        return NULL; 

 }
 
     	    decreaseKeyBHeap(h, data, -10000); 
 
    // Delete the minimum element from heap 
    return extractMinBHeap(h); 

    // Check if heap is empty or not

      for(garb=0;garb<10;garb++){
    	
    }
    // Reduce the value of element to minimum 

} 

struct list{
	int val;
	int lvl;
};

void traverse(struct list lst[],int * index,node * h,int level){
	while(h!=NULL){
		lst[*index].val=h->data;
		lst[*index].lvl=level;
		++(*index);
		traverse(lst,index,h->child,level+1);
		h=h->sibling;
	}
}


void levelordertraverse(node * h){
	struct list list[size+1];
	int index=0;
	traverse(list,&index,h,0);
	int i;
	for(i=0;i<size-1;i++){
		int j;
		for(j=0;j<size-i-1;j++){
			if(list[j].lvl>list[j+1].lvl){
				int tempval=list[j].val;
				int templevel=list[j].lvl;
				list[j].val=list[j+1].val;
				list[j].lvl=list[j+1].lvl;
				list[j+1].val=tempval;
				list[j+1].lvl=templevel;
			}
		}
	}
	for(i=0;i<size;i++){
		printf("%d ",list[i].val);
	}
}


int main() {
   char ch='a';
       for(garb=0;garb<10;garb++){
    	
    }
    size=0;
   FILE * fp,*fr;
   fr=fopen("output.txt","w");
	if((fp=fopen("input.txt","r"))!=NULL){
        while(!feof(fp) && ch!='s'){
        			fscanf(fp,"%c",&ch);
                if(ch=='i'){
                        int temp;
                        fscanf(fp," %d",&temp);
        							binomialHeapInsert(temp);
                }
                else if(ch=='p'){
								levelordertraverse(root);
								printf("\n");

                }             
                else if(ch=='d'){
                     int temp;
                    fscanf(fp,"%d",&temp);
							root=binomialHeapDelete(root,temp); 
                }  
                else if(ch=='m'){
		                node *p = getMinBHeap(root);
		                if (p != NULL)
		                    printf("%d\n", p->data);
							  else 	
							  	printf("NULL\n");
                }            
		          else if(ch=='x'){
		                root = extractMinBHeap(root);
		             }
                else if(ch=='s'){
							break;
                }  
   		}
   }   
   else{
        printf("Error loading file");
   } 
	    for(garb=0;garb<10;garb++){
    	
    }   
	return 0;              
}
