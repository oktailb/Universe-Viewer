#include "uv.h"

/*-------------------------------------------------------------------------------------------------*/

/* Give an abacus for the homogen volum					*/

void init_abacusV(Environnement *env, double Zmax)
{
  register int j;
  int nmax,Nmax;
  double inte;
  
  env->abacus_max=env->abacus_max0;
  nmax=(int) (env->abacus_max/env->abacus_pas)+1;
  Nmax=(int) (Zmax/env->abacus_pas)+1;
  if (Nmax>nmax) 
    {
      env->abacus_max=Zmax;
      init_abacus(env);
    }
  if (Nmax<nmax) 
    {
      Nmax=nmax;
      init_abacus(env);
    }
  if (env->abacusV!=NULL)
    free(env->abacusV);
  env->abacusV = xmalloc((Nmax+1) * sizeof(*env->abacusV));
  env->abacusV[0]=0.0;
  for(j=1;j<=Nmax;j++)
    {
      inte=sqrt(ABS(env->friedman.k))*env->abacus[j];
      if (env->friedman.k>0.0)
	env->abacusV[j]=(2*inte-sin(2*inte))/(4*pow(env->friedman.k,1.5));
      if (env->friedman.k==0.0)
	env->abacusV[j]=inte*inte/3.0;
      if (env->friedman.k<0.0)
	env->abacusV[j]=(-2*+sinh(2*inte))/(4*pow(-env->friedman.k,1.5));
    }
}
