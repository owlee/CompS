#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

  // Given y0, and h
  // t0 might just be 0.
  // h0 might also just be 0.005

double[] f(double Ti, double Tj, double Rij, double Ci, Wi) {

}

double rk(double t0, double y0, double h) {
  int n = 4;
  double fi, k1, k2, k3, k4, y1;
  for(; t0<n; t0=t0+h) {
    fi = f(t0,y0);
    k1 = h * fi;
    fi = f(t0 + h/2, y0 + k1/2);
    k2 = h * fi;
    fi = f(t0 + h/2, y0 + k2/2);
    k3 = h * fi;
    fi = f(t0 + h, y0 + k3);
    k4 = h * fi;

    y1 = y0 + (1/6) * (k1 + 2*k2 + 2*k3 + k4);
    y0=y1;
  }
  return y0;
}

// Creates a 2D matrix (R and C)
double* getMatrix (char* fileName) {
  // input one file and return an array
}

  // writes a single line into file
int outputToFile(char* fileName, double time, double[] tempArr, double[] ageArr) {
  // 3. compiles results into a string line
  //    Then, writes the string line into the outputFile
  char* outputStr = "";

  iter2=0;
  outputStr = outputStr + t; // first includes the time

  for(iter2=0; iter2<4; iter2++) {
    outputStr = outputStr + " " + tempArr[iter2] + " " + ageArr[iter2];
  }

  fputs(outputStr, outputF);

  return 0; // 0 = success
}

int main (int argc, char *argv[]) {
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
  double tempArr[4];
  double h = 0.005; // time step
  double t = 0; // Cold start

  for (iter1=0; i<numRecords; i++) {

    // 1. getting the ambient Temperatures
    tempArr = rk(t, T1, T2, T3, T4);

    // 2. getting the age accelerations
    ageArr = age(tempArr);

    // 3. write results into file
    outputToFile(outputF, t, tempArr, ageArr);

    // time steps by h.
    t = t + h;
  }

  fclose(paramF);
  fclose(powerF);
  fclose(outputF);

  printf("I have reached the end of this program.");

  return 0;
}
