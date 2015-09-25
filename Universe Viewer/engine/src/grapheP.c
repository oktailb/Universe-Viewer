#include "uv.h"

/*------------------------------------------------------------------------------------*/

/*  give a pointer of the values of 1/sqrt(P(R)) (use for graph)		*/

Point *grapheP(Environnement *env)
{
  register int i;
  double denomin;
  Point *graphP;
  
  env->graphPx_max=1.0;
  env->graphPy_max=0.0;
  graphP = xmalloc(env->graphP_lenght * sizeof(*graphP));
  for (i=0;i<env->graphP_lenght;i++)
    {
      graphP[i].x=(double) i/(double) (env->graphP_lenght-1);
      denomin=PdeR(env, graphP[i].x);
      if (denomin>0)
	graphP[i].y=AONEonPdeR(env, graphP[i].x);
      else if (denomin==0) graphP[i].y=0;
      else graphP[i].y=-AONEonPdeR(env, graphP[i].x);
      if (abs(graphP[i].y)>env->graphPy_max)
	env->graphPy_max=ABS(graphP[i].y);
    }
  if (env->graphPy_max!=0.0)
    for (i=0;i<env->graphP_lenght;i++)
      {
	graphP[i].y=(double) (graphP[i].y/env->graphPy_max);
      }
  return (graphP);
}

