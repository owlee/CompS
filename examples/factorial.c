#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int factorial(int);

int main(void) {
     int n;

     printf("Enter a non-negative integer \n");
     scanf("%u",  &n);
     printf("factorial of %d is %d\n", n, factorial(n));
}

int factorial(int number) {

   assert(number>=0);  // precondition: negative factorials must not be accepted.
   if (number == 0)
      return 1;
   else if (number == 1)
      return 1;
   else
      return number*factorial(number-1);

}
