#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

  // Given y0, and h
  // t0 might just be 0.
  // h0 might also just be 0.005

//#define f(x,y)  1 + (y)*(y)

double f(double x, double y)
{
  return 1 + (y)*(y);
}

double rk(double t0, double y0, double h)
{
  int n = 4;
  double fi, k1, k2, k3, k4, y1;
  for(; t0<n; t0=t0+h)
  {
    fi = f(t0,y0);
    printf(" rk: %f", fi);
    k1 = h * fi;
    fi = f(t0 + h/2, y0 + k1/2);
    k2 = h * fi;
    fi = f(t0 + h/2, y0 + k2/2);
    k3 = h * fi;
    fi = f(t0 + h, y0 + k3);
    k4 = h * fi;

    y1 = y0 + (1/6) * (k1 + 2*k2 + 2*k3 + k4);
    y0=y1;
    printf(" rk: %f", y1);
  }
  return y0;
}

int main (int argc, char *argv[])
{
  int count;
  double ambient;
  FILE* paramF, powerF, outputF;

  assert((argc == 3) || (argc == 4))

  // if input is 3. ambient is default. Else, we will use a predefined ambient from file.
  if(argc == 3) {
    paramF = fopen(argv[1], "r");
    powerF = fopen(arg[2], "r");
    outputF = fopen(arg[3], "w+");
    ambient = 300;

  } else if(argc == 4) {
    FILE* ambientF;
    paramF = fopen(argv[1], "r");
    powerF = fopen(arg[2], "r");
    ambientF = fopen(argv[3], "r");
    outputF = fopen(argv[4], "w+");

    // reads ambient file, adds integer characters and parses it into string with atol
    char* ambientS;
    while (ambIter = fgetc(ambientF)!=EOF) {
      ambientS = ambientS + ambIter;
    }
    ambient = atol (ambientS)

    fclose(ambientF);
  }

  // start parsing. The output file will end up with numRecords of temps and age
  int numRecords = 10;
  int iter1;
  for (iter1=0; i<numRecords; i++) {

  }

  fclose(paramF);
  fclose(powerF);
  fclose(outputF);
  //double val = rk(0, 10, 0.005);
  printf("I have reached the end of this program.");

  return 0;
}
