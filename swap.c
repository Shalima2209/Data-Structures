#include<stdio.h>
int main()
{
  int first,second,temp;
  printf("enter the first number:");
  scanf("%d", &first);
  printf("enter the second number:");
  scanf("%d", &second);
  temp = first;
  first = second;
  second = temp;
  printf("After swapping,first number = %d\n",first);
  printf("After swapping,second number = %d\n",second);
  
  return 0;
}  
