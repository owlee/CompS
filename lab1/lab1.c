#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

  // Global Variables
  double RC[];
  double ambient;

  // Functions for main
  double* rk(double*, double*, double*);
  double* getMatrix*(char*);
  double* f(double, double, double, double, double, double);
  double fHelper(double, double, double, double);
  int outputToFile(char*, double, double[], double[]);

int main (int argc, char *argv[]) {
  int count;
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

// FUNCTIONS OUTSIDE OF MAIN
  // finds the next temperatures by h stepy T(t0 + h)
double* rk(double* TempArr, double* rcArr, double* t0) {
  int n = 4;
  double fi, k1, k2, k3, k4, y1;
  double k1[4];
  double k2[4];
  double k3[4];
  double k4[4];
  double temp_h[4];
  int iterRk;

  for(iterRk=0; iterRk<n; iterRk++) {
    fi = f(t0, temp[iterRk][0], temp[iterRk][1], temp[iterRk][2], temp[iterRk][3]);
    k1[iterRk] = h * fi;
  }

  for(iterRk=0; iterRk<n; iterRk++) {
    fi = f(t0 + h/2, temp[iterRk][0] + k1[iterRk]/2, temp[iterRk][1] + k1[iterRk]/2, temp[iterRk][2] + k1[iterRk]/2, temp[iterRk][3] + k1[iterRk]/2);
    k2[iterRk] = h * fi;
  }

  for(iterRk=0; iterRk<n; iterRk++) {
    fi = f(t0 + h/2, temp[iterRk][0] + k1[iterRk]/2, temp[iterRk][1] + k1[iterRk]/2, temp[iterRk][2] + k1[iterRk]/2, temp[iterRk][3] + k1[iterRk]/2);
    k3[iterRk] = h * fi;
  }

  for(iterRk=0; iterRk<n; iterRk++) {
    fi = f(t0 + h, temp[iterRk][0] + k1[iterRk], temp[iterRk][1] + k1[iterRk], temp[iterRk][2] + k1[iterRk], temp[iterRk][3] + k1[iterRk]);
    k4[iterRk] = h * fi;
  }

  for(iterRk=0; iterRk<n; iterRk++) {
    temp_h[iterRk] = temp[0][iterRk] + (1/6) * (k1[iterRk] + 2*k2[iterRk] + 2*k3[iterRk] + k4[iterRk]);
  }

  return temp_h;
}


// Creates a 2D matrix (R and C)
double* getMatrix(char* fileName) {
  // input one file and return an array
}

double* f(double t0, double TTarget, double T1, double T2, double T3, double T4) {
  assert(rc != null);
  assert(ambient != null);

  double sum = 0;
  double Tamb = T5;
  int iterF;
  double sum += fHelper(TTarget, T1);
  sum += fHelper(TTarget, T2);
  sum += fHelper(TTarget, T3);
  sum += fHelper(TTarget, T4);

  sum +=
}

  // One iteration of sigma
    // arg { temp of curr core, temp of comparing core, thermal resistance between two, and thermal cap of curr core
double fHelper(double Ti, double Tj, double Rij, double Ci) {
  return (Ti - Tj)/(Rij * Ci);
}

  // writes a single line into file
int outputToFile(char* fileName, double t0, double[] tempArr, double[] ageArr) {
  assert(fileName != null);

  //  1. Compiles results into a string line
  //  2. Writes the string line into the outputFile
  char* outputStr = "";
  FILE* outputF = fileName;

  int iter;
  outputStr = strcat(outputStr, t0); // first includes the time

  for(iter=0; iter<4; iter++) {
    outputStr = strcat(outputStr, " ");
    outputStr = strcat(outputStr, tempArr[iter2];
    outputStr = strcat(outputStr, " ");
    outputStr = strcat(outputStr, ageArr[iter2]);
  }

  fputs(outputStr, outputF);

  fclose(outputF);

  return 0;
}
