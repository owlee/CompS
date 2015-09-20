
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>


int main(void) {

     int *intPtr;
     float *floatPtr;
     double *doublePtr;
     char *charPtr;
     long double *longdoublePtr;

     intPtr = (int *) malloc(sizeof(int));
     floatPtr = (float *) malloc(sizeof(float));
     doublePtr = (double *) malloc(sizeof(double));
     charPtr = (char *) malloc(sizeof(char));
     longdoublePtr = (long double *) malloc(sizeof(long double));

  
     printf("intPtr=%d; \t\t intPtr+1=%d\n", intPtr, intPtr+1);
     printf("floatPtr=%d; \t floatPtr+1=%d\n", floatPtr, floatPtr+1);
     printf("doublePtr=%d; \t doublePtr+1=%d\n", doublePtr, doublePtr+1);
     printf("charPtr=%d; \t\t charPtr+1=%d\n", charPtr, charPtr+1);
     printf("longdoublePtr=%d; \t longdoublePtr+1=%d\n", 
               longdoublePtr, longdoublePtr+1);
 


}
