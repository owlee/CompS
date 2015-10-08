#include <stdio.h>
#include <math.h>
#include <assert.h>

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
  if (argc > 1)
  {
    for (count = 1; count < argc; count++)
    {
      printf("argv[%d] = %s\n", count, argv[count]);
    }
  }
  else
  {
    printf("The command had no other arguments.\n");
  }
  //double val = rk(0, 10, 0.005);
  //printf("I have the following double val: %f", val);

   return 0;
}
