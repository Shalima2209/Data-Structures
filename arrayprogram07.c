#include<stdio.h>
 
int main()
    {
    
     int tArr[5][5];
     int i,j;

     for(i=0;i<5;i++) //assign values to the two-dimensional array
        for(j=0;j<=5;j++){
           if(i==0) tArr[i][j]=j+1; //fill the first
           if(i>0 && j==0)

              tArr[i][j]=tArr[i-1][4]+1; //fetching the value of the last cell in the previous row
           else
             tArr[i][j]=tArr[i][j-1]+1; //fill subsequent cells
             }    
           
     for(i=0;i<5;i++){ //print the array
        for(j=0;j<5;j++)
            printf("%d\t",tArr[i][j]);
       printf("\n");  
       }
       
     return 0;
 
    }
