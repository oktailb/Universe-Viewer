#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the number of causal cell of a model 				*/

double donne_cell(Environnement *env)
{
  double Zr,tc,tr,tetac=0,cell;

  Zr=1100.0;
  tc=sqrt(ABS(env->friedman.k))*integral(env, ONEonPdeR,0.0,1.0/(double) (1.0+Zr),env->graphC_prec);
  tr=sqrt(ABS(env->friedman.k))*donne_integral(env, ONEonPdeR,1.0/(double) (1.0+Zr),1.0,10,env->graphC_prec);
  if (env->friedman.k>0.0)
    tetac=2*sin(sin(tc)/sin(tr));
  else if (env->friedman.k==0.0)
    tetac=2*sin(tc/tr);
  else if (env->friedman.k<0.0)
    tetac=2*sin(sinh(tc)/sinh(tr));
  cell=sqrt(2)/(1-cos(tetac));
  return cell;
}

