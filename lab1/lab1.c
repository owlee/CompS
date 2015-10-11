#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

  // Global Variables
  double R[5][4];
  double C[4];
  double W[100];
  double Tamb;

  // Functions for main
  double* rk(int i, double*, double);
  double* f(int, double, double*);
  int outputToFile(char*, double, double[], double[]);
  double age(double);
  void setRes(char*);
  void setCap(char*);
  void readpowerF(char*);

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
    ambient = 300.0;

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
  readpowerF(powerFilename);
  setRes(paramFilename);
  setCap(paramFilename);

  // GETTING NUMBER OF LINES IN  POWERFILE;
  int ch, numLinesPower = 0;

  do {
    ch = fgetc(powerF);
    if(ch == '\n')
      numLinesPower++;
  } while (ch != EOF);

  if(ch != '\n' && numLinesPower != 0)
    numLinesPower++;

  // start parsing. The output file will end up with numRecords of temps and
  double h = 0.005; // time step
  double T0 = 0; // Cold start
  double ageArr[4];
  double tempArr[4];

  int t = 0; // t = first time at the power
  int iter;

  tempArr[0] = Tamb;
  tempArr[1] = Tamb;
  tempArr[2] = Tamb;
  tempArr[3] = Tamb;

  for (iter=0; iter<numLinesPower; iter++) {

    // 1. getting the Temperatures of t + h
    int i; // i represents the core number
    for(i=0; i<4; i++) {
      tempArr[i] = rk(i, tempArr, h);
    }

    // 2. getting the age accelerations
    for(i=0; i<4 i++) {
      ageArr[i] = age(tempArr[i]);
    }

    // 3. write results into file
    int write_check = outputToFile(outputFilename, t, tempArr, ageArr);
    assert(write_check == 0);

    // time steps by h.
    t = t + h;
  }

  fclose(paramF);
  fclose(powerF);
  fclose(outputF);

  printf("I have reached the end of this program.");

  return 0;
}

// FUNCTIONS OUTSIDE OF MAIN()
  // finds the next temperatures by h stepy T(t0 + h)
double rk(int i, double* tempArr, double h) {
  double k1, k2, k3, k4, T0, y1, y2, y3, next_temp;

  T0 = tempArr[i];

  k1 = f(i, T0, tempArr);
  y1 = T0 + k1 * h/2;

  k2 = f(i, y1, tempArr);
  y2 = T0 + k2 * h/2;

  k3 = f(i, y2, tempArr);
  y3 = T0 + k3 + h;

  k4 = f(i, y3, tempArr);

  next_temp = T0 + (h/6) * (k1 + 2*k2 + 2*k3 + k4);

  return next_temp;
}

double f(int i, double T, double* tempArr) {
  double sum = 0;
  int j;
  for(j=0; j<5; j++) {
    if (j != i) {
      sum += (T - tempArr[j]) / (R[i][j] * C[0][i]);
    }
  }
  sum += W[i]/C[i];
  return sum;
}

  // writes a single line into file
int outputToFile(char* fileName, double t0, double tempArr[], double ageArr[]){
  assert(fileName != NULL);

  FILE* outputF = fopen(fileName, "w");

  fprintf(outputF, "%lf %lf %lf %lf %lf %lf %lf %lf %lf\n", t0, tempArr[0], ageArr[0], tempArr[1], ageArr[1], tempArr[2], ageArr[2], tempArr[3], ageArr[3]);

  fclose(outputF);

  return 0;
}

double age(double Temp) {
  double E = 0.8;
  double k = 0.00008617;
  double Tamb = 300.0;

  return exp(((-E/k)*((1/Temp)-(1/Tamb))));
}

//method for importing Resistor values from paramFile
void setRes(char* fileName){
  int i;
  int j;
  char buf[100];
  double** space=malloc(5*sizeof(double*));
  for(i=0;i<5;++i)
    space[i]=malloc(4*sizeof(double));

  FILE* Rvalues;
  Rvalues=fopen(fileName, "r");
  fgets(buf, 100, Rvalues);
  for(i = 0; i < 5; i++)
  {
    for(j = 0; j < 4; j++)
    {
      if (!fscanf(Rvalues, "%lf", &space[i][j]))
        break;
      R[i][j] = space[i][j];
    }
  }
  fclose(Rvalues);
}

//METHOD FOR IMPORTING CAPACITOR VALUES from paramFile
void setCap(char* fileName){
  FILE *file = fopen(fileName, "r");
    int i=0;
    double num;
    while(fscanf(file, "%lf", &num) > 0 && i < 4) {
        C[i] = num;
        i++;
    }
    fclose(file);
}

//Read Power File
void readpowerF(char* fileName){
  FILE *file = fopen(fileName, "r");
    double num;
    while(fscanf(file, "%lf", &num) != EOF){
        W[i] = num;
    }
    fclose(file);
}
