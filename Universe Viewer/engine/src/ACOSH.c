#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the arc cosh of cosh(teta)						*/

double ACOSH(double chteta)
  {
	double shteta,teta;

	shteta=sqrt(1+chteta*chteta);
	teta=log(chteta+shteta);
	
	return teta;
  }

