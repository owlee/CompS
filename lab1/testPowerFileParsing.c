#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

  // Global Variables
  double R[5][4];
  double C[4];
  double W[100];
  double Tamb;

int main (int argc, char *argv[]) {
  int count;
  char *paramFilename;
  char *powerFilename;
  char *outputFilename;

  // SETTING UP AMBIENT AND INPUT FILES
  assert((argc == 4) || (argc == 5));
  if(argc == 4) {
    paramFilename = argv[1];
    powerFilename = argv[2];
    outputFilename = argv[3];
    Tamb = 300.0;

  } else if(argc == 5) {
    FILE* ambientF;
    paramFilename = argv[1];
    powerFilename = argv[2];
    ambientF = fopen(argv[3], "r");
    outputFilename = argv[4];

    double amb;
    fscanf(ambientF, "%lf", &amb);
    Tamb = amb;

    fclose(ambientF);
  }

  // SETTING GLOBAL VARIABLES
  //readpowerF(powerFilename);
  //setRes(paramFilename);
  //setCap(paramFilename);

  // GETTING NUMBER OF LINES IN  POWERFILE;
  int ch, numLinesPower = 0;
  FILE* powerF = fopen(powerFilename, "r");
  do {
    ch = fgetc(powerF);
    if(ch == '\n')
      numLinesPower++;
  } while (ch != EOF);

  if(ch != '\n' && numLinesPower != 0)
    numLinesPower++;

  printf("number of lines in power file is: %d\n", numLinesPower);

}
