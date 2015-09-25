#include "uv.h"

/*------------------------------------------------------------------------------------*/

/* Give the value of Lambda made by the equation in test_C2 function 	*/

Point *grapheC2(Environnement *env, double Omax)
{
  int i;
  double r,o0,k0,a0,l0,dom,dl,del;
  Point *graphC2;

  graphC2 = xmalloc(sizeof(*graphC2) * env->graphC2_lenght);
  env->disfunction=0;
  a0=env->friedman.alpha;
  graphC2[0].x=0;
  graphC2[0].y=1-a0;
  l0=0;
  o0=0.01;
  r=Omax/(double) (env->graphC2_lenght-1);
  while(l0<=10)
    {
      o0=0.01;
      l0+=r;
      k0=-1+o0+a0+l0;
      if (k0<=0) continue;
      if (ABS(test_C2(a0,k0,l0,o0))<env->graphC2_eps)
	{
	  graphC2[1].x=o0;
	  graphC2[1].y=l0;
	  break;
	}
    }
  if (l0<=10)
    {
      for(i=2;i<env->graphC2_lenght;i++)
	{
	  k0=-1+o0+a0+l0;
	  dom=derivo(a0,k0,l0,o0);
	  dl=derivl(a0,k0,l0,o0);
	  del=(double) (-r*dom)/(double) dl;
	  o0+=r;
	  l0+=del;
	  graphC2[i].x=o0;
	  graphC2[i].y=l0;
	}
      for(i=0;i<env->graphC2_lenght;i++)
	{
	  graphC2[i].x/=Omax;
	  graphC2[i].y/=Omax;
	}
    }
  else 
    {
      env->disfunction=1;
	  printf(" This model is not available ");
    }
  return (graphC2);
}

