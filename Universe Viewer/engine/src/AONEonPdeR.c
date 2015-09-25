#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* give the value of 1/|sqrt(P(R))|  				*/

double AONEonPdeR(Environnement *env, double R)
{
  return sqrt(ABS(1.0/PdeR(env, R)));
}

