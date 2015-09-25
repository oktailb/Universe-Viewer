#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* give the value of R/sqrt(P(R))  				*/

double RonPdeR(Environnement *env, double R)
{
  return R/sqrt(PdeR(env, R));
}

