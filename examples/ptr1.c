
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>


int main(void) {

     int *i;   
     int *j;


     printf("&i = %x; i=%x\n", &i, i);
     i = (int *) malloc(sizeof(int));
     *i=5;
     printf("&i = %x; i=%x\n", &i, i);
     free(i);  // Beyond this point, i does not necessarily point to
               // anything meaningful.  It will still hold something, though.
               // 
     j = (int *) malloc(sizeof(int));
     printf("&i = %x; i=%x\n", &i, i);
     printf("&j = %x; j=%x\n", &j, j);

}
