#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the values of Omega et Lambda which made the universe age right	*/

Point *grapheC3(Environnement *env, double Omax, double this_age_universe)
{
  int i,trouve;
  double r,o0,k0,a0,l0,dom,dl,del,val_test_C3,old_graphC3_eps;
  Point *graph;

  graph = xmalloc(sizeof(*graph) * env->graphC3_lenght);
  env->old_friedman=env->friedman;
  old_graphC3_eps=env->graphC3_eps;
  a0=env->friedman.alpha;
  l0=0.0;
  o0=0.01-0.05;
  trouve=0;
  r=Omax/(double) (env->graphC3_lenght-1);
  while(o0<=Omax && trouve==0)
    {
      o0+=0.05;
      l0=0.0;
      env->graphC3_eps*=1.5;
      while(l0<=Omax)
	{
	  l0+=r;
	  k0=-1+o0+a0+l0;
	  env->friedman.omega=o0;
	  env->friedman.lambda=l0;
	  env->friedman.k=k0;
	  val_test_C3=test_C3(env, this_age_universe);
	  if (ABS(val_test_C3)<env->graphC3_eps)
	    {
	      graph[0].x=o0;
	      graph[0].y=l0;
	      trouve=1;
	      break;
	    }
	}
    }
  if (trouve==1)
    {
      for(i=1;i<env->graphC3_lenght;i++)
	{
	  k0=-1+o0+a0+l0;
	  env->friedman.omega=o0;
	  env->friedman.lambda=l0;
	  env->friedman.k=k0;
	  dom=donne_integral(env, DomRonPdeR,0.0,1.0,env->quanta,env->graphC_prec);
	  dl=donne_integral(env, DlaRonPdeR,0.0,1.0,env->quanta,env->graphC_prec);
	  del=(double) -(r*dom)/(double) dl;
	  o0+=r;
	  l0+=del;
	  graph[i].x=o0;
	  graph[i].y=l0;
	}
      for(i=0;i<env->graphC3_lenght;i++)
	{
	  graph[i].x/=Omax;
	  graph[i].y/=Omax;
	}
    }
  else
    {
      env->disfunction=1;
      printf("Could not compute constant age curve for age=%f",this_age_universe);
    } 
  env->friedman=env->old_friedman;
  env->graphC3_eps=old_graphC3_eps;
  return (graph);
}

