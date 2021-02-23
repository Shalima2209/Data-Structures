// inserting a key on b tree
#include<stdio.h>
#include<stdlib.h>

#define MAX 3
#define MIN 2

struct btreeNode
{
	int item[MAX+1], count;
	struct btreeNode *link[MAX+1];
};

struct btreeNode *root;

//node creation
struct btreeNode *createNode(int item, struct btreeNode *child)
{
	struct btreeNode *newNode;
	newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
	newNode->item[1] = item;
	newNode->count = 1;
	newNode->link[0] = root;
	newNode->link[1] = child;
	return newNode;
}

//insert
void insertValue(int item, int pos, struct btreeNode *node, struct btreeNode *child)
{
	int j = node->count;
	while(j>pos) 
	{
		node->item[j+1]=node->item[j];
		node->link[j+1]=node->link[j];
		j--;
	}
	node->item[j+1] = item;
	node->link[j+1] = child;
	node->count++;
}

//split node
void splitNode(int item, int *pval, int pos, struct btreeNode *node, struct btreeNode *child, struct btreeNode **newNode)
{
	int median, j;
	
	if(pos > MIN)
	  median = MIN +1;
	else
	  median = MIN;
	  
	*newNode = (struct btreeNode *)malloc(sizeof(struct btreeNode));
	j = median+1;
	while (j<=MAX)
	{
		(*newNode)->item[j - median] = node->item[j];
		(*newNode)->link[j - median] = node->link[j];
		j++;
	}
	node->count=median;
	(*newNode)->count = MAX - median;
	
	if(pos <=MIN)
	{
		insertValue(item, pos, node, child );
	}
	else
	{
		insertValue(item, pos - median, *newNode, child);
	}
	*pval = node->item[node->count];
	(*newNode)->link[0]=node->link[node->count];
	node->count--;
}

//set the value of node
int setNodeValue(int item, int *pval, struct btreeNode *node, struct btreeNode **child)
{
	int pos;
	if (!node)
	{
		*pval = item;
		*child = NULL;
		return 1;
	}
	if(item < node->item[1])
	{
		pos = 0;
	}
	else
	{
		for(pos = node->count;
		(item < node->item[pos] && pos > 1); pos--) ;
		if(item == node->item[pos])
		{
			printf("Duplicates not allowed\n");
			return 0;
		}
	}
	if(setNodeValue(item, pval, node->link[pos], child))
	{
		if(node->count < MAX)
		{
			insertValue(*pval, pos, node, *child);
		}
		else
		{
			splitNode(*pval, pval, pos, node, *child, child);
			return 1;
		}
	}
	return 0;
}

//insert the value
void insertion(int item)
{
	int flag, i;
	struct btreeNode *child;
	
	flag = setNodeValue(item, &i, root, &child);
	
	if(flag)
	  root=createNode(i, child);
  }
  
  //copy the successor
  void copySuccessor(struct btreeNode *myNode, int pos)
  {
	  struct btreeNode *dummy;
	  dummy = myNode->link[pos];
	  
	  for(; dummy->link[0] != NULL;)
	  dummy=dummy->link[0];
	  myNode->item[pos]=dummy->item[1];
  }
  
  //do rightshift
  void rightShift(struct btreeNode *myNode, int pos)
  {
	  struct btreeNode *x = myNode->link[pos];
	  int j = x->count;
	  
	  while(j>0)
	  {
		  x->item[j+1]=x->item[j];
		  x->link[j+1]=x->link[j];
	  }
	  x->item[1]= myNode->item[pos];
	  x->link[1]=x->link[0];
	  x->count++;
	  
	  x=myNode->link[pos-1];
	  myNode->item[pos]=x->item[x->count];
	  myNode->link[pos]=x->link[x->count];
	  x->count--;
	  return;
  }
  
  //do leftshift
   void leftShift(struct btreeNode *myNode, int pos)
  {
	  struct btreeNode *x = myNode->link[pos-1];
	  int j =1;
	  
	  while(j<=x->count)
	  {
		  x->item[j]=x->item[j+1];
		  x->link[j]=x->link[j+1];
		  j++;
	  }
	  x->item[x->count]= myNode->item[pos];
	  x->link[x->count]=myNode->link[pos]->link[0];
	  x->count++;
	  
	  x=myNode->link[pos];
	  myNode->item[pos]=x->item[1];
	  x->link[0]=x->link[1];
	  x->count--;
	  return;
  }
  
  //merge the nodes
  void mergeNodes(struct btreeNode *myNode, int pos)
  {
	  
   struct btreeNode *x1 = myNode->link[pos], *x2 = myNode->link[pos - 1];
   
	  int j =1;
	  
	  while(j<=x1->count)
	  {
		  x2->count++;
		  x2->item[x2->count]=x1->item[j];
		  x2->link[x2->count]=x1->link[j];
		  j++;
	  }
	  x2->item[x2->count]= myNode->item[pos];
	  x2->link[x2->count]=myNode->link[0];
	  x2->count++;
  
	 j=pos;
	 while(j< myNode->count)
	 {
		 myNode->item[j]=myNode->item[j+1];
		 myNode->link[j]=myNode->link[j+1];
		 j++;
	 }
	 myNode->count--;
	 free(x1);
 }
  
	
	
	   
// adjusr the node
void adjustNode(struct btreeNode *myNode, int pos)
{
	if(!pos)
	{
		if(myNode->link[1]->count>MIN)
		{
			leftShift(myNode, 1);
		}
		else {
			mergeNodes(myNode, 1);
		}
	}
	else {
		if(myNode->count!=pos)
		{
			if(myNode->link[pos-1]->count>MIN)
			{
				rightShift(myNode, pos);
			}
			else {
				if(myNode->link[pos+1]->count > MIN) {
					leftShift(myNode, pos +1);
				}
				else {
					mergeNodes(myNode, pos);
				}
			}
		}
		else {
			if(myNode->link[pos-1]->count >MIN)
			rightShift(myNode, pos);
			else
			mergeNodes(myNode, pos);
		}
	}
}

//traverse the tree
void traversal(struct btreeNode *myNode)
{
	int i;
	if(myNode)
	{
		for(i=0; i< myNode->count; i++)
		{
			traversal(myNode->link[i]);
			printf("%d", myNode->item[i+1]);
		}
		traversal(myNode->link[i]);
	}
}

int main()
{
	
	insertion(8);
	insertion(9);
	insertion(10);
	insertion(11);
	insertion(12);
	insertion(15);
	insertion(16);
	insertion(17);
	insertion(18);
	insertion(19);
	insertion(20);
	insertion(23);
	
	traversal(root);
}

				
