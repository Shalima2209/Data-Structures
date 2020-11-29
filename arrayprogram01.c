#include <stdio.h>
int main()
{
	int arr[]={10,12,18,20,33,48,40,50};
	int n;
	
	n=sizeof(arr)/sizeof(int);
	
	printf("Number of elements are: %d\n",n);
	
	return 0;
}
