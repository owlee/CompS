#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

  // Global Variables
  double R[5][4];
  double C[1][4];

int main(int argc, char *argv[]) {
  int count;
  FILE *paramF;
  FILE *powerF;
  FILE *outputF;

  double ambient;

  printf("argc: %i\n", argc);

  assert((argc == 4) || (argc == 5));

  // if input is 3. ambient is default. Else, we will use a predefined ambient from file.
  if(argc == 3) {
    paramF = fopen(argv[1], "r");
    powerF = fopen(argv[2], "r");
    outputF = fopen(argv[3], "w+");
    ambient = 300;

  } else if(argc == 4) {
    FILE* ambientF;
    paramF = fopen(argv[1], "r");
    powerF = fopen(argv[2], "r");
    ambientF = fopen(argv[3], "r");
    outputF = fopen(argv[4], "w+");

    // reads ambient file, adds integer characters and parses it into string with atol
    char* ambientS;
    char ambIter;
    while ((ambIter = fgetc(ambientF)) != EOF) {
      ambientS = ambientS + ambIter;
    }
    ambient = atol (ambientS);

    fclose(ambientF);
  }

  fclose(paramF);
  fclose(powerF);
  fclose(outputF);

  printf("I have reached the end of this program.");
  printf("The global ambient is: %f", ambient);

  return 0;
}
