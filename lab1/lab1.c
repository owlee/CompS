#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>

  // Global Variables
  double R[4][4];
  double C[4];
  double ambient;

  // Functions for main
  double* rk(double*, double*, double*);
  double* getMatrix*(char*);
  double* f(double, double, double, double, double, double);
  double fHelper(double, double, double, double);
  int outputToFile(char*, double, double[], double[]);
  double age(double);

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

  // start parsing. The output file will end up with numRecords of temps and

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
double rk(int i, double* tempArr, double h) {
  double k1, k2, k3, k4, T0, T1, T2, T3, next_temp;

  T0 = tempArr[i];

  k1 = f(i, T0, tempArr);
  y1 = T0 + k1 * h/2;

  k2 = f(i, y1, tempArr);
  y2 = T0 + k2 * h/2;

  k3 = f(i, y2, tempArr);
  y3 = T0 + k3 + h

  k4 = f(i, y3, tempArr);

  next_temp = T0 + (h/6) * (k1 + 2*k2 + 2*k3 + k4);

  return next_temp;
}

double f(int i, double T, double* tempArr) {
  double sum = 0;
  int j;
  for(j=0; j<5; j++) {
    if (j != i) {
      sum += (T - tempArr(j)) / (R[i][j] * C[i]);
    }
  }
  sum += w[i]/c[i];
  return sum;
}

// Creates a 2D matrix (R and C)
double* getMatrix(char* fileName) {
  // input one file and return an array
}

  // writes a single line into file
int outputToFile(char* fileName, double t0, double tempArr[], double ageArr[]){
  assert(fileName != NULL);

  //  1. Compiles results into a string line
  //  2. Writes the string line into the outputFile
  char* outputStr = "";
  FILE* outputF = fopen(fileName, "w");

  fprintf(outputF, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", t0, tempArr[0], ageArr[0], tempArr[1], ageArr[1], tempArr[2], ageArr[2], tempArr[3], ageArr[3]);

  fclose(outputF);

  return 0;
}

double age(double Temp) {
  double E = 0.8;
  double k = 0.00008617;
  double Tamb = 300.0;

  return exp(((-E/k)*((1/Temp)-(1/Tamb))));
}

     //method for importing parameter values

double** getMatrix(char* fileName){
  int i;
  int j;

double** space=malloc(6*sizeof(double*)); 
for(i=0;i<6;++i)
space[i]=malloc(4*sizeof(double));
  FILE *Rvalues;
  Rvalues=fopen(fileName, "r");

 for(i = 0; i<6; i++)
  {
      for(j = 0; j<4; j++) 
      {
    if (!fscanf(Rvalues, "%lf", &space[i][j])) 
           break;
  printf("%lf\n",space[i][j]); 
      }

  }
  fclose(Rvalues);
}