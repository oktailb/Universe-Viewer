#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* give 1 if P(R)=0 on [xi,xf], 0 else				*/

int null_PdeR(Environnement *env, double xi, double xf, double step)
{
  int reponse;
  double R;
  
  reponse=0;
  for (R=xi;R<=xf;R+=step)
    {
      if (PdeR(env, R)==0) reponse=1;
      break;
    }
  return reponse;
}

