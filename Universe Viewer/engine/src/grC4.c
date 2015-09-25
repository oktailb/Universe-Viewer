#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* this function is the second test procedure for causal cell curve		*/

Point *grC4(Environnement *env, double Omax)
{
  int i;
  double zr,r,o0,k0,a0,l0;
  double cell,erreur,old_erreur,pas;
  Point *graphC4;

  graphC4 = xmalloc(sizeof(*graphC4) * env->graphC4_lenght);
  zr=1100.0;
  env->old_friedman=env->friedman;
  a0=env->friedman.alpha;
  r=Omax/(double) (env->graphC4_lenght);
  o0=0.01-r;
  for(i=0;i<env->graphC4_lenght;i++)
    {
      o0+=r;
      pas=0.05;
      old_erreur=0.0;
      erreur=10.0;
      printf("o0=%f\n",o0);
      l0=0.0;
      while(l0<=Omax && ABS(erreur)>env->graphC4_eps)
	{
	  l0+=pas;
	  k0=-1+o0+a0+l0;
	  env->friedman.omega=o0;
	  env->friedman.lambda=l0;
	  env->friedman.k=k0;
	  if (k0>0.0)
	    {
	      cell=donne_cell(env);
	      erreur=test_C4(cell,env->nb_causal_cell);
	      
	      printf("cell=%f  || erreur= %f   ||  old=  %f\n",
		     cell,erreur,old_erreur);
	      printf("pas=%f  || l0= %f \n",pas,l0);
	      
	      if (erreur*old_erreur<0)
		{
		  l0=l0-pas;
		  pas=pas/10.0;
		  break;
		}
	      old_erreur=erreur;
	      
	    }
	}
      if (ABS(erreur)<=env->graphC4_eps)
	{
	  graphC4[i].x=o0;
	  graphC4[i].y=l0;
	  printf("OK, j'ai trouve le %d  %f point.\n",i,erreur);
	  printf("x[i]= %f || y[i]= %f\n",graphC4[i].x,graphC4[i].y);
	  
	}
      else if (i>0)
	{
	  graphC4[i].x=graphC4[i-1].x;
	  graphC4[i].y=graphC4[i-1].y;
	  printf("PLANTE");
	}
      else 
	{
	  graphC4[i].x=0.0;
	  graphC4[i].y=0.0;
	  printf("PLANTE");
	}
      
    }
  for(i=0;i<env->graphC4_lenght;i++)
    {
      graphC4[i].x/=Omax;
      graphC4[i].y/=Omax;
    }
  return (graphC4);
}
