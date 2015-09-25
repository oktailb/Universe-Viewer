#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Make the values of R(t)						*/ 

Point *grapheA1(Environnement *env, double Rmax)
{
  int i;
  double r,yinte=0;
  Point *graphA;

  env->graphAx_max=0.0;
  env->graphAy_max=Rmax;
  
  if (Rmax< 1)
    env->inte = env->AGE_CST* integral(env, RonPdeR,0.0,1.0,env->graphA_prec);
  graphA = xmalloc(sizeof(*graphA) * env->graphA_lenght);
  r=Rmax/(double) (env->graphA_lenght-1);
  graphA[0].x=0;
  graphA[0].y=0;
  for(i=1;i<env->graphA_lenght;i++)
    {
      graphA[i].y=graphA[i-1].y+r;
      graphA[i].x=graphA[i-1].x+env->AGE_CST*integral(env, RonPdeR,
						      graphA[i-1].y,graphA[i].y,env->graphA_prec);
      if (graphA[i].y<=1)
	{ 
	  env->inte=graphA[i].x; 
	  yinte=graphA[i].y;
	}
      if (graphA[i].x>env->graphAx_max)
	env->graphAx_max=graphA[i].x;
      if(!i%10) printf("%d ,x: %f || y: %f\n",i,graphA[i].x,graphA[i].y);
    }
  env->inte+=env->AGE_CST*integral(env, RonPdeR,yinte,1.0,env->graphA_prec);
  env->age_universe=env->inte;
  for(i=1;i<env->graphA_lenght;i++)
    {
      graphA[i].y=(double) graphA[i].y/(double) env->graphAy_max;
      graphA[i].x=(double) graphA[i].x/(double) env->graphAx_max;
    }
  return (graphA);
}
