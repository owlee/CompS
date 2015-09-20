
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>


int main(void) {

     int *i;   
     char *j;
     float *k;
     double *l;
     long double *m;

     i=(int *)malloc(10*sizeof(int));
     j=(char *)malloc(10*sizeof(char));
     k=(float *)malloc(10*sizeof(float));
     l=(double *)malloc(10*sizeof(double));
     m=(long double *)malloc(10*sizeof(long double));

     printf("i=%6d; i+1=%6d; i+2=%6d\n", i, i+1, i+2);  // Illustrates that
     printf("j=%6d; j+1=%6d; j+2=%6d\n", j, j+1, j+2);  // pointer arithmetic
     printf("k=%6d; k+1=%6d; k+2=%6d\n", k, k+1, k+2);  // works in units of 
     printf("l=%6d; l+1=%6d; l+2=%6d\n", l, l+1, l+2);  // the size of the data
     printf("m=%6d; m+1=%6d; m+2=%6d\n", m, m+1, m+2);  // type being pointed to.


     free(i);
     free(j);
     free(k);
     free(l);
     free(m);
}
