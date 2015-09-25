#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* give the value of 1/sqrt(P(R))  				*/

int bounced = 0;

double ONEonPdeR(Environnement *env, double R)
{
  double pdr;
  
  pdr=PdeR(env, R);
  if(pdr>=0) return sqrt(1.0/pdr);
  else
    {
      bounced=1;
      return 0.0;
    }
}

