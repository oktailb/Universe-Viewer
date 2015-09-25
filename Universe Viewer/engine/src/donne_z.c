#include "uv.h"

/*-------------------------------------------------------------------------------------------------*/

/* Give the redshift corresponding to a given volum				*/

double donne_z(Environnement *env, double V)
{
  int j,nmax;
  double Z;
  
  Z=0;
  nmax=(int) (env->abacus_max/env->abacus_pas)+1;
  for(j=1;j<=nmax;j++)
    {
      if (V>=env->abacusV[j] && env->abacusV[j+1]>V)
	{
	  Z=j*env->abacus_pas+
	    ((V-env->abacusV[j])*env->abacus_pas/(env->abacusV[j+1]-env->abacusV[j]));
	}
    }
  return Z;
}

