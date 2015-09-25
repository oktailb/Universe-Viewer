#include "uv.h"

/*------------------------------------------------------------------------------------*/
/* Give the value of derivative on Omega of equation in test_C2 function*/

double derivo(double a, double k, double l, double o)
{
  a = a;
	return 1.5*sqrt(3*l*k)+2.25*o*l/sqrt(3*k*l)-2*k;
}

