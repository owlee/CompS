#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

  // Global Variables
  double R[5][4];
  double C[1][4];
  double ambient;

int main(int argc, char *argv[]) {
  int count;
  FILE *paramF;
  FILE *powerF;
  FILE *outputF;

  printf("argc: %i\n", argc);

  assert((argc == 4) || (argc == 5));

  // if input is 3. ambient is default. Else, we will use a predefined ambient from file.
  if(argc == 4) {
    paramF = fopen(argv[1], "r");
    powerF = fopen(argv[2], "r");
    outputF = fopen(argv[3], "w+");
    ambient = 300;

  } else if(argc == 5) {
    FILE* ambientF;
    double amb;
    paramF = fopen(argv[1], "r");
    powerF = fopen(argv[2], "r");
    ambientF = fopen(argv[3], "r");
    outputF = fopen(argv[4], "w+");

    // reads ambient file, adds integer characters and parses it into string with atol
    fscanf(ambientF, "%lf", &amb);
    printf("I am the ambient from file: %lf", amb);

    ambient = amb;
    fclose(ambientF);
  }

  fclose(paramF);
  fclose(powerF);
  fclose(outputF);

  printf("I have reached the end of this program.");
  printf("The global ambient is: %f", ambient);

  return 0;
}
