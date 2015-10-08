
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>


int main(void) {

    int x[10][10];
    int i;
    int j;

    printf("x = %d; x+1 = %d\n", x, x+1);

    for (i=0; i<5; i++) 
      for (j=0; j<5; j++)
         x[i][j] = 10*i+j;


    for (i=0; i<5; i++) 
      for (j=0; j<5; j++) 
         printf("x[i][j]=%d; *(x[i]+j)=%d; *(*(x+i)+j)=%d\n",
                 x[i][j],    *(x[i]+j),    *(*(x+i)+j) );

}
