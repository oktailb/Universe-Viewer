#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* give the value of P(R)					*/

double PdeR(Environnement *env, double R)
{
  return (((env->friedman.lambda*R*R-env->friedman.k)*R
	   +env->friedman.omega)*R+env->friedman.alpha);
  
}

