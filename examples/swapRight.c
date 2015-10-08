
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

void swap(int *, int *);

int main(void) {

    int i;
    int j;

    i = 5;
    j = -4;

    printf("i=%d; j=%d\n", i, j);
    swap(&i,&j);
    printf("Return from swap function: i=%d; j=%d\n", i, j);

}

void swap(int *a, int *b) {
   int temp;
   temp = *a;
   *a = *b;
   *b = temp;

   printf("Within swap function: a=%d; b=%d\n", *a, *b);

}
