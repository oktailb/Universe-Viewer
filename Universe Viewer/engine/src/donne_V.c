#include "uv.h"

/*-------------------------------------------------------------------------------------------------*/

/* Give the volum of a given redshift						*/

double donne_V(Environnement *env, double Z)
{
  double inte=0,V=0,nmax;
  int i,rajout=0;
  
  nmax=(int) (env->abacus_max/env->abacus_pas)+1;
  for(i=0;i<=nmax;i++)
    if (Z>=i*env->abacus_pas && Z<(i+1)*env->abacus_pas)
      {
	inte=sqrt(ABS(env->friedman.k))*env->abacus[i];
	rajout=i;
	break;
      }	 
  inte+=sqrt(ABS(env->friedman.k))*integral(env, ONEonPdeR,1.0/(1.0+Z),1.0/(1.0+(rajout*env->abacus_pas)),env->abacus_prec);
  if (env->friedman.k>0.0)
    V=(2*inte-sin(2*inte))/(4*pow(env->friedman.k,1.5));
  if (env->friedman.k==0.0)
    V=inte*inte*inte/3.0;
  if (env->friedman.k<0.0)
    V=(-2*inte+sinh(2*inte))/(4*pow(-env->friedman.k,1.5));
  return V;
}
