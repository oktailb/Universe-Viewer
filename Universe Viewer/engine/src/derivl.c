#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the value of derivative on Lambda of equation in test_C2 function*/


double derivl(double a, double k, double l, double o)
  {
	return 2.25*o*(l+k)/sqrt(3*k*l)+4.5*a-2*k;
  }

