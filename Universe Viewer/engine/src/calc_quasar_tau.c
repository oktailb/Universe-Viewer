#include "uv.h"

/* give the TAU of all QSO in a pointer					*/
Point* calc_quasar_tau (Environnement *env, Quasar *q)
{
  register int count;
  Point *graphT;
  
  env->bounced=0;
  env->graphTx_max = env->abacus_max;
  env->graphTy_max=M_PIl;
  if(q)
    {
      graphT = xmalloc((env->data_lenght+1) * sizeof(*graphT));
      if (env->friedman.k<0.0)
	for(count=0;count < env->data_lenght-1;count++)
	  {
	    q[count].tau = sqrt(-env->friedman.k)*earth_codistance(env, q+count);
	    graphT[count].x = q[count].redshift/env->graphTx_max;
	    graphT[count].y = q[count].tau/env->graphTy_max;
	  }
      if (env->friedman.k>0.0)
	for(count=0;count < env->data_lenght-1;count++)
	  {
	    q[count].tau = sqrt(env->friedman.k)*earth_codistance(env, q+count);
	    graphT[count].x=q[count].redshift/env->graphTx_max;
	    graphT[count].y=q[count].tau/env->graphTy_max;
	  }
      if (env->friedman.k==0.0)
	for(count=0;count < env->data_lenght-1;count++)
	  {
	    q[count].tau = earth_codistance(env, q+count);
	    if (q[count].tau > env->distance_max) 
	      env->distance_max=q[count].tau;
	    graphT[count].x=q[count].redshift/env->graphTx_max;
	    graphT[count].y=q[count].tau/env->graphTy_max;
	  }
      if(env->bounced == 1)
	printf("\n  This universe is bounced !   \n");
      return (graphT);
    }
  return (NULL);
}

