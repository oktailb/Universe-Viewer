#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the distance between QSO see by Vectors v1 and v2		*/

double inter_distance(Environnement *env, Vector *v1,Vector *v2)
{
  double ps=0,reponse=0;
  
  if (env->friedman.k>0.0)
    {
      ps=Vscalar(env, *v1,*v2);
      reponse=acos(ps);
    }
  else if (env->friedman.k<0.0)
    {
      ps=Vscalar(env, *v1,*v2);
      reponse=ACOSH(ABS(ps));
    }
  else if (env->friedman.k==0.0)
    reponse=Vnorme(env, Vadd(*v1,Vmult(*v2,-1.0)));
  return reponse;
  
}

