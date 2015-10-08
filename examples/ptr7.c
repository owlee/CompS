#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>


int main(void) {

    int a[5]; 
    int b[5];
    int *c;
    int *d;

    c = (int *)a;
    d = (int *)b;

    printf("a=%d; b=%d; c=%d; d=%d\n", a,b,c,d);

    b=a; // will cause an error
    c=d; // ok
    d=a; // ok
     

}
