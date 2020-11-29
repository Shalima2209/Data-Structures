// C program to store marks obtained in two subjects of  students and display it.
#include <stdio.h>
const int SUBJECT = 2;
const int STUDENT = 8;
int main()
{
  int mark[SUBJECT][STUDENT];

  // Using nested loop to store values in a 2d array
  for (int i = 0; i < SUBJECT; ++i)
  {
    for (int j = 0; j < STUDENT; ++j)
    {
      printf("subject %d, Student %d: ", i + 1, j + 1);
      scanf("%d", &mark[i][j]);
    }
  }
  printf("\nDisplaying values: \n\n");

  // Using nested loop to display vlues of a 2d array
  for (int i = 0; i < SUBJECT; ++i)
  {
    for (int j = 0; j < STUDENT; ++j)
    {
      printf("subject %d, student %d = %d\n", i + 1, j + 1, mark[i][j]);
    }
  }
  return 0;
 }  
