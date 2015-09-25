#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the values of Omega et Lambda which a right number of causal cells.	*/

Point *grapheC4(Environnement *env, double Omax)
{
  int i,j,taille,trouve;
  double r,o0,k0,a0,l0;
  double cell,erreur,pas,old_r;
  Point *graph;

  graph = xmalloc(sizeof(*graph) * env->graphC4_lenght);
  env->zr=1100.0;
  env->old_friedman=env->friedman;
  a0=env->friedman.alpha;
  taille=(int) (Omax/ (env->graphC4_eps))+1;
  pas=(double) (Omax/env->graphC4_lenght);
  r=2*env->graphC4_eps;
  old_r=r;
  o0=0.01-pas;
  for(j=0;j<env->graphC4_lenght;j++)
    {
      o0+=pas;
      l0=0.0;
      trouve=0;
      r=old_r;
      while(trouve==0 && r>(old_r/8.0))
	{
	  l0=0.0;
	  r=r/2.0;
	  while( l0<=Omax)
	    {
	      l0+=r;
	      k0=-1+o0+a0+l0;
	      env->friedman.omega=o0;
	      env->friedman.lambda=l0;
	      env->friedman.k=k0;
	      if (k0>0.0)
		{
		  cell=donne_cell(env);
		  erreur=ABS(test_C4(cell, env->nb_causal_cell));
		  if (erreur<=env->graphC4_eps)
		    {
		      graph[j].x=o0;
		      graph[j].y=l0;
		      trouve=1;
		      break;
		    }
		  else if (j>0)
		    {
		      graph[j].x=graph[j-1].x;
		      graph[j].y=graph[j-1].y;
		    }
		  else
		    {
		      graph[j].x=o0;
		      graph[j].y=l0;
		    }
		}
	    }
	}
    }
  for(i=0;i<env->graphC4_lenght;i++)
    {
      graph[i].x/=Omax;
      graph[i].y/=Omax;
    }
  env->friedman=env->old_friedman;
  return (graph);
}

