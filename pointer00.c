#include <stdio.h>
int main()
{
   int i = 10;
   int * p =&i;
   printf("The address of variable i is: %p", p);
 
   return 0;
}
