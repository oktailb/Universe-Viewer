#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* give the value of the derivative of RonPdeR on Lambda		*/

double DlaRonPdeR(Environnement *env, double R)
{
  return -0.5*R*(pow(R,4)-R*R)/pow(PdeR(env, R),1.5);
}

