#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

// Global Variables
  double R[4][4] = {
    {30, 40, 50, 30} ,
    {23, 41, 12, 43} ,
    {12, 24, 53, 23} ,
    {64, 24, 52, 13}
  };

  double C[4] = { 0.00005, 0.00006, 0.00007, 0.00003};

  double W[4] = { 4000, 2300, 4100, 3300};

double rk(int, double*, double);
double f(int, double, double*);

int main() {
    double h = 0.005;
  double tempArr[5] = {300, 300, 300, 300, 300};


  double val = rk(0, tempArr, h);


  printf("Temperature value: %f", val);
  return 0;
}

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
      sum += (T - tempArr[j]) / (R[i][j] * C[i]);
    }
  }
  sum += W[i]/C[i];
  return sum;
}
