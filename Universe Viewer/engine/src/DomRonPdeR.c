#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* give the value of the derivative of RonPdeR on Omega		*/

double DomRonPdeR(Environnement *env, double R)
{
  return -0.5*R*(R-R*R)/pow(PdeR(env, R),1.5);
}
