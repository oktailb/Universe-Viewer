#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* create an distance's abacus for redshift get from 0 to abacus_max	*/
/* by abacus_prec steps							*/

void init_abacus(Environnement *env)
{
  int j;
  int nmax;
  double da,db,inte;
  
  if (env->abacus!=NULL)
    free(env->abacus);
  nmax=(int) (env->abacus_max/env->abacus_pas)+1;
  env->abacus = xmalloc((nmax+1) * sizeof(*env->abacus));
  env->abacus[0]=0.0;
  for(j=1;j<=nmax;j++)
    {
      da=(double) 1.0/(1.0+(j*env->abacus_pas));
      db=(double) 1.0/(1.0+((j-1.0)*env->abacus_pas));
      inte=integral(env, ONEonPdeR,da,db,env->abacus_prec);
      env->abacus[j]=env->abacus[j-1]+inte;
    }
}

