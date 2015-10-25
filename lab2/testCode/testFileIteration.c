#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(void) {
  char *traceEntry1;
  FILE *ifp;

  traceEntry1 = malloc(200*sizeof(char));
  ifp = fopen("./textIteration.txt", "r");

  while (fgets(traceEntry1, 75, ifp))
    printf("String input is %s \n", traceEntry1);
  fclose(ifp);
}
