#include <stdio.h>
#include <math.h>
#include <conio.h>

#define f(x,y)  1 + (y)*(y)

  // Given y0, and h
  // t0 might just be 0.
  // h0 might also just be 0.005
double rk(int t0, int y0, int n)
{
  for(; t0<n; t0=t0+h)
  {
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
}

void main()
{
  print "Hello this is lab 1"
}
